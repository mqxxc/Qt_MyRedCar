/*
*
* �������ڣ�2022.05.xx
* ���һ���޸����ڣ�2022.08.06
* ���ߣ��������ǳ�
*
*/
#include"ui_unit.h"
#include"Unit.h"
#include<QMouseEvent>
#include<QMenu>
#include"DataHandle.h"

#define UNIT_H
#include"macro.h"	


Unit::Unit(Msg* rc,int id, QWidget* parent){
    //��ʼ����������
    ui = new Ui::Unit;
    ui->setupUi(this);
    if (parent != Q_NULLPTR) {
        this->setParent(parent);
    }
    this->rc = rc;
    this->id = id;
    
    //������ʼ��
    initMember();                     //��ʼ����������
    setWid_W();                       //��ʼ�����ڴ�С
    initUi();                         //��ʼ����������
    initR_Menu();                     //��ʼ���Ҽ��˵�
}

void Unit::setWid_W(){
    this->resize(QSize(widW, widW));
    ui->ico->setGeometry(0,0, widW, widW);
    int texth = widW / 4 * 3;
    ui->text->setGeometry(0, texth, widW, widW-texth);
    ui->input->setGeometry(0, texth, widW, widW - texth);
}

void Unit::initR_Menu(){
    //�˵��б�
    menuList[0]=new QAction(menuRN, this);
    if (rc->getLove()) {
        menuList[1] = new QAction(menuNL, this);
        menuList[1]->setData(1);
    }
    else{
        menuList[1] = new QAction(menuIL, this);
        menuList[1]->setData(0);
    }
    menuList[2]=new QAction(menuDe, this);
    rMenu->addAction(menuList[0]);
    rMenu->addAction(menuList[1]);
    rMenu->addAction(menuList[2]);
    connect(menuList[0], SIGNAL(triggered(bool)), this, SLOT(menuRename(bool)));
    connect(menuList[1], SIGNAL(triggered(bool)), this, SLOT(menuIsLove(bool)));
    connect(menuList[2], SIGNAL(triggered(bool)), this, SLOT(menuDelete(bool)));
}

void Unit::initUi() {
//��ʼ������
    this->setWindowFlags(Qt::FramelessWindowHint);      //����Ϊ�ޱ߿򴰿�

//��ʼ���ı������
    ui->text->setTextColor(QColor(255, 255, 255));                   //��ɫ����
    ui->text->setContextMenuPolicy(Qt::NoContextMenu);               //ȡ���Ҽ��˵�
    ui->text->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);    //�޻���

//��������������
    ui->input->hide();                                               //��ʼ״̬Ϊ����
    ui->input->setContextMenuPolicy(Qt::NoContextMenu);              //��������Ҽ��˵�
    ui->input->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);  //����򴰿ڱ��

//�����ı�ͼ��
    ui->text->setText(rc->getName());
    QPixmap pixmapPic(photo);
    QPixmap pixmapPicFit = pixmapPic.scaled(this->width(), this->width(),
        Qt::IgnoreAspectRatio);
    ui->ico->setPixmap(pixmapPicFit);

//����Ĭ�ϲ���
    onRelease();                                //Ĭ�ϲ�ѡ��
}

void Unit::initMember(){
    rMenu = new QMenu(this);
    menuList = new QAction * [3];
    photo = exePath + datePath + rc->getPhoto();
    input_loop = new QEventLoop(ui->input);
}

Unit::~Unit(){
    for (int i=0;i<3;++i){
        delete menuList[i];
    }
    delete menuList;
    delete rMenu;
    if (input_loop != nullptr) {
        delete input_loop;
    }
    this->disconnect();
    delete ui;
}

void Unit::setScaling(float appScaling){
    //scaling = appScaling;
    widW = initw / appScaling;
}

int Unit::getWid_W(){
    return widW;
}

void Unit::onSelect(){
    ui->ico->setStyleSheet("border:4px solid rgb(0, 255, 255);"
        " border-radius:25px;");
}

void Unit::onRelease(){
    ui->ico->setStyleSheet("border:2px solid rgb(240, 242, 245);"
        " border-radius:25px; ");
}

int Unit::getUnit_Id(){
    return selectId;
}

void Unit::setExe_Path(QString path){
    exePath = path;
}

void Unit::menuFinish(){
    input_loop->exit();
    /*delete input_loop;
    input_loop = nullptr;*/
    QString name = ui->input->toPlainText();
    if (!name.isEmpty()) {
        if (name.compare(rc->getName())!=0) {
            ui->text->setText(name);
            emit rename_sig(id, name);
            up_UnitPath(name);
        }
    }
    ui->input->hide();
    ui->input->removeEventFilter(this);
}

void Unit::up_UnitPath(QString name){
    rc->setName(name);
    rc->setVideo(name);
    rc->setPhoto(name);
    photo = exePath + datePath + rc->getPhoto();
    //this->name = name;
    /*QString left = photo.left(photo.lastIndexOf("/"));
    left = left.left(left.lastIndexOf("/"));
    QString right = photo.right(photo.size()-photo.lastIndexOf(".")+1);
    photo = left +"/" + name+ "/"+name + right;*/
}

void Unit::mousePressEvent(QMouseEvent* ev){
    if (ev->button() == Qt::RightButton) {
        rMenu->move(ev->globalPos());
        rMenu->show();
        return;
    }
    if (ev->button() == Qt::LeftButton) {
        int oldId = selectId;
        selectId = id;
        emit upUnits(oldId);
        onSelect();
        return;
    }
}

bool Unit::eventFilter(QObject* object, QEvent* event) {
    if (object == ui->input) {
        if (event->type() == QEvent::KeyPress) {            //�س������������
            QKeyEvent* e = static_cast <QKeyEvent*> (event);
            if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) {
                menuFinish();
                return true;
            }
        }
    }
    if (event->type() == QEvent::MouseButtonPress) {        //������⴦���������
        menuFinish();
        return true;
    }
    return QObject::eventFilter(object, event);
}

void Unit::menuRename(bool b){
    Q_UNUSED(b)
    ui->input->installEventFilter(this);                             //��װ�¼�������
    //������
    ui->input->setText(ui->text->toPlainText());
    ui->input->move(ui->text->mapToGlobal(QPoint(0, 0)));
    ui->input->show();
    ui->input->activateWindow();                         //����Ϊ���㴰��
    input_loop->exec();
}

void Unit::menuIsLove(bool b){
    Q_UNUSED(b)
    //�Ƿ�ϲ��
    if (menuList[1]->data() == 0) {
        rc->setLove(true);
        menuList[1]->setText(menuNL);
        menuList[1]->setData(1);
    }
    else {
        rc->setLove(false);
        menuList[1]->setText(menuIL);
        menuList[1]->setData(0);
    }
}

void Unit::menuDelete(bool b) {
    Q_UNUSED(b)
    this->close();
    emit delete_sig(id);
}

int Unit::widW = 120;
//float Unit::scaling = 1;
int Unit::selectId = -1;
QString Unit::exePath = "";

//bool Unit::event(QEvent* event){
//   /* if (event->type() == QEvent::MouseButtonDblClick){
//        return true;
//    }*/
//    return QWidget::event(event);
//}