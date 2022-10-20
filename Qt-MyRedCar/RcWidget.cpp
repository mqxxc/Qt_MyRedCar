/*
*
* 创建日期：2022.05.xx
* 最后一次修改日期：2022.06.24
* 作者：寐晴下星辰
* 
*/
#include "RcWidget.h"
#include"ui_RcWidget.h"
#include<QDir>
#include<QFile>
#include<QTextStream>
#include<QMap>
#include<QLibrary>
#include<QTimer>
#include<QWheelEvent>
#include<QCollator>
#define RCWIDGET_H
#include"macro.h"
#include"Unit.h"
#include"DataHandle.h"
#pragma execution_character_set("utf-8")


RcWidget::RcWidget(QWidget* parent) {
//初始化基本变量
	ui = new Ui::RcWidget;
	ui->setupUi(this);

//其他初始化
	initMember();
	initUnitSize();

//延迟初始化
	QTimer::singleShot(10, this, [=]() {
		initUnit(0);
		refreshUnit();
		controlSig |= stateSig_N & 1;
		   }); 
}

RcWidget::~RcWidget() {
//将本次运行的各种数据进行保存到本地缓存文件
	delete rc;
//回收units
	while (!units.empty()){
		auto it = units.begin();
		Unit* btn = it.value();
		if (btn != nullptr){
			delete btn;
			btn = nullptr;
		}
		units.erase(units.begin());
	}
	delete ui;
	this->disconnect();
}

void RcWidget::setScaling(float Scaling){
	Unit::setScaling(Scaling);
}

void RcWidget::setPath(QString path){
	this->path = path;
	Unit::setExe_Path(path);
//初始化资源
	initRc();
}

void RcWidget::initRc(){
	if (rc->getNum()==0){
		redLocal_Rc();
	}
}

//bool RcWidget::redRecord(){
//	int sum = 0;
//	FileMag temp;
//	QString filePath(path);
//	QFile file(filePath.append(initTextPath));
//	if (!file.exists()) {
//		return false;
//	}
//	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//		return false;
//	}
//	if (file.readAll().isEmpty()) {
//		return false;
//	}
//	QString names;
//	redRc_Name(&names);
//	QTextStream fileStream(&file);
//	fileStream.seek(0);
//	while (!fileStream.atEnd()) {
//		QString name = fileStream.readLine();
//		if (name.contains(u8'*')) {
//			QString namea = name.mid(name.indexOf(u8'*')+1);
//			if (names.contains(namea)) {
//				temp.name.assign(namea.toLocal8Bit());
//				temp.vido.assign(fileStream.readLine().toLocal8Bit());
//				temp.photo.assign(fileStream.readLine().toLocal8Bit());
//				temp.useTime.assign(fileStream.readLine().toLocal8Bit());
//				filec temp2(temp);
//				temp2.setScouce(fileStream.readLine().toInt());
//				temp2.setLTime(fileStream.readLine().toStdString());
//				temp2.setLove(fileStream.readLine().toInt());
//				rc->addRc(temp2);
//			}
//			idList.append(sum++);
//		}
//	}
//	file.close();
//	return true;
//}
//
//void RcWidget::redRc_Name(QString* names) {
//	QString filePath(path);
//	filePath.append("/data");
//
//	QDir dir(filePath);
//	dir.setFilter(QDir::NoDotAndDotDot | QDir::Dirs| QDir::Files);
//	dir.setSorting(QDir::Name);
//
//	QFileInfoList dirList = dir.entryInfoList();
//	for (int i = 0; i < dirList.size(); ++i) {
//		QFileInfo fileInfo = dirList.at(i);
//		names->append('*').append(fileInfo.fileName());
//	}
//}

