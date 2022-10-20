/*
* 
*Awaken_source������ͻ�������ʵ����
*Server�������
* 
*/
#pragma once
#include"rep_awaken_source.h"

//class QRemoteObjectNode;
class QRemoteObjectHost;


class Awaken_source :public awakenSource {
	Q_OBJECT

public:
	virtual void awaken();          //����ʱ���份���ź�

signals:
	void awaken_sig();              //�����ź�
};


class Server : public QObject{
    Q_OBJECT

private:
    Awaken_source* m_pInterface ;
    QRemoteObjectHost* m_pHost;

public:
    explicit Server(QWidget* parent = nullptr);
    ~Server();

signals:
    void awaken();                  //�����ź�

private slots:
    void sendAwaken();              //���ͻ����ź�
};