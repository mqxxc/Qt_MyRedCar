#include "awaken_replica.h"
#include "rep_awaken_replica.h"
awaken_replica::awaken_replica(QObject* p) :QObject(p) {
	remoteNode = new QRemoteObjectNode(this);
	remoteNode->connectToNode(QUrl("local:qtmyredcar"));
	ptr = remoteNode->acquire<awakenReplica>();
}

awaken_replica::~awaken_replica(){
	if (ptr != nullptr) {
		delete ptr;
	}
}

void awaken_replica::sendAwaken(){
	ptr->awaken();
}