void RcWidget::redLocal_Rc(){
	char sum = 0;

	QString filePath(path);
	QString temp(dataPath);
	filePath.append(temp.left(temp.lastIndexOf("/")));

	QDir dir(filePath);
	dir.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);
	dir.setSorting(QDir::Name);

	QDir inDir("");
	inDir.setFilter(QDir::NoDotAndDotDot | QDir::Files);
	inDir.setSorting(QDir::Name);


	QFileInfoList fileList = dir.entryInfoList();
	QString file, video, photo;
	for (int i = 0; i < fileList.size(); ++i) {
		QFileInfo fileInfo = fileList.at(i);
		QString rcstr(filePath);
		rcstr.append("/").append(fileInfo.fileName());
		inDir.setPath(rcstr);
		file=fileInfo.fileName();

		QFileInfoList inFileList = inDir.entryInfoList();
		for (int i = 0; i < inFileList.size(); ++i) {
			QFileInfo inFileInfo = inFileList.at(i);
			if (inFileInfo.suffix() == u8"mp4") {
				video=inFileInfo.fileName();
			}
			else if (inFileInfo.suffix() == u8"jpg") {
				photo=inFileInfo.fileName();
			}
		}
		rc->addData(new Msg(file,video,photo));
	}
}

//void RcWidget::saveRc_to_local(){
//	QString filePath(path);
//	QFile file(filePath.append(initTextPath));
//	if (!file.open(QIODevice::WriteOnly )) {
//		return ;
//	}
//	QTextStream fileStream(&file);
//	for (int i = 0; i < rc->getNum(); ++i) {
//		filec* temp = rc->getData(i);
//		if (temp->getDelt()) {
//			fileStream << u8"*" << QString::fromLocal8Bit(temp->getName().c_str()) << "\n";
//			fileStream << QString::fromLocal8Bit(temp->getVido().c_str()) << "\n";
//			fileStream << QString::fromLocal8Bit(temp->getPhoto().c_str()) << "\n";
//			fileStream << QString::fromLocal8Bit(temp->getUse_Time().c_str()) << "\n";
//			fileStream << QString::number(static_cast<int>(temp->getSource())) << "\n";
//			fileStream << QString::fromLocal8Bit(temp->getImport_Time().c_str()) << "\n";
//			fileStream << QString::number(temp->getLove()) << "\n";
//		}
//	}
//}

void RcWidget::initMember(){
	rc = new DetaHandle();
	controlSig &= (stateSig_N ^ 1);
	controlSig |= (stateSig_N & 2);
	controlSig |= (stateSig_N & 4);
}

void RcWidget::initUnit(int i){
	for (; i < rc->getNum();++i) {
		units[i] = new Unit(rc->getData(i), i,this);
		connect(units[i], &Unit::upUnits,    this, &RcWidget::release);
		connect(units[i], &Unit::rename_sig, this, &RcWidget::fileRename);
		connect(units[i], &Unit::delete_sig, this, &RcWidget::fileDelete);
		idList.append(i);
	}
}

void RcWidget::initUnitSize() {
//计算图片单元的大小
	unitMag.unitW = Unit::getWid_W();					//单元的宽
	unitMag.spaceW = Unit::getWid_W() / ratio;			//间隙宽
	int divisor = unitMag.unitW + unitMag.spaceW;		//二者宽的和
	unitMag.rowN = (widW - unitMag.spaceW) / divisor;	//一行能存放的个数
	unitMag.offset= widW % divisor / 2;					//两边的偏移量
}

void RcWidget::refreshUnit(){
	lastUnitX = unitMag.offset;
	lastUnitY = 0;
	emit up_ScrValue(0);
	if (controlSig&2) {
		QList<int>::const_iterator STL;
		for (STL = idList.constBegin(); STL != idList.constEnd(); ++STL) {
			showUnit(*STL);
		}
	}else {
		QList<int>::const_reverse_iterator  STL;
		for (STL = idList.rbegin(); STL != idList.rend(); ++STL) {
			showUnit(*STL);
		}
	}
	if (!(controlSig&1)) {//仅在第一次初始化是发射信号
		emit newFinish();
	}
}

void RcWidget::showUnit(int sum) {
	if (!rc->getData(sum)->isHide()) {
		units[sum]->move(lastUnitX, lastUnitY);
		units[sum]->show();
		reckonNext();
	}
}

