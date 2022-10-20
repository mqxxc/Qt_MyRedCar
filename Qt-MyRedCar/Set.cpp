/*
*
* �������ڣ�2022.06.15
* ���һ���޸����ڣ�2022.07.25
* ���ߣ��������ǳ�
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
	if (value & 1) {	//����������
		ui->self_start->setChecked(true);
	}
}

void Set::svaeSetMsg(){
	if (ui->self_start->checkState() != Qt::Unchecked) {	//��������
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
	//dxg˼����ȥ����setӦ�÷���dll�е������ź��Ժ����޸�
	//���ÿ���������flag��ʾ�Ƿ񿪻�����
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
		HEKY_AUTORUN,//�궨�壬��������ע���λ��
		QSettings::NativeFormat);
	QString val = reg->value(appName).toString();//����appName��ȡ��ֵ
	dll.unload();

	if (state) {//�򿪿�������
		if (val != appPath) {//��ֵ���Ǳ������ַ���߲����ڣ���д���ֵ
			reg->setValue(appName, appPath);
		}
		QString v = reg->value(appName).toString();//��ȡ�ո�д��ļ�ֵ
		if (v != appPath) {//д��ʧ��
			ui->self_start->setChecked(false);
			QMessageBox::warning(this, error_addKeyTitle, error_addKeyText);
		}
	}
	else {//�رտ�������
		reg->remove(appName);//�Ƴ���ֵ
		QString v = reg->value(appName).toString();
		if (v != "") {//��ֵ��Ȼ���ڣ��Ƴ�ʧ��
			ui->self_start->setChecked(true);
			QMessageBox::warning(this, error_addKeyTitle, error_addKeyText);
		}
	}
	reg->deleteLater();//�ӳ�ɾ��
}

void Set::on_ok_clicked() {
	svaeSetMsg();
	this->close();
}