#pragma once
#include<QWidget>


class Elastic :public QWidget {
	Q_OBJECT

protected:
    QWidget* substitute;                            //替身窗口
    QWidget* mywid;                                 //要处理事件的窗口
    char state;                                     //鼠标对于窗口的位置
    /* state说明:
    *xxxx 1代表在此位置，
    *1.上 2.下 3.左 4.右
    */
    bool keyDown;                                  //鼠标左键是否被按下
    /*true：按下，false：没有按下*/
    bool isMove;                                   //鼠标能否带动窗口移动
    /*true：允许移动，false：不允许移动*/
    bool isShow;                                   //替身窗口是否显示
    /*允许显示替身窗口，false：不允许显示替身窗口*/
    QPoint point;                                  //鼠标对于窗口位置
    QPoint currentPoint;                           //鼠标对于屏幕的位置
    QPoint lastPoint;                              //窗口左上角对于桌面的坐标
    int titleH;                                    //标题栏高度

public:
	Elastic(QWidget* parent = Q_NULLPTR);
	~Elastic();

    void setTitleH(int h);                           //设置窗口高


protected:
    void upMouseIco();                              //更新鼠标图标
    void isEdge(QPoint point, QRect rect);          //判断鼠标是否靠窗口边上停靠
    void upWidSize(QPoint);                         //根据拖拽值更新窗口大小      
    void mouseHoverEventHandler(QHoverEvent* e);    //鼠标停靠窗口
    void mouseMoveEventHandler(QMouseEvent* e);     //鼠标移动
    void mousePressEventHandler(QMouseEvent* e);    //鼠标被按下
    void mouseReleaseEventHandler(QMouseEvent* e);  //鼠标被松开
    bool eventFilter(QObject* obj, QEvent* e);      //事件过滤器
    void initSubstitute();                          //初始化替身
};