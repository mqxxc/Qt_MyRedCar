#pragma once
#include<QSlider>
#include<QDesktopWidget>
#include<QApplication>
#include"ui_VolumeControl.h"

class VolumeControl:public QWidget{

	Q_OBJECT

private:
	Ui::VolumeControl ui;
	int oldVolume;									//���õ�����
	bool state;
	QEventLoop* loop;

public:
	VolumeControl();
	~VolumeControl();
	void showa();

private:
	void setVolume(int value);

signals:
	void setVideoVolume(float);

public slots:
	bool eventFilter(QObject* object, QEvent* event);		 //�ӿؼ��¼�������

	void initState(float volume,bool state);
};