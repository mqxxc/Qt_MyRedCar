/*
*
* 创建日期：2022.06.15
* 最后一次修改日期：2022.07.25
* 作者：寐晴下星辰
*
*/
#include"Set.h"
#include<QFile>
#include<QLibrary>
#include<QSettings>
#include<QMessageBox>

#include"../SaveOrRead/SaveOrRead.h"
#include"../getScreenInformation/getScreenInformation.h"
#define SET_H
#include"macro.h"


Set::Set(QObject* parent):ui(new Ui::Set()){
	ui->setupUi(this);
	loop = new QEventLoop(this);
	oldValue= value = 0;
	initOption();
	
	this->setWindowIcon(QIcon(icoPath));
	this->show();
	loop->exec();
}

Set::~Set(){
	saveData();
	delete ui;
	delete loop;
}

void Set::saveData(){
	QLibrary dll("SaveOrRead");
	if (dll.load()) {
		QList<QString> list;
		list.append(QString::number(value));
		SaveOrRead* save = ((SaveOrRead * (*)(QString path, QList<QString>*list))
			(dll.resolve("getSOR")))(QString(initPath), &list);
		save->saveFile();
		delete save;
		dll.unload();
	}
}

void Set::readData(){
	QLibrary dll("SaveOrRead");
	if (dll.load()) {
		QList<QString> list;
		SaveOrRead* read = ((SaveOrRead * (*)(QString path, QList<QString>*list))
			(dll.resolve("getSOR")))(QString(initPath), &list);
		if (read->pathExist()) {
			read->readFile();
			oldValue = list[0].toUInt();
			value = oldValue;
		}
		delete read;
		dll.unload();
	}
}

void Set::initOption(){
	readData();
	if (value == 0) {
		return;
	}
	if (value & 1) {	//开机自启项
		ui->self_start->setChecked(true);
	}
}

void Set::svaeSetMsg(){
	if (ui->self_start->checkState() != Qt::Unchecked) {	//开机自启
		if (!(value & 2)) {
			value |= (2 & SeItemNum);
		}
	}
	else {
		if (value & 2) {
			value &= (2 ^ SeItemNum);
		}
	}

	
	reviseSet(value^oldValue);
	oldValue = value;
}

void Set::reviseSet(unsigned int value){
	//dxg思来想去觉得set应该放在dll中但是有信号以后在修改
	//设置开机自启，flag表示是否开机自启
	if (value & 2) {
		setSelf_start(this->value & 2);
	}
}

void Set::on_close_clicked(){
	this->close();
}

void Set::closeEvent(QCloseEvent* e){
	loop->quit();
}

void Set::setSelf_start(bool state){
	QLibrary dll("getScreenInformation");
	QString appName;
	QString appPath;
	if (dll.load()) {
		getScreenInformation* pcMsg = ((getScreenInformation * (*)())
			(dll.resolve("getClassobj")))();
		 appName= pcMsg->getName();
		 appPath= pcMsg->getPath()+ appName;
		delete pcMsg;
		dll.load();
	}
	QSettings* reg = new QSettings(
		HEKY_AUTORUN,//宏定义，自启动的注册表位置
		QSettings::NativeFormat);
	QString val = reg->value(appName).toString();//根据appName获取键值
	dll.unload();

	if (state) {//打开开机自启
		if (val != appPath) {//键值不是本程序地址或者不存在，则写入键值
			reg->setValue(appName, appPath);
		}
		QString v = reg->value(appName).toString();//读取刚刚写入的键值
		if (v != appPath) {//写入失败
			ui->self_start->setChecked(false);
			QMessageBox::warning(this, error_addKeyTitle, error_addKeyText);
		}
	}
	else {//关闭开机自启
		reg->remove(appName);//移除键值
		QString v = reg->value(appName).toString();
		if (v != "") {//键值仍然存在，移除失败
			ui->self_start->setChecked(true);
			QMessageBox::warning(this, error_addKeyTitle, error_addKeyText);
		}
	}
	reg->deleteLater();//延迟删除
}

void Set::on_ok_clicked() {
	svaeSetMsg();
	this->close();
}