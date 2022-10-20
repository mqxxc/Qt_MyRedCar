/*
*
* �������ڣ�2022.05.xx
* ���һ���޸����ڣ�2022.07.19
* ���ߣ��������ǳ�
*
*/
#include <QtWidgets/QApplication>
#include<QMessageBox>
#include<QFile>
#include<QLibrary>
#include<QSharedMemory>
#include<QProcess>
#define MAIN_H
#include "macro.h"
#include"StartUp.h"
#include"../getScreenInformation/getScreenInformation.h"
#include"../playVideo/playVideo.h"
#include"../Screenshot/Screenshot.h"
#include"../SaveOrRead/SaveOrRead.h"

bool testFile();
bool testApp();
int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	app.setWindowIcon(QIcon(IcoPath));

	if (!testFile()) {			//���������dll�Ƿ����ɾ
		return 0;
	}

	if (testApp()) {			//����Ƿ��ظ�����
		return 0;
	}

	StartUp exe;
	app.setQuitOnLastWindowClosed(false);
	exe.setApp(&app);
	return app.exec();
}

bool testFile() {
	QWidget wid;
	wid.setWindowIcon(QIcon(IcoPath));
	wid.hide();

	QLibrary dll("getScreenInformation");
	if (!dll.load()) {
		QMessageBox::warning(&wid, error_loseTitle, error_loseGSIFM);
		return false;
	}
	getScreenInformation* pcMag = ((getScreenInformation * (*)())
		(dll.resolve("getClassobj")))();
	QString path = pcMag->getPath();
	delete pcMag;
	dll.unload();
	dll.setFileName("playVideo");
	if (!dll.load()) {
		QMessageBox::warning(&wid, error_loseTitle, error_losePlayVideo);
		return false;
	}
	dll.unload();
	dll.setFileName("Screenshot");
	if (!dll.load()) {
		QMessageBox::warning(&wid, error_loseTitle, error_loseSCreenshot);
		return false;
	}
	dll.unload();
	dll.setFileName("SaveOrRead");
	if (!dll.load()) {
		QMessageBox::warning(&wid, error_loseTitle, error_loseSaveOrRead);
		return false;
	}
	dll.unload();
	QFile file(path+"/awaken_client.exe");
	if (!file.exists()) {
		QMessageBox::warning(&wid, error_loseTitle, error_loseAwaken);
		return false;
	}
	file.close();
	/*file.setFileName(path+"/Loading.exe");
	if (!file.exists()) {
		QMessageBox::warning(&wid, error_loseTitle, error_loseLoading);
		return false;
	}
	file.close();*/
	return true;
}

bool testApp() {
	QSharedMemory* sharedMemory = new QSharedMemory;
	sharedMemory->setKey("appConst");
	if (sharedMemory->attach()) {//Ӧ���Ѿ�����������ʾ�����ڣ�����������
		QProcess *process=new QProcess;
		process->start("awaken_client.exe");
		delete sharedMemory;
		return true;
	}
	QString error= sharedMemory->errorString();
	if (!sharedMemory->create(1)) {//���ٹ���ռ�ʧ��ʧ�ܣ�������ʾ��
		QMessageBox::warning(nullptr, QString("���д���"), QString("��Ҳ������ԭ��"));
		return true;
	}
	return false;
}