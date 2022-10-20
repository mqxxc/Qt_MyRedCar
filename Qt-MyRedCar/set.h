#pragma once
#include"ui_set.h"
class QEventLoop;

class Set:public QWidget {

	Q_OBJECT

private:
	Ui::Set* ui;						//ui界面
	QEventLoop* loop;					//事件循环
	unsigned int value;					//设置的值
	/*
	* 设置的值
	*1 ，保留
	*2 ，开机自启，1开机自启
	*/
	unsigned int oldValue;				//旧的设置的值

public:
	Set(QObject* parent=Q_NULLPTR);
	~Set();

private:
	void initOption();					//初始化所有按钮的状态
		
	void saveData();					//保存设置的值到本地
	void readData();					//读取本地设置

	void svaeSetMsg();					//保存修改的设置
	void reviseSet(unsigned int value);	//具体的修改操作

	void setSelf_start(bool state);		//设置开机自启

	
private slots:
	void on_ok_clicked();				//确定按钮响应槽函数
	void on_close_clicked();			//取消按钮响应槽函数
	void closeEvent(QCloseEvent* e);	//窗体关闭事件
};