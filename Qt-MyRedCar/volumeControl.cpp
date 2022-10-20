/*
*
* 创建日期：2022.06.23
* 最后一次修改日期：2022.06.23
* 作者：寐晴下星辰
*
*/
#include "VolumeControl.h"

VolumeControl::VolumeControl(){
    ui.setupUi(this);
    this->setFixedSize(40, 150);
    QRect clientRect = QApplication::desktop()->availableGeometry();
    this->move((clientRect.width() - width()),
        (clientRect.height() - height()));
    setWindowFlags(Qt::FramelessWindowHint
        | Qt::Tool);
    //ui.widget->setWindowFlags(Qt::FramelessWindowHint |Qt::Popup);

    loop = new QEventLoop(ui.widget);
    oldVolume = ui.verticalSlider->value();
    //ui.widget->hide();

    ui.label->installEventFilter(this);
    ui.widget->installEventFilter(this);

}

VolumeControl::~VolumeControl(){

}

void VolumeControl::showa(){
    show();
    //ui.widget-> show();
    loop->exec();
    int op = 2;
}

void VolumeControl::setVolume(int value){
    if (value == 0) {
        QImage img(":/QtMyRedCar/Mute");
        img = img.scaled(20, 20, Qt::KeepAspectRatio);
        ui.label->setPixmap(QPixmap::fromImage(img));
        ui.verticalSlider->setValue(0);
        state = false;
    }
    else {
        QImage img(":/QtMyRedCar/volume");
        img = img.scaled(20, 20, Qt::KeepAspectRatio);
        ui.label->setPixmap(QPixmap::fromImage(img));
        ui.verticalSlider->setValue(value);
        state = true;
    }
}

void VolumeControl::initState(float volume, bool state){
    state = state;
    setVolume(volume*100);
}


bool VolumeControl::eventFilter(QObject* object, QEvent* event) {
    if (object == ui.label) {
        if (event->type() == QEvent::MouseButtonPress) {
            if (state) {
                oldVolume = ui.verticalSlider->value();
                setVolume(0);
                emit setVideoVolume(0);
            }
            else{
                setVolume(oldVolume);
                emit setVideoVolume(float(oldVolume) / 100);
            }
            return true;
        }
    }
    return QObject::eventFilter(object, event);
}