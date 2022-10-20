/*
*
* �������ڣ�2022.05.26
* ���һ���޸����ڣ�2022.07.25
* ���ߣ��������ǳ�
*
*/
#include<Windows.h>
#include<Qlibrary>
#include<QWindow>
#include<QTimer>
#include<QWidget>
#include<QVariant>
#include<QFile>
#include<QMessageBox>
#include"DeskVideo.h"
#include"../playVideo/playVideo.h"
#include"../SaveOrRead/SaveOrRead.h"

#define DESKVIDEO_H
#include"macro.h"

//����windows��ֽ�㴰�ڲ�����
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM Lparam) {
	HWND hDefView = FindWindowEx(hwnd, nullptr, L"SHELLDLL_DefView", 0);
	if (hDefView != 0) {
		// ��������һ�����ڣ�����ΪWorkerW
		HWND hWorkerw = FindWindowEx(0, hwnd, L"WorkerW", 0);
		ShowWindow(hWorkerw, SW_HIDE);
		return false;
	}
	return true;
}


DeskVideo::DeskVideo() {
	//��ʼ������
	deskwinv = new QWidget();
	dll = new QLibrary("playVideo");
	volume = 100;
	vPath = "";
	
	HWND hProgman = FindWindow(L"Progman", 0);				//�ҵ�PM����
	SendMessageTimeout(hProgman, 0x52C, 0, 0, 0, 100, 0);	//������������Ϣ
	QWindow* winv = QWindow::fromWinId(WId(hProgman));		//�ҵ�����ı�ֽ��
	//������Ƶ����Ϊ�����ֽ�㻹�Ӵ��ڲ�������Ƶ���ڴ�СΪ�����ֽ����С
	deskwinv->setProperty("_q_embedded_native_parent_handle",
		QVariant(WId(hProgman)));				
	deskwinv->winId();							
	deskwinv->windowHandle()->setParent(winv);
	deskwinv->resize(winv->frameGeometry().size());
	deskwinv->move(0, 0);
	//�ҵ�winddows��ֽ�㲢����
	EnumWindows(EnumWindowsProc, 0);

	//������ʼ������
	dll->load();
	player = ((playVideo * (*)(QWidget*))(dll->resolve("getpvobj")))(deskwinv);

	//��ȡ�ϴα����������Ϣ
	QTimer::singleShot(10, this, [=]() {
		if (!redsavedata()) {
			emit noVideo();			//�ϴ�����Ƶ������ʾ������
		}
		else {
			emit trayShow(volume);	//ֱ�Ӳ����ϴ���Ƶ��ֱ����ʾ����
		}
		});
}

DeskVideo::~DeskVideo() {
	delete player;
	dll->unload();
	delete dll;
	saveseting();
	delete deskwinv;
}

bool DeskVideo::replaceDesk(QString videoPath) {
	if (videoPath.isEmpty()) {
		vPath = "";
		player->stopPlay();
		deskwinv->hide();
		return false;
	}
	else {
		QFile video(videoPath);
		if (!video.exists()) {
			QWidget wid;
			wid.setWindowIcon(QIcon(icoPath));
			wid.hide();
			QMessageBox::warning(&wid, msgBoxTitle, fileNoFind);
			return false;
		}
		vPath = videoPath;
		player->setVideo(videoPath);
		player->flyVideo();
		deskwinv->show();
		emit loadFinish();
		return true;
	}
}

void DeskVideo::setVolume(float volume) {
	this->volume = volume;
	player->setVolume(volume);
}

void DeskVideo::stopOrStart(int state) {
	if (state) {
		player->flyVideo();
	}
	else {//��ͣ
		player->pauseVideo();
	}
}

void DeskVideo::saveseting() {
	QList<QString> list;
	list.append(vPath);
	list.append(QString::number(volume));

	QLibrary saveDll("SaveOrRead");
	if (saveDll.load()) {
		SaveOrRead* saveData = ((SaveOrRead* (*)(QString, QList<QString>*))
			(saveDll.resolve("getSOR")))(initFilePath, &list);
		saveData->saveFile();
		delete saveData;
		saveDll.unload();
	}
}

bool DeskVideo::redsavedata() {
	QList<QString> list;

	QLibrary saveDll("SaveOrRead");
	if (saveDll.load()) {
		SaveOrRead* saveData = ((SaveOrRead * (*)(QString, QList<QString>*))
			(saveDll.resolve("getSOR")))(initFilePath, &list);
		if (!saveData->pathExist()) {
			return false;
		}
		else{
			saveData->readFile();
		}
	}

	QList<QString>::const_iterator it;
	it = list.constBegin();
	vPath = *it;
	volume = (*++it).toFloat();
	setVolume(volume);
	if (replaceDesk(vPath)) {
		return true;
	}
	return false;
}