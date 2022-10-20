#pragma once
#include<QObject>
#include<QSystemTrayIcon>
class QMenu;
class About;
class QSlider;
class QLabel;
class QEventLoop;
class QAction;
#pragma execution_character_set("utf-8")

class Tray :public QObject{

	Q_OBJECT

private:
	QSystemTrayIcon* ico;							//托盘类实例
	QMenu* menu;									//托盘菜单
	QAction** list;									//菜单项
	About* about;									//关于窗口

	QWidget* volumScr;								//音量条		
	int oldVolume;									//静音前设置的音量
	QEventLoop* loop;								//事件循环
	QSlider* scr;									//音量调节部件
	QLabel* volumeico;								//音量设置ico部件
	/*false----静音状态，true-----非静音状态*/
	bool vIcoState;									//音量设置ico状态


public:
	Tray();
	~Tray();

	void show();									//显示托盘
	void hide();									//隐藏托盘


private:
	void init();									//总初始化函数
	void inittray();								//初始化托盘
	void initmenu();								//初始化菜单
	void initScr();									//初始化音量条
	void connects();								//建立联系
	void setVolumFish();							//音量设置完成
	void changeScrIco();

signals:
	void setVolumeToDesk(float value);				//设置壁纸音量
	void stateToDesk(int state);					//暂停或者开始播放视频
	void mainExit();								//主程序退出
	void ShowMW();									//主窗口显示

public slots:
	void eventHandler(QSystemTrayIcon::
		ActivationReason reason);						//事件处理
	bool eventFilter(QObject* object, QEvent* event);   //子控件事件监听器

	//菜单对应的动作
	void menuOpen();								//打开							
	void menuVolume();								//设置声音
	void menuState();								//设置视频播放状态
	void menuAbout();								//关于
	void menuExit();								//退出

	void setVolume(int volume);						//设置音量
	void setState();								//设置视频播放状态
};