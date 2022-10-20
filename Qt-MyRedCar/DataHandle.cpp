#include"DataHandle.h"
#include<QLibrary>
#include<QDateTime>
#define DATAHANDLE_H
#include"macro.h"
#include"../SaveOrRead/SaveOrRead.h"
#pragma execution_character_set("utf-8")

DetaHandle::DetaHandle(){
	readMsg();
}

DetaHandle::~DetaHandle(){
	saveMsg();
	while (!database.empty()) {
		auto it = database.begin();
		Msg* btn = it.value();
		if (btn != nullptr) {
			delete btn;
			btn = nullptr;
		}
		database.erase(database.begin());
	}
}

void DetaHandle::addData(QString fileNmae,bool success){
	fileNmae=fileNmae.right(fileNmae.size()-fileNmae.lastIndexOf("/")-1);
	fileNmae = fileNmae.left(fileNmae.lastIndexOf("."));
	database.insert(database.size(), new Msg(fileNmae,
			QDateTime::currentDateTime().toString("yyyy-MM-dd"), success));
}

void DetaHandle::addData(Msg* msg){
	database.insert(database.size(), msg);
}

void DetaHandle::deleteData(char id){
	delete database[id];
	database[id] = nullptr;
	database.remove(id);
}

//void DetaHandle::updataData(char id, Term term, QString newValue){
//	switch (term){
//	case Term::NMAE: {
//		database[id]->setName(newValue);
//	}break;
//	case Term::PHOTO: {
//		database[id]->setPhoto(newValue);
//	}break;
//	case Term::VIDEO: {
//		database[id]->setVideo(newValue);
//	}break;
//	case Term::USETIME: {
//		database[id]->setUse_time(newValue);
//	}break;
//	case Term::LOVE: {
//		database[id]->setLove(newValue.toInt());
//	}break;
//	case Term::HIDE: {
//		database[id]->setHide(newValue.toInt());
//	}break;
//
//	default:
//		break;
//	}
//}

Msg* DetaHandle::getData(char id){
	return database.value(id);
}

int DetaHandle::getNum(){
	return database.size();
}

void DetaHandle::refresh(bool state){
	QList<Msg*>datas=database.values();
	QList<Msg*>::iterator STL;
	for (auto& ti:datas) {
		ti->setHide(state);
	}
}

void DetaHandle::saveMsg(){
	QList<Msg*> list = database.values();
	QList<Msg*>::const_iterator STL;
	QList<QString> datas;
	for (STL = list.constBegin(); STL!= list.constEnd();++STL) {
		datas.append((*STL)->getName());
		datas.append((*STL)->getVideo(true));
		datas.append((*STL)->getPhoto(true));
		datas.append((*STL)->getImport_time());
		datas.append((*STL)->getSource());
		datas.append((*STL)->getUse_time());
		datas.append(QString::number((*STL)->getState()));
	}
	QLibrary saveDll("SaveOrRead") ;
	if (saveDll.load()) {
		SaveOrRead* saveFile = ((SaveOrRead *(*)(QString,QList<QString>*))
			(saveDll.resolve("getSOR")))(recordPath,&datas);
		saveFile->saveFile();
		delete saveFile;
		saveDll.unload();
	}
}

void DetaHandle::readMsg(){
	QList<QString> datas;
	QLibrary readDll("SaveOrRead");
	if (readDll.load()) {
		SaveOrRead* readFile = ((SaveOrRead * (*)(QString, QList<QString>*))
			(readDll.resolve("getSOR")))(recordPath, &datas);
		if (readFile->pathExist()) {
			readFile->readFile();
			QList<QString> dat=datas;
			char num = 0;
			QList<QString>::const_iterator STL;
			for (STL = datas.constBegin(); STL != datas.constEnd();++STL) {
				QString name = *STL;
				QString video = *(++STL);
				QString photo = *(++STL);
				QString importTime = *(++STL);
				QString soure = *(++STL);
				QString useTime = *(++STL);
				QString state = *(++STL);
				database.insert(num++, new Msg(name,video,photo,
					importTime,soure,useTime,state));
			}
		}
		delete readFile;
		readDll.unload();
	}
}

Msg::Msg(QString name, QString video, QString photo, QString importTime,
	QString source, QString useTime, QString state){
	this->name = name;
	this->video = video;
	this->photo = photo;
	this->importTime = importTime;
	switch (source.toInt()){
	case 0: {
		this->source = Source::CRAFT;
	}break;
	case 1: {
		this->source = Source::LOCAL;
	}break;
	case 2: {
		this->source = Source::INTERNET;
	}break;
	default:
		break;
	}
	this->useTime = useTime;
	this->state = state.toInt();
}

Msg::Msg(QString fileName,QString time,bool success){
	name = fileName;
	video = fileName;
	success ? photo = fileName : photo = dePhotoPath;
	time.isEmpty() ? importTime = defImTime : importTime = time;
	useTime = deusedTime;
	source = Source::LOCAL;
	state = 0;
}

Msg::Msg(QString fileName, QString videoNmae, QString photoName,
	QString time,bool success){
	name = fileName;
	video = videoNmae.left(videoNmae.lastIndexOf("."));
	success ? photo =  photoName.left(photoName.lastIndexOf(".")) : photo = dePhotoPath;
	time.isEmpty() ? importTime = defImTime : importTime = time;
	useTime = deusedTime;
	source = Source::LOCAL;
	state = 0;
}

QString Msg::getName(){
	return name;
}

QString Msg::getPhoto(bool save){
	if (save) {
		return photo;
	}
	return name+"/"+photo+dePhotoS;
}

QString Msg::getVideo(bool save){
	if (save) {
		return video;
	}
	return name + "/"+video+deVideoS;
}

QString Msg::getImport_time(){
	return importTime;
}

QString Msg::getSource(){
	return QString::number(state);
}

QString Msg::getUse_time(){
	return useTime;
}

bool Msg::getLove(){
	return state&1;
}

bool Msg::isHide(){
	return state&2;
}

char Msg::getState(){
	return state;
}

void Msg::setName(QString name){
	this->name = name;
}

void Msg::setPhoto(QString path){
	photo = path;
}

void Msg::setVideo(QString path){
	video = path;
}

void Msg::setImport_time(QString time){
	importTime = time;
}

void Msg::setUse_time(QString time){
	useTime = time;
}

void Msg::setSource(Source source){
	this->source = source;
}

void Msg::setLove(bool value){
	if (value) {
		state |= stateSig_N&1;
	}
	else{
		state &= stateSig_N^1;
	}
}

void Msg::setHide(bool value){
	if (value) {
		state |= stateSig_N&2;
	}
	else {
		state &= stateSig_N^2;
	}
}