void RcWidget::refresh(){
	rc->refresh(false);
	char i = 0;
	for (auto& temp :idList){
		temp = i++;
	}
	refreshUnit();
	up_ScrSize();
}

void RcWidget::moveUnit(int offset){
	for (int i = 0; i < rc->getNum(); ++i) {
		if (!rc->getData(i)->isHide()) {
			units[i]->move(units[i]->geometry().x(),
				units[i]->geometry().y() + offset);
		}
	}
}

void RcWidget::searchUnit(QString name){
	rc->refresh(true);
	for (int i = 0; i < rc->getNum(); ++i) {
		QString rcName =rc->getData(idList[i])->getName();
		units[idList[i]]->hide();
		if (rcName.contains(name)) {
			rc->getData(idList[i])->setHide(false);
		}
	}
	refreshUnit();
	up_ScrSize();
	emit up_ScrValue(0);
}

void RcWidget::changeCondition(int condition){
	if (controlSig & (stateSig_N&(condition<<3))) {
		return;
	}
	controlSig &= (stateSig_N ^ 60);
	controlSig |= (stateSig_N & condition);
	QCollator collator(QLocale::Chinese);
	QStringList list;
	if (controlSig & (stateSig_N & 4)) {
		QMap<QString, int>map;
		for (int i = 0; i < rc->getNum(); ++i) {
			QString temp= rc->getData(i)->getName();
			list << temp;
			map[temp] = i;
		}
		std::sort(list.begin(), list.end(), collator);
		for (int i = 0; i < rc->getNum(); ++i){
			idList[i] = map[list.at(i)];
		}
	}else if(controlSig & (stateSig_N & 32)){
		QMap<QString, int>map;
		QList<int> loveList;
		for (int i = 0; i < rc->getNum(); ++i) {
			if (rc->getData(i)->getLove()) {
				loveList.prepend(i);
			}else {
				loveList.append(i);
			}
		}
		for (int i = 0; i < rc->getNum(); ++i) {
			idList[i] = loveList.at(i);
		}
	}else if (controlSig & (stateSig_N & 8)) {
		QMultiMap<QString, int> map;
		for (int i = 0; i < rc->getNum(); ++i) {
			QString temp = rc->getData(i)->getUse_time();
			list << temp;
			map.insert(temp,i);
		}
		list.removeDuplicates();
		std::sort(list.begin(), list.end(), collator);
		int j = 0;
		for (int i = 0; i < list.size();++i) {
			QList<int> n = map.values(list.at(i));
			for (auto& ti : n) {
				idList[j++] = ti;
			}
		}
	}else {
		QMultiMap<QString, int> map;
		for (int i = 0; i < rc->getNum(); ++i) {
			QString temp = rc->getData(i)->getImport_time();
			list << temp;
			map.insert(temp, i);
		}
		list.removeDuplicates();
		std::sort(list.begin(), list.end(), collator);
		int j = 0;
		for (int i = 0; i < list.size(); ++i) {
			QList<int> n = map.values(list.at(i));
			for (auto& ti : n) {
				idList[j++] = ti;
			}
		}
	}
}

void RcWidget::changeOrder(bool state){
	if (state) {
		controlSig &= (stateSig_N ^ 2);
	}
	else {
		controlSig |= (stateSig_N & 2);
	}
	refreshUnit();
}

void RcWidget::addUnit(){
	int i = units.size();
	initUnit(i);
	units[i]->move(lastUnitX, lastUnitY);
	units[i]->show();
	reckonNext();
	up_ScrSize();
}

void RcWidget::reckonNext(){
	lastUnitX += unitMag.unitW + unitMag.spaceW;
	if (lastUnitX+ unitMag.unitW > widW) {
		lastUnitY += unitMag.unitW + unitMag.spaceW;
		lastUnitX = unitMag.offset;
	}
}

