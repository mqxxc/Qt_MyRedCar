/*
*
* 创建时间：2022.04.xx
* 最后一次修改日期：2022.06.17
* 作者：寐晴下星辰
* 
*/
#include<QWidget>               //基本窗口类
#include<QEvent>                //qt事件类
#include<QMouseEvent>           //移动事件类
#include"Elastic.h"

#define ELASTIC_H
#include"macro.h"


Elastic::Elastic(QWidget* parent) {
    initSubstitute();   //初始化替身窗口样式
    //初始化变量
    state = 0;
    keyDown = false;                                 
    isMove = false;                                    
    isShow = false;
    mywid = parent;
    //对要管理的窗口进行基本设置
    parent->installEventFilter(this);                        //安装事件过滤器
    parent->setAttribute(Qt::WA_Hover, true);                //开启悬停事件
}

Elastic::~Elastic(){
    mywid->removeEventFilter(this);  //关闭事件过滤
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
        if (state&8) {//含有向左拉伸的向量
            temp_point = fimp.topLeft();
            if (fimp.bottomRight().y() - p.y() > minh) {
                temp_point.setY(p.y());
            }
            else {
                temp_point.setY(fimp.bottomRight().y() - minh);
            }
            fimp.setTopLeft(temp_point);
        }
        if (state&4) {//含有向右拉伸的向量
            temp_point = fimp.bottomLeft();
            if (p.y() - fimp.topRight().y() > minh) {
                temp_point.setY(p.y());
            }
            else {
                temp_point.setY(fimp.bottomRight().y() + minh);
            }
            fimp.setBottomLeft(temp_point);
        }
        if (state&2) {//含有向下拉伸的向量
            temp_point = fimp.topLeft();
            if (fimp.bottomRight().x() - p.x() > minw) {
                temp_point.setX(p.x());
            }
            else {
                temp_point.setX(fimp.bottomRight().x() - minw);
            }
            fimp.setTopLeft(temp_point);
        }
        if (state&1) {//含有向上拉伸的向量
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
        if (isMove) {          //判断鼠标是否位于标题栏
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
        if (lastPoint.y() < titleH) {//鼠标在标题栏处按下
            isShow = true;
            isMove = (state == 0);
        }
        if (state != 0) {//含有任意拉伸的向量
            isShow = true;
        }
        if (isShow) {//显示替身窗口
            substitute->setGeometry(mywid->geometry());
            substitute->show();
        }
        keyDown = true;
    }
}

void Elastic::mouseReleaseEventHandler(QMouseEvent* e) {
    if (e->button() == Qt::LeftButton) {
        keyDown =      //按键松开
            isMove= false;       //更正移动状态
        if (isShow) {       //替身窗口显示
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
    //设置为无边框窗口
    substitute->setWindowFlags(Qt::FramelessWindowHint| Qt::Tool);
    //设置背景颜色
    substitute->setStyleSheet("background-color:rgb(85, 255, 255);");
    //设置透明度
    substitute->setWindowOpacity(0.7);
}