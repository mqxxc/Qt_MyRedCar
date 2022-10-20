#pragma once
#include"ui_set.h"
class QEventLoop;

class Set:public QWidget {

	Q_OBJECT

private:
	Ui::Set* ui;						//ui����
	QEventLoop* loop;					//�¼�ѭ��
	unsigned int value;					//���õ�ֵ
	/*
	* ���õ�ֵ
	*1 ������
	*2 ������������1��������
	*/
	unsigned int oldValue;				//�ɵ����õ�ֵ

public:
	Set(QObject* parent=Q_NULLPTR);
	~Set();

private:
	void initOption();					//��ʼ�����а�ť��״̬
		
	void saveData();					//�������õ�ֵ������
	void readData();					//��ȡ��������

	void svaeSetMsg();					//�����޸ĵ�����
	void reviseSet(unsigned int value);	//������޸Ĳ���

	void setSelf_start(bool state);		//���ÿ�������

	
private slots:
	void on_ok_clicked();				//ȷ����ť��Ӧ�ۺ���
	void on_close_clicked();			//ȡ����ť��Ӧ�ۺ���
	void closeEvent(QCloseEvent* e);	//����ر��¼�
};