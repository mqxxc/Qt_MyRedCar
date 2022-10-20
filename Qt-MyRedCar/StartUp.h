#pragma once
class QProcess;
class Server;

#include"qtmyredcar.h"
#include"Tray.h"
#include"DeskVideo.h"


class StartUp : public QObject {

	Q_OBJECT

private:
	QtMyRedCar* mainwid;					//应用主窗口
	Tray* tray;								//托盘
	DeskVideo* desk;						//桌面视频类
	QApplication* app;						//事件循环实例
	QString exePath;						//程序运行路径
	float ration;							//电脑缩放比例
	QProcess* load;							//加载界面进程
	Server* srever;							//进程服务端

public:	
	StartUp();
	~StartUp();
	void setApp(QApplication* app);			//设置事件循环实例
	

private:
	void init();
	void initMember();
	void loading();
	void loadFinish();
	void getPcmag();						//调用dll获取屏幕信息
	void connectForMW();					//有关主窗口的信号联系
	void connectForOther();					//其他类的信号联系
	void exitToApp();						//结束事件循环退出应用					

signals:
	void appExit();

private slots:
	void mainWidDelete();					//主窗口销毁
	void mainWidNew();						//主窗口创建
	void mainWidShow();						//主窗口展示
	void mainAwaken();						//主窗口唤醒
	void awakenExe();						//重复启动唤醒主窗口
};