#pragma once
#include "playvideo_global.h"
#include<QObject>
class QWidget;
class QMediaPlayer;
class QVideoWidget;
class QMediaPlaylist;

class PLAYVIDEO_EXPORT playVideo:public QObject{

    Q_OBJECT

public:
    playVideo(QWidget* parent);
    virtual~playVideo();

private:
    QMediaPlayer* player;                   //������
    QVideoWidget* video;                    //���Ŵ���
    QMediaPlaylist* list;                   //�����б�

public:
    virtual void setVideo(QString vpath);           //����Ҫ���ŵ�ý��
    virtual void flyVideo();                        //������Ƶ
    virtual void setVolume(int volume);             //��������
    virtual void stopPlay();                        //ֹͣ���Ų�ɾ��ý�建��
    virtual void pauseVideo();                      //��ͣ����
    virtual void startVideo();                      //��������

private slots:
    void getduration(qint64 playtime);              //��ȡ����ʱ��
    void refreshLoop();                             //ˢ����Ƶ����λ��
};

extern "C" PLAYVIDEO_EXPORT playVideo* getpvobj(QWidget * parent);
