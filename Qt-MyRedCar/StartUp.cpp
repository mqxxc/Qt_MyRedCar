/*
*
* 创建日期：2022.06.15
* 最后一次修改日期：2022.07.02
* 作者：寐晴下星辰
*
*/
#include<QProcess>
#include<QLibrary>
#include<QApplication>
#include"StartUp.h"
#include"awaken_source.h"
#include"../getScreenInformation/getScreenInformation.h"
#define STARTUP_H
#include"macro.h"

StartUp::StartUp() {
//获取设别信息
	getPcmag();
//初始化操作
	init();
//与除主窗口外的部件建立联系
	connectForOther();
}
StartUp::~StartUp() {
	this->disconnect();
	if (mainwid != nullptr) {
		delete mainwid;
	}
	delete desk;
	delete tray;
}

void StartUp::setApp(QApplication* app){
	this->app = app;
}

void StartUp::awakenExe(){
	if (mainwid != nullptr) {
		if (mainwid->isMinimized()) {
			mainwid->showNormal();
		}
		else {
			mainwid->hide();
			mainwid->show();
		}
	}
	else {
		tray->hide();
		mainWidNew();
	}
}

void StartUp::connectForOther() {
	connect(tray,  &Tray::setVolumeToDesk, desk, &DeskVideo::setVolume);
	connect(tray,  &Tray::mainExit,        this, &StartUp::exitToApp);
	connect(tray,  &Tray::ShowMW,          this, &StartUp::mainAwaken);
	connect(desk,  &DeskVideo::noVideo,    this, &StartUp::mainWidNew);
	connect(desk,  &DeskVideo::trayShow,   tray, &Tray::setVolume);
	connect(tray,  &Tray::stateToDesk,     desk, &DeskVideo::stopOrStart);
	connect(tray,  &Tray::setVolumeToDesk, desk, &DeskVideo::setVolume);
	connect(desk,  &DeskVideo::loadFinish, this, &StartUp::loadFinish);
	connect(desk,  &DeskVideo::trayShow,   tray, &Tray::setVolume);
	connect(srever,&Server::awaken,        this, &StartUp::awakenExe);
}

void StartUp::init(){
	initMember();
}

void StartUp::initMember(){
	load = nullptr;
	loading();
	mainwid = nullptr;
	tray = new Tray();
	desk = new DeskVideo();
	srever = new Server();
}

void StartUp::loading(){
	if (load == nullptr) {
		load = new QProcess;
	}
	QString processPath = exePath + load_path;
	load->start(processPath);
}

void StartUp::loadFinish(){
	if (load != nullptr) {
		load->terminate();
		delete load;
		load = nullptr;
	}
}


void StartUp::getPcmag(){
	QLibrary pathDll("getScreenInformation");
	if (pathDll.load()) {
		getScreenInformation* gScrIn =
			((getScreenInformation * (*)())(pathDll.resolve("getClassobj")))();

		exePath = gScrIn->getPath();
		float lration = gScrIn->getLogicRatio();
		float pration = gScrIn->getPhysicsRatio();
		ration = lration / pration;

		delete gScrIn;
		pathDll.unload();
	}
}

void StartUp::connectForMW(){
	connect(mainwid, &QtMyRedCar::mainExit,     this, &StartUp::exitToApp);
	connect(mainwid, &QtMyRedCar::mainWidClear, this, &StartUp::mainWidDelete);
	connect(mainwid, &QtMyRedCar::upDesk,       desk, &DeskVideo::replaceDesk);
	connect(mainwid, &QtMyRedCar::upDesk,       tray, &Tray::setState);
	connect(mainwid, &QtMyRedCar::loaded,       this, &StartUp::mainWidShow);
}

void StartUp::exitToApp(){
	app->exit();
}

void StartUp::mainWidNew(){
	mainwid = new QtMyRedCar();
	mainwid->show();
	mainwid->hide();
	connectForMW();
}

void StartUp::mainWidShow(){
	loadFinish();
	mainwid->show();
}

void StartUp::mainAwaken(){
	loading();
	mainWidNew();
}

void StartUp::mainWidDelete() {
	if (mainwid != nullptr) {
		delete mainwid;
		mainwid = nullptr;
		tray->show();
	}
}