bool RcWidget::moveFile(QString path){
	QString filePath(this->path);
	QString video = (path.section("/", -1));
	QString name=video.section(".",-3,-2);			
	filePath.append(dataPath).append(name);			//以视频名字作为文件夹名字
	QDir dir;
	QFile file(path);

	if (dir.mkdir(filePath)) {			//创建文件夹
		if (file.rename(filePath.append("/").append(video))) {

			QLibrary dll("Screenshot");
			Screenshot* getPotho;
			if(dll.load()) {
				getPotho = ((Screenshot * (*)())(dll.resolve("getScrObj")))();
			}
			QEventLoop loop;
			getPotho->setLoop(&loop);
			getPotho->getJpg(filePath);
			//dxg提示框正在导入
			loop.exec();	
			rc->addData(filePath, getPotho->isSuccess());

			addUnit();
			
			delete getPotho;
			dll.unload();
			return true;
		}
	}
	return false;
}

void RcWidget::resizeEvent(QResizeEvent* e){
	widW = this->size().width();
	widH = this->size().height();
	initUnitSize();
	up_ScrSize();
	if (controlSig&1) {
		refreshUnit();
	}
}

void RcWidget::wheelEvent(QWheelEvent* e){
	int pag=e->angleDelta().y()/4;
	emit up_ScrValue(-pag,false);
}

void RcWidget::mousePressEvent(QMouseEvent* event){
	int id = Unit::getUnit_Id();
	if (id != -1) {
		units[id]->onRelease();
		emit selectUnit("");
	}
}

void RcWidget::release(int id){
	if (id != -1) {
		units[id]->onRelease();
	}
	QString videoPath = path + dataPath
		+rc->getData(Unit::getUnit_Id())->getVideo();
	emit selectUnit(videoPath);
}

void  RcWidget::fileRename(int id,QString name){
	/*QString rcVpath= rc->getData(id)->getVideo();
	QString oldVpath = path + dataPath + rcVpath;
	QString right = rcVpath.right(rcVpath.size() - rcVpath.lastIndexOf("."));
	QString left= rcVpath.left(rcVpath.lastIndexOf("/"));
	QString newVpath=path+ dataPath + left + "/" +name+ right;
	QFile::rename(oldVpath,newVpath);*/
	

	/*QString rcPpath = rc->getData(id)->getPhoto();
	QString oldPpath = path + dataPath + rcPpath;
	right = rcPpath.right(rcVpath.size() - rcVpath.lastIndexOf(".")+1);
	QString newPpath= path + dataPath + left + "/" + name + right;
	QFile::rename(oldPpath, newPpath);*/
	

	/*QString rcNpath = rc->getData(id)->getName();
	QString oldNname = path + dataPath + rcNpath;
	QString newNname = path + dataPath + name;
	QFile::rename(oldNname, newNname);*/

	QString dirName = path + dataPath + rc->getData(id)->getName();

	QFile::rename(path + dataPath + rc->getData(id)->getVideo(),
		dirName + "/" + name + deVideoS);

	QFile::rename(path + dataPath + rc->getData(id)->getPhoto(),
		dirName + "/" + name + dePhotoS);

	QFile::rename(dirName , path + dataPath + name);
}

void RcWidget::fileDelete(int id) {
	QString temp = path + dataPath;

	QString videoPath = temp +rc->getData(id)->getVideo();
	QFile file_v(videoPath);
	file_v.remove();
	file_v.close();

	QString photoPath = temp + rc->getData(id)->getPhoto();
	QFile file_p(photoPath);
	file_p.remove();
	file_p.close();

	QString dirPath = temp + rc->getData(id)->getName();
	QDir file_dir(dirPath);
	file_dir.rmpath(dirPath);

	rc->deleteData(id);
	idList.removeAt(id);
	delete units[id];
	units.remove(id);
	refreshUnit();
}

void RcWidget::up_ScrSize(){
	int n = rc->getNum();
	int h = n / unitMag.rowN;
	if (n % unitMag.rowN) {
		++h;
	}
	int range = h * (unitMag.spaceW + unitMag.unitW) -widH;
	if (range <= 10) {
		range = 0;
	}
	else {
		range -= 10;
	}
	emit up_ScrSize_sig(range);
}