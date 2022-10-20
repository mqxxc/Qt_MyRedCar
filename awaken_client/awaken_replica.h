#pragma once
#include<QObject>
class awakenReplica;
class QRemoteObjectNode;

class awaken_replica :public QObject{

	Q_OBJECT

private:
	awakenReplica* ptr;
	QRemoteObjectNode* remoteNode;

public:
	awaken_replica(QObject* p = nullptr);
	~awaken_replica();

	void sendAwaken();
};