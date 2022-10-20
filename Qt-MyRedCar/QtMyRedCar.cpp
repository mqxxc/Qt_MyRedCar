/*
*
* 创建时间：2022.04.xx
* 最后一次修改日期：2022.07.02
* 作者：寐晴下星辰
*
*/
#include "ui_qtmyredcar.h"      
#include "QtMyRedCar.h"
#include<QLibrary>              
#include<QMessageBox>          
#include<QDesktopServices>      
#include<QUrl>                  
#include<QFileDialog>           
#include<QTimer>               
#include<QLineEdit>             
#include<QMouseEvent>           
#include<QListView>
#include"Elastic.h"
#include"set.h"
//我的dll库
#include"../playVideo/playVideo.h"                        
#include"../getScreenInformation/getScreenInformation.h"  
#define QTMYREDCAR_H
#include"macro.h"


QtMyRedCar::QtMyRedCar(QWidget* parent) {
	//获取计算机信息
	QLibrary dll("getScreenInformation");
	dll.load();
	getScreenInformation* pcMag = ((getScreenInformation * (*)())
		(dll.resolve("getClassobj")))();
	float ration = pcMag->getLogicRatio() / pcMag->getPhysicsRatio();
	exePath = pcMag->getPath();
	QPoint workSize = pcMag->getWid_workSize();
	delete pcMag;
	dll.unload();
	//初始化基本变量
	ui = new Ui::QtMyRedCar;
	ui->setupUi(this);
	if (parent != Q_NULLPTR) {
		this->setParent(parent);
	}
	//其他初始化
	initMember();
	initWid(workSize, ration);
	initUi(ration);
	//链接信号与信号槽
	connects();
}

QtMyRedCar::~QtMyRedCar() {
	delete evenRoot;
	delete player;
	dll->unload();
	delete dll;
	delete ui;
	this->disconnect();
}

void QtMyRedCar::initMember() {
	minState = false;
	old_SrcValue = 0;
	dll = new QLibrary("playVideo");
	player = nullptr;
	evenRoot = new Elastic(this);
	orderState = true;
}

void QtMyRedCar::initWid(QPoint& workSize, float& ration) {
// 窗口基本设置
	setWindowFlags(Qt::FramelessWindowHint |
		Qt::WindowMinimizeButtonHint);          // 无边框
	setWindowIcon(QIcon(exePath+icoPath));

//标题栏
	int title = titleh * ration;
	ui->title->setMinimumSize(QSize(1200 * ration, title));     //初始化标题栏

//初始窗口大小
	this->resize(QSize(1200 * ration, 930 * ration + title));
	//移动窗口至屏幕中间
	move((workSize.x() - width()) / 2,
		(workSize.y() - height()) / 2);

//其他默认操作
	evenRoot->setTitleH(title);
}

void QtMyRedCar::initUi(float& ration) {
	//title
		//无滑块
	ui->titletext->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->titletext->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//取消右键菜单
	ui->titletext->setContextMenuPolicy(Qt::NoContextMenu);
	//鼠标事件穿透
	ui->titletext->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	//分类设置字体格式
	ui->label->setFont(QFont("Timers", 10, QFont::Bold));
	//过滤按钮
	ui->filter->setLayoutDirection(Qt::RightToLeft);
	//Rcwid
	ui->RcWid->setScaling(ration);
	ui->RcWid->setPath(exePath);
	//comboBox
	ui->comboBox->addItems(QStringList() << comboBox1 << comboBox2
		<< comboBox3 << comboBox4);
	ui->comboBox->setView(new QListView());
	//order
	on_order_clicked();
	//延时初始化
	QTimer::singleShot(10, this, [=]() {
		initSearch();
		initVidewid();
		});
}

void QtMyRedCar::connects() {
	connect(ui->RcWid, &RcWidget::up_ScrValue, this, &QtMyRedCar::setSrcValue);
	connect(ui->RcWid, &RcWidget::up_ScrSize_sig, this, &QtMyRedCar::setSrcSize);
	connect(this,      &QtMyRedCar::upUnitSrc, ui->RcWid, &RcWidget::moveUnit);
	connect(ui->RcWid, &RcWidget::selectUnit, this, &QtMyRedCar::previewVideo);
	connect(ui->Rcroll,&QScrollBar::valueChanged, this, &QtMyRedCar::changeValue);
	connect(ui->RcWid, &RcWidget::newFinish, this, &QtMyRedCar::emitLoaded);
	connect(this,      &QtMyRedCar::search, ui->RcWid, &RcWidget::searchUnit);
	connect(this,      &QtMyRedCar::changeOrder, ui->RcWid, &RcWidget::changeOrder);
	connect(ui->comboBox, SIGNAL(activated(QString)), ui->RcWid, SLOT(changeCondition(QString)));
}

