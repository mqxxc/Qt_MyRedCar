/*
*
* 创建日期：2022.06.0x
* 最后一次修改日期：2022.06.23
* 作者：寐晴下星辰
*
*/
#include<QSystemTrayIcon>
#include<QMenu>
#include<QSlider>
#include<QTimer>
#include<QLabel>
#include<QEventLoop>
#include<QEvent>
#include<QDesktopWidget>
#include<QLibrary>
#include"About.h"
#include"Tray.h"
#include"../getScreenInformation/getScreenInformation.h"

#define TRAY_H
#include"macro.h"


Tray::Tray(){
	//初始化变量
    ico  = new QSystemTrayIcon();
    menu = new QMenu();
    list = new QAction * [5];
    about = nullptr;
    volumScr = new QWidget;
    volumeico = new QLabel(volumScr);
    scr = new QSlider(volumScr);
    vIcoState = true;
    loop = new QEventLoop(volumScr);
    oldVolume = 100;
    init();
    connects();
}

Tray::~Tray(){
    delete loop;
    delete volumScr;
    for (int i = 0; i < 5; ++i) {
       delete list[i];
    }
    delete list;
    delete menu;
    hide();
    delete ico;
}

void Tray::init(){
    initmenu();
    inittray();
    initScr();
}

void Tray::inittray(){
    ico->setIcon(QIcon(icoPath));               //设定托盘图标
    ico->setToolTip(TrayTitle);                        //提示文字
    ico->setContextMenu(menu);
    ico->hide();
}

void Tray::initmenu(){
    list[0] = new QAction(menu1);
    list[1] = new QAction(menu2);
    list[1]->setData(1);
    list[2] = new QAction(menu3_1);
    list[2]->setData(1);
    list[3] = new QAction(menu4);
    list[4] = new QAction(menu5);
    for (int i = 0; i < 5;++i) {
        menu->addAction(list[i]);
    }
    connect(list[0], SIGNAL(triggered(bool)), this, SLOT(menuOpen()));
    connect(list[1], SIGNAL(triggered(bool)), this, SLOT(menuVolume()));
    connect(list[2], SIGNAL(triggered(bool)), this, SLOT(menuState()));
    connect(list[3], SIGNAL(triggered(bool)), this, SLOT(menuAbout()));
    connect(list[4], SIGNAL(triggered(bool)), this, SLOT(menuExit()));
}

void Tray::initScr(){
    volumScr->setFixedSize(40, 150);
    QLibrary dll("getScreenInformation");
    dll.load();
    getScreenInformation* pcMag= ((getScreenInformation * (*)())
        (dll.resolve("getClassobj")))();
    QPoint workSize = pcMag->getWid_workSize();
    delete pcMag;
    dll.unload();
    volumScr->move((workSize.x() - volumScr->width()),
        (workSize.y() - volumScr->height()));
    volumScr->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    volumScr->setStyleSheet("background-color: rgb(0, 0, 0);");

    scr->setGeometry(10, 10, 20, 100);
    scr->setMaximum(100);
    scr->setMinimum(0);
    scr->setPageStep(10);
    scr->setValue(100);
    scr->setTracking(false);

    volumeico->setGeometry(10, 120, 20, 20);
    volumScr->hide();
}

void Tray::connects(){
    connect(scr, &QSlider::valueChanged,this,&Tray::setVolumFish);
    connect(ico, &QSystemTrayIcon::activated, this, &Tray::eventHandler);
}

void Tray::setVolumFish(){
    if (scr->value() != 0) {
        vIcoState = true;
        changeScrIco();
    }
    emit setVolumeToDesk(scr->value());
}

void Tray::changeScrIco(){
    if (!vIcoState || oldVolume == 0) {
        QImage img(muteIco);
        img = img.scaled(20, 20, Qt::KeepAspectRatio);
        volumeico->setPixmap(QPixmap::fromImage(img));
        vIcoState = false;
    }
    else {
        QImage img(volumeIco);
        img = img.scaled(20, 20, Qt::KeepAspectRatio);
        volumeico->setPixmap(QPixmap::fromImage(img));
        vIcoState = true;
    }
}

void Tray::show(){
    ico->show();
}

void Tray::hide(){
    ico->hide();
}

void Tray::menuVolume() {
    volumeico->installEventFilter(this);
    QTimer::singleShot(10, this, [=]() {
        volumScr->show();
        });
    loop->exec();
}

void Tray::menuState(){
    if (list[2]->data() == 1) {
        emit stateToDesk(0);//暂停播放
        list[2]->setText(menu3_0);
        list[2]->setData(0);
    }  
    else {
        emit stateToDesk(1);//继续
        list[2]->setText(menu3_1);
        list[2]->setData(1);
    }
}

void Tray::menuAbout(){
    if (about == nullptr) {
        about = new About;
    }
    delete about;
    about = nullptr;
}

void Tray::menuExit(){
    hide();
    emit mainExit();
}

void Tray::setVolume(int volume){
    show();
    oldVolume = volume;
    scr->setValue(volume);
    changeScrIco();
}

void Tray::setState(){
    list[2]->setText(menu3_1);
    list[2]->setData(1);
}

void Tray::eventHandler(QSystemTrayIcon::ActivationReason reason){
    if (reason == QSystemTrayIcon::DoubleClick) {
        menuOpen();
    }
}

bool Tray::eventFilter(QObject* object, QEvent* event){
    if (object == volumeico) {
        if (event->type() == QEvent::MouseButtonPress){
            vIcoState = !vIcoState;
            changeScrIco();
            if (vIcoState) {
                scr->setValue(oldVolume);
                emit setVolumeToDesk(oldVolume);
            }
            else {
                oldVolume = scr->value();
                emit setVolumeToDesk(0);
            }
        return true;
        }
    }
    if (event->type() == QEvent::MouseButtonPress) {        //点击任意处关闭音量调节
        QObject* op = object;
        volumScr->hide();
        volumeico->removeEventFilter(this);             //关闭事件过滤
        loop->exit();
        return true;
    }
    return QObject::eventFilter(object, event);
}

void Tray::menuOpen() {
    emit ShowMW();
    hide();
}