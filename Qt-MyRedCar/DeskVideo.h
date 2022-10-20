/*
* 
* DeskVideo桌面视频播放类
* 
*/
#pragma once
#include<QObject>
class playVideo;
class QLibrary;
#pragma execution_character_set("utf-8")

class DeskVideo:public QObject{

	Q_OBJECT

private:
	int volume;				//音量
	QWidget* deskwinv;		//视频层窗口
	QLibrary* dll;			//dll库
	playVideo* player;		//播放器
	QString vPath;			//播放视频的路径

public:
	DeskVideo();
	~DeskVideo();
	bool replaceDesk(QString videoPath);						//替换桌面
	void setVolume(float volume);								//设置音量

private:
	void saveseting();		//保存设置信息
	bool redsavedata();		//读取设置信息 

signals:
	void noVideo();						//初始化时无视频播放信号
	void trayShow(float volume);		//托盘显示信号
	void loadFinish();					//初始化完成完成信号

public slots:
	void stopOrStart(int state);		//暂停或者开始播放
};