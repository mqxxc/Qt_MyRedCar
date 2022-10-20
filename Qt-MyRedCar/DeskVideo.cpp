/*
*
* 创建日期：2022.05.26
* 最后一次修改日期：2022.07.25
* 作者：寐晴下星辰
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

//查找windows壁纸层窗口并隐藏
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM Lparam) {
	HWND hDefView = FindWindowEx(hwnd, nullptr, L"SHELLDLL_DefView", 0);
	if (hDefView != 0) {
		// 找它的下一个窗口，类名为WorkerW
		HWND hWorkerw = FindWindowEx(0, hwnd, L"WorkerW", 0);
		ShowWindow(hWorkerw, SW_HIDE);
		return false;
	}
	return true;
}


DeskVideo::DeskVideo() {
	//初始化变量
	deskwinv = new QWidget();
	dll = new QLibrary("playVideo");
	volume = 100;
	vPath = "";
	
	HWND hProgman = FindWindow(L"Progman", 0);				//找到PM窗口
	SendMessageTimeout(hProgman, 0x52C, 0, 0, 0, 100, 0);	//给它发特殊消息
	QWindow* winv = QWindow::fromWinId(WId(hProgman));		//找到背后的壁纸层
	//设置视频窗口为背后壁纸层还子窗口并设置视频窗口大小为背后壁纸层层大小
	deskwinv->setProperty("_q_embedded_native_parent_handle",
		QVariant(WId(hProgman)));				
	deskwinv->winId();							
	deskwinv->windowHandle()->setParent(winv);
	deskwinv->resize(winv->frameGeometry().size());
	deskwinv->move(0, 0);
	//找到winddows壁纸层并隐藏
	EnumWindows(EnumWindowsProc, 0);

	//其他初始化操作
	dll->load();
	player = ((playVideo * (*)(QWidget*))(dll->resolve("getpvobj")))(deskwinv);

	//读取上次保存的设置信息
	QTimer::singleShot(10, this, [=]() {
		if (!redsavedata()) {
			emit noVideo();			//上次无视频播放显示主窗口
		}
		else {
			emit trayShow(volume);	//直接播放上次视频并直接显示托盘
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
	else {//暂停
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