#include "awaken_source.h"
#include<QtRemoteObjects/QRemoteObjectNode>
#include <QtRemoteObjects/QRemoteObjectHost>

void Awaken_source::awaken(){
	emit awaken_sig();
}


//Server
Server::Server(QWidget* parent) {
    m_pHost = new QRemoteObjectHost(this);
    m_pHost->setHostUrl(QUrl("local:qtmyredcar"));
    m_pInterface = new Awaken_source();
    m_pHost->enableRemoting(m_pInterface);

    connect(m_pInterface, &Awaken_source::awaken_sig, this, &Server::sendAwaken);
}

Server::~Server(){
    delete m_pInterface;
    delete m_pHost;
}

void Server::sendAwaken(){
    emit awaken();
}