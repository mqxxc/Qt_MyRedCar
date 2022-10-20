#pragma once
class QProcess;
class Server;

#include"qtmyredcar.h"
#include"Tray.h"
#include"DeskVideo.h"


class StartUp : public QObject {

	Q_OBJECT

private:
	QtMyRedCar* mainwid;					//Ӧ��������
	Tray* tray;								//����
	DeskVideo* desk;						//������Ƶ��
	QApplication* app;						//�¼�ѭ��ʵ��
	QString exePath;						//��������·��
	float ration;							//�������ű���
	QProcess* load;							//���ؽ������
	Server* srever;							//���̷����

public:	
	StartUp();
	~StartUp();
	void setApp(QApplication* app);			//�����¼�ѭ��ʵ��
	

private:
	void init();
	void initMember();
	void loading();
	void loadFinish();
	void getPcmag();						//����dll��ȡ��Ļ��Ϣ
	void connectForMW();					//�й������ڵ��ź���ϵ
	void connectForOther();					//��������ź���ϵ
	void exitToApp();						//�����¼�ѭ���˳�Ӧ��					

signals:
	void appExit();

private slots:
	void mainWidDelete();					//����������
	void mainWidNew();						//�����ڴ���
	void mainWidShow();						//������չʾ
	void mainAwaken();						//�����ڻ���
	void awakenExe();						//�ظ���������������
};