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
    QMediaPlayer* player;                   //播放器
    QVideoWidget* video;                    //播放窗口
    QMediaPlaylist* list;                   //播放列表

public:
    virtual void setVideo(QString vpath);           //设置要播放的媒体
    virtual void flyVideo();                        //播放视频
    virtual void setVolume(int volume);             //设置音量
    virtual void stopPlay();                        //停止播放并删除媒体缓存
    virtual void pauseVideo();                      //暂停播放
    virtual void startVideo();                      //继续播放

private slots:
    void getduration(qint64 playtime);              //获取播放时长
    void refreshLoop();                             //刷新视频播放位置
};

extern "C" PLAYVIDEO_EXPORT playVideo* getpvobj(QWidget * parent);
