#pragma once
#include<QWidget>


class Elastic :public QWidget {
	Q_OBJECT

protected:
    QWidget* substitute;                            //������
    QWidget* mywid;                                 //Ҫ�����¼��Ĵ���
    char state;                                     //�����ڴ��ڵ�λ��
    /* state˵��:
    *xxxx 1�����ڴ�λ�ã�
    *1.�� 2.�� 3.�� 4.��
    */
    bool keyDown;                                  //�������Ƿ񱻰���
    /*true�����£�false��û�а���*/
    bool isMove;                                   //����ܷ���������ƶ�
    /*true�������ƶ���false���������ƶ�*/
    bool isShow;                                   //�������Ƿ���ʾ
    /*������ʾ�����ڣ�false����������ʾ������*/
    QPoint point;                                  //�����ڴ���λ��
    QPoint currentPoint;                           //��������Ļ��λ��
    QPoint lastPoint;                              //�������ϽǶ������������
    int titleH;                                    //�������߶�

public:
	Elastic(QWidget* parent = Q_NULLPTR);
	~Elastic();

    void setTitleH(int h);                           //���ô��ڸ�


protected:
    void upMouseIco();                              //�������ͼ��
    void isEdge(QPoint point, QRect rect);          //�ж�����Ƿ񿿴��ڱ���ͣ��
    void upWidSize(QPoint);                         //������קֵ���´��ڴ�С      
    void mouseHoverEventHandler(QHoverEvent* e);    //���ͣ������
    void mouseMoveEventHandler(QMouseEvent* e);     //����ƶ�
    void mousePressEventHandler(QMouseEvent* e);    //��걻����
    void mouseReleaseEventHandler(QMouseEvent* e);  //��걻�ɿ�
    bool eventFilter(QObject* obj, QEvent* e);      //�¼�������
    void initSubstitute();                          //��ʼ������
};