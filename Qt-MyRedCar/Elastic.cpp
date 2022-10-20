/*
*
* ����ʱ�䣺2022.04.xx
* ���һ���޸����ڣ�2022.06.17
* ���ߣ��������ǳ�
* 
*/
#include<QWidget>               //����������
#include<QEvent>                //qt�¼���
#include<QMouseEvent>           //�ƶ��¼���
#include"Elastic.h"

#define ELASTIC_H
#include"macro.h"


Elastic::Elastic(QWidget* parent) {
    initSubstitute();   //��ʼ����������ʽ
    //��ʼ������
    state = 0;
    keyDown = false;                                 
    isMove = false;                                    
    isShow = false;
    mywid = parent;
    //��Ҫ����Ĵ��ڽ��л�������
    parent->installEventFilter(this);                        //��װ�¼�������
    parent->setAttribute(Qt::WA_Hover, true);                //������ͣ�¼�
}

Elastic::~Elastic(){
    mywid->removeEventFilter(this);  //�ر��¼�����
    delete substitute;
}

void Elastic::setTitleH(int h){
    titleH = h;
}

void Elastic::upMouseIco() {
    switch (state) {
    case 0: {
        mywid->setCursor(Qt::ArrowCursor);
    }break;
    case 8:
    case 4: {
        mywid->setCursor(Qt::SizeVerCursor);
    }break;
    case 2:
    case 1: {
        mywid->setCursor(Qt::SizeHorCursor);
    }break;
    case 10:
    case 5: {
        mywid->setCursor(Qt::SizeFDiagCursor);
    }break;
    case 9:
    case 6: {
        mywid->setCursor(Qt::SizeBDiagCursor);
    }break;
    }
}

void Elastic::isEdge(QPoint point, QRect rect) {
    state &= 0;
    if (point.y() - rect.y() < mouse_sens) {
        state |= 8;
    }
    if (point.x() - rect.x() < mouse_sens) {
        state |= 2;
    }
    if (rect.y() + rect.height() - point.y() < mouse_sens) {
        state |= 4;
    }
    if (rect.x() + rect.width() - point.x() < mouse_sens) {
        state |= 1;
    }
}

void Elastic::upWidSize(QPoint p) {
    int minw = mywid->minimumWidth();
    int minh = mywid->minimumHeight();
    QRect fimp = substitute->geometry();
    QPoint temp_point;

    if (!state^0) {

    }
    else {
        if (state&8) {//�����������������
            temp_point = fimp.topLeft();
            if (fimp.bottomRight().y() - p.y() > minh) {
                temp_point.setY(p.y());
            }
            else {
                temp_point.setY(fimp.bottomRight().y() - minh);
            }
            fimp.setTopLeft(temp_point);
        }
        if (state&4) {//�����������������
            temp_point = fimp.bottomLeft();
            if (p.y() - fimp.topRight().y() > minh) {
                temp_point.setY(p.y());
            }
            else {
                temp_point.setY(fimp.bottomRight().y() + minh);
            }
            fimp.setBottomLeft(temp_point);
        }
        if (state&2) {//�����������������
            temp_point = fimp.topLeft();
            if (fimp.bottomRight().x() - p.x() > minw) {
                temp_point.setX(p.x());
            }
            else {
                temp_point.setX(fimp.bottomRight().x() - minw);
            }
            fimp.setTopLeft(temp_point);
        }
        if (state&1) {//�����������������
            temp_point = fimp.topRight();
            if (p.x() - fimp.bottomLeft().x() > minw) {
                temp_point.setX(p.x());
            }
            else {
                temp_point.setX(fimp.bottomLeft().x() + minw);
            }
            fimp.setTopRight(temp_point);
        }
    }
    substitute->setGeometry(fimp);
}

void Elastic::mouseHoverEventHandler(QHoverEvent* e) {
    if(!keyDown){
        point = mywid->mapToGlobal(e->pos());
        isEdge(point, mywid->frameGeometry());
        upMouseIco();
    }
}

void Elastic::mouseMoveEventHandler(QMouseEvent* e) {
    Q_UNUSED(e);

    if (keyDown) {
        currentPoint = e->globalPos();
        if (isMove) {          //�ж�����Ƿ�λ�ڱ�����
            QPoint tmp = currentPoint - lastPoint;
            substitute->move(tmp);
        }
        else if (state != 0) {
            upWidSize(currentPoint);  
        }
    }
}

void Elastic::mousePressEventHandler(QMouseEvent* e) {
    if (e->button() == Qt::LeftButton) {
        lastPoint = e->pos();
        if (lastPoint.y() < titleH) {//����ڱ�����������
            isShow = true;
            isMove = (state == 0);
        }
        if (state != 0) {//�����������������
            isShow = true;
        }
        if (isShow) {//��ʾ������
            substitute->setGeometry(mywid->geometry());
            substitute->show();
        }
        keyDown = true;
    }
}

void Elastic::mouseReleaseEventHandler(QMouseEvent* e) {
    if (e->button() == Qt::LeftButton) {
        keyDown =      //�����ɿ�
            isMove= false;       //�����ƶ�״̬
        if (isShow) {       //��������ʾ
            mywid->setGeometry(substitute->geometry());
            substitute->hide();
            isShow = false;
        }
    }
}

bool Elastic::eventFilter(QObject* obj, QEvent* e) {
    switch (e->type()) {
    case QEvent::HoverMove:
        mouseHoverEventHandler(static_cast<QHoverEvent*>(e));
        break;
    case QEvent::MouseMove:
        mouseMoveEventHandler(static_cast<QMouseEvent*>(e));
        break;
    case QEvent::MouseButtonPress:
        mousePressEventHandler(static_cast<QMouseEvent*>(e));
        break;
    case QEvent::MouseButtonRelease:
        mouseReleaseEventHandler(static_cast<QMouseEvent*>(e));
        break;
    default:
        return QObject::eventFilter(obj, e);
    }
    return true;
}

void Elastic::initSubstitute(){
    substitute = new QWidget();
    //����Ϊ�ޱ߿򴰿�
    substitute->setWindowFlags(Qt::FramelessWindowHint| Qt::Tool);
    //���ñ�����ɫ
    substitute->setStyleSheet("background-color:rgb(85, 255, 255);");
    //����͸����
    substitute->setWindowOpacity(0.7);
}