void QtMyRedCar::initSearch() {
	int w = ui->widget->height();
	input = new QLineEdit;
	input->setMinimumHeight(w);
	input->setFont(QFont("Timers", 16, QFont::Bold));
	input->setPlaceholderText(inputTxt);

	button = new QPushButton;
	QPixmap pixmap(exePath+inputIco);
	QPixmap fitpixmap = pixmap.scaled(w, w, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	button->setIcon(QIcon(fitpixmap));
	button->setIconSize(QSize(w, w));
	button->setFlat(true);
	button->setStyleSheet("border: 0px"); //消除边框
	button->setCursor(Qt::PointingHandCursor);
	button->installEventFilter(this);

	QVBoxLayout* pEditTmpLayout = new QVBoxLayout(input);
	pEditTmpLayout->setSpacing(0);
	pEditTmpLayout->setMargin(0);
	pEditTmpLayout->addWidget(button);
	pEditTmpLayout->setAlignment(button, Qt::AlignHCenter | Qt::AlignRight);

	QGridLayout* pMainLayout = new QGridLayout();
	pMainLayout->setMargin(0);
	pMainLayout->setSpacing(0);
	pMainLayout->addWidget(input);

	ui->widget->setLayout(pMainLayout);
}

void QtMyRedCar::initVidewid() {
	ui->videwid->setMaximumHeight(ui->videwid->height());
}

void QtMyRedCar::on_maxsize_clicked() {
	if (minState) {
		//dxg后期可加上ico的改变这里用文字‘□’表示
		this->resize(leftTop_point);
		minState = false;
	}
	else {
		leftTop_point = this->geometry().size();
		this->hide();
		this->showMaximized();
		minState = true;
	}
}

void QtMyRedCar::on_originality_clicked() {
	QMessageBox::about(this, MsgTitle, Msg_originality);
}

void QtMyRedCar::on_about_clicked() {
	QDesktopServices::openUrl(QUrl
	(QString(Msg_about_link)));
}

void QtMyRedCar::on_lod_clicked() {
	//定义文件对话框类
	QFileDialog fileDialog(this);
	//定义文件对话框标题
	fileDialog.setWindowTitle(dialogTitle);
	//设置默认文件路径
	fileDialog.setDirectory(".");
	//设置文件过滤器
	fileDialog.setNameFilter(dialogFilter);
	//设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
	fileDialog.setFileMode(QFileDialog::ExistingFiles);
	//设置视图模式
	fileDialog.setViewMode(QFileDialog::Detail);
	//判断是否点击确定键
	if (fileDialog.exec() != QFileDialog::Rejected) {

		QStringList fileNames = fileDialog.selectedFiles();
		QString path = fileNames.join("");
		if (ui->RcWid->moveFile(path)) {
			QMessageBox::about(this, MsgTitle, loadFinish);
		}
		else {
			QMessageBox::about(this, MsgTitle, loadFail);
		}
	}
	fileDialog.setHistory(QStringList());
	fileDialog.close();
}

void QtMyRedCar::on_Refresh_clicked() {
	ui->Rcroll->setValue(0);
	ui->RcWid->refresh();
	input->setText("");
}

void QtMyRedCar::on_deletebo_clicked() {
	emit upDesk("");
}

void QtMyRedCar::on_OK_clicked() {
	emit upDesk(path);
}

void QtMyRedCar::on_endbo_clicked() {
	emit mainExit();
}

void QtMyRedCar::previewVideo(QString path) {
	if (!path.isEmpty()) {
		if (player == nullptr) {
			dll->load();
			player = ((playVideo * (*)(QWidget*))
				(dll->resolve("getpvobj")))(ui->videwid);
		}
		this->path = path;
		player->setVideo(path);
		player->setVolume(0);
		player->flyVideo();
	}
	else {
		this->path = "";
		delete player;
		player = nullptr;
		dll->unload();
	}
}

void QtMyRedCar::on_off_clicked() {
	emit mainWidClear();
}

void QtMyRedCar::on_filter_clicked() {
	QMessageBox::about(this, MsgTitle, Msg_filter);
}

void QtMyRedCar::on_order_clicked() {
	if (orderState) {
		QPixmap pixmap(exePath+sort_p);
		int w = ui->order->geometry().width();
		QPixmap fitpixmap = pixmap.scaled(w, w, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		ui->order->setIcon(QIcon(fitpixmap));
		orderState = false;
		emit changeOrder(orderState);
	}
	else {
		QPixmap pixmap(exePath+sort_r);
		int w = ui->order->geometry().width();
		QPixmap fitpixmap = pixmap.scaled(w, w, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		ui->order->setIcon(QIcon(fitpixmap));
		orderState = true;
		emit changeOrder(orderState);
	}
}

void QtMyRedCar::on_setbox_clicked() {
	Set* set=new Set;
	delete set;
}

void QtMyRedCar::setSrcSize(int log) {
	ui->Rcroll->setMaximum(log);
}

void QtMyRedCar::setSrcValue(int value, bool code) {
	if (code) {
		ui->Rcroll->setValue(value);
		return;
	}
	int oldValue = ui->Rcroll->value();
	int newValue = oldValue + value;
	if (value < 0) {
		if (newValue >= ui->Rcroll->minimum()) {
			ui->Rcroll->setValue(newValue);
		}
		else {
			ui->Rcroll->setValue(ui->Rcroll->minimum());
			newValue = ui->Rcroll->minimum();
		}
	}
	if (value > 0) {
		if (newValue <= ui->Rcroll->maximum()) {
			ui->Rcroll->setValue(newValue);
		}
		else {
			ui->Rcroll->setValue(ui->Rcroll->maximum());
			newValue = ui->Rcroll->maximum();
		}
	}
}

void QtMyRedCar::changeValue(int value) {
	int changValue = old_SrcValue - ui->Rcroll->value();
	old_SrcValue = ui->Rcroll->value();
	emit upUnitSrc(changValue);
}

void QtMyRedCar::emitLoaded() {
	emit loaded();
}

bool QtMyRedCar::eventFilter(QObject* obj, QEvent* even) {
	if (obj == button) {
		if (even->type() == QEvent::MouseButtonPress) {
			QMouseEvent* e = static_cast <QMouseEvent*> (even);
			if (e->button() == Qt::LeftButton) {
				QString name = input->text();
				if (!name.isEmpty()) {
					emit search(name);
				}
				return true;
			}
		}
	}
	return QObject::eventFilter(obj, even);
}