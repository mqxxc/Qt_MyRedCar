/*
* 
* DeskVideo������Ƶ������
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
	int volume;				//����
	QWidget* deskwinv;		//��Ƶ�㴰��
	QLibrary* dll;			//dll��
	playVideo* player;		//������
	QString vPath;			//������Ƶ��·��

public:
	DeskVideo();
	~DeskVideo();
	bool replaceDesk(QString videoPath);						//�滻����
	void setVolume(float volume);								//��������

private:
	void saveseting();		//����������Ϣ
	bool redsavedata();		//��ȡ������Ϣ 

signals:
	void noVideo();						//��ʼ��ʱ����Ƶ�����ź�
	void trayShow(float volume);		//������ʾ�ź�
	void loadFinish();					//��ʼ���������ź�

public slots:
	void stopOrStart(int state);		//��ͣ���߿�ʼ����
};