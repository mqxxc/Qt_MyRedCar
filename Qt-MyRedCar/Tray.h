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
	QSystemTrayIcon* ico;							//������ʵ��
	QMenu* menu;									//���̲˵�
	QAction** list;									//�˵���
	About* about;									//���ڴ���

	QWidget* volumScr;								//������		
	int oldVolume;									//����ǰ���õ�����
	QEventLoop* loop;								//�¼�ѭ��
	QSlider* scr;									//�������ڲ���
	QLabel* volumeico;								//��������ico����
	/*false----����״̬��true-----�Ǿ���״̬*/
	bool vIcoState;									//��������ico״̬


public:
	Tray();
	~Tray();

	void show();									//��ʾ����
	void hide();									//��������


private:
	void init();									//�ܳ�ʼ������
	void inittray();								//��ʼ������
	void initmenu();								//��ʼ���˵�
	void initScr();									//��ʼ��������
	void connects();								//������ϵ
	void setVolumFish();							//�����������
	void changeScrIco();

signals:
	void setVolumeToDesk(float value);				//���ñ�ֽ����
	void stateToDesk(int state);					//��ͣ���߿�ʼ������Ƶ
	void mainExit();								//�������˳�
	void ShowMW();									//��������ʾ

public slots:
	void eventHandler(QSystemTrayIcon::
		ActivationReason reason);						//�¼�����
	bool eventFilter(QObject* object, QEvent* event);   //�ӿؼ��¼�������

	//�˵���Ӧ�Ķ���
	void menuOpen();								//��							
	void menuVolume();								//��������
	void menuState();								//������Ƶ����״̬
	void menuAbout();								//����
	void menuExit();								//�˳�

	void setVolume(int volume);						//��������
	void setState();								//������Ƶ����״̬
};