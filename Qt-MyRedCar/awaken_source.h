/*
* 
*Awaken_source服务与客户端链接实现类
*Server服务端类
* 
*/
#pragma once
#include"rep_awaken_source.h"

//class QRemoteObjectNode;
class QRemoteObjectHost;


class Awaken_source :public awakenSource {
	Q_OBJECT

public:
	virtual void awaken();          //唤醒时发射唤醒信号

signals:
	void awaken_sig();              //唤醒信号
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
    void awaken();                  //唤醒信号

private slots:
    void sendAwaken();              //发送唤醒信号
};