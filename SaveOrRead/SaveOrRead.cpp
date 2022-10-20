#include "SaveOrRead.h"
#include<QFile>
#include<QTextStream>
#include<QList>
#include<QCoreApplication>
#pragma execution_character_set("utf-8")

SaveOrRead::SaveOrRead(QString path, QList<QString>* list){
	this->path = QCoreApplication::applicationDirPath();;
	this->path +=('/'+ path);
	this->list=list;
}

SaveOrRead::~SaveOrRead(){

}

bool SaveOrRead::pathExist(){
	QFile file(path);
	if (!file.exists()) {
		return false;
	}
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return false;
	}
	if (file.readLine().isEmpty()) {
		return false;
	}
	file.close();
	return true;
}

void SaveOrRead::saveFile(){
	QFile file(path);
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream fileStream(&file);
	fileStream.seek(0);
	QList<QString>::const_iterator ti;
	for (ti = list->constBegin(); ti != list->constEnd();++ti) {
		fileStream << *ti << '\n';
	}
	file.close();
}

void SaveOrRead::readFile(){
	QFile file(path);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream fileStream(&file);
	fileStream.seek(0);
	while (!fileStream.atEnd()) {
		list->append(fileStream.readLine());
	}
	file.close();
}

SaveOrRead* getSOR(QString filePath, QList<QString>* list){
	return new SaveOrRead(filePath, list);
}