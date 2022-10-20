/*
*
* 创建时间：2022.03.xx
* 最后一次修改时间：2022.07.02
* 作者：寐晴下星辰
* 
*/

#include"Frc.h"

#define defImTime "2021.01.05"
#define dePhotoS " "
#define deusedTime "2022.05.06"

//资源类的函数实现
filec::filec(FileMag fileMag) {
	this->fileMag = fileMag;
	//初始状态变量
	state = true;
	source = Source::LOCAL;
	importTime = defImTime;
	love = false;
	delt = true;
}

string filec::getPhoto() {
	return fileMag.photo;
}

string filec::getVido() {
	return fileMag.vido;
}

string filec::getName() {
	return fileMag.name;
}

Source filec::getSource(){
	return source;
}

string filec::getImport_Time(){
	return importTime;
}

bool filec::getLove() {
	return love;
}

bool filec::getDelt(){
	return delt;
}

string filec::getUse_Time() {
	return fileMag.useTime;
}

void filec::setState(bool state) {
	this->state = state;
}

void filec::setScouce(char id){
	switch (id){
	case 0: {
		source = Source::CRAFT;
	}break;
	case 1: {
		source = Source::LOCAL;
	}break;
	case 2: {
		source = Source::INTERNET;
	}break;
	default:
		break;
	}
}

void filec::setLove(int love){
	this->love;
}

void filec::setLTime(string time){
	importTime = time;
}

void filec::deleteRc(){
	delt = false;
}

void filec::rename(string str){
	string name;
	fileMag.name = str;
	fileMag.photo = name.assign(str).append(dePhotoS);
	fileMag.vido = name.assign(str).append(fileMag.vido.substr(fileMag.vido.rfind('.')));
}

bool filec::isShow(){
	if (delt && state) {
		return true;
	}
	return false;
}


//资源集类
void filecs::addRc(filec tmp) {
	this->rcVector.push_back(tmp);
}

void filecs::addRc(string path,bool state){

	FileMag temp;
	string fb(path);
	string video = fb.substr(fb.rfind('/')+1);
	string name=video.substr(0,video.rfind('.'));
	string photo;
	if (state) {
		photo = name;
		photo.append(dePhotoS);
	}
	else {
		photo = "默认路径";//dxg
	}
	temp.name = name;
	temp.photo = photo;
	temp.vido = video;
	temp.useTime = deusedTime;
	temp.conversion();
	filec temp2(temp);
	addRc(temp2);
}

void filecs::hideAll_Frc(){
	refresh(false);
	for (int i = 0; i < rcVector.size(); ++i) {
		rcVector[i].setState(false);
	}
}

void filecs::refresh(bool state){
	for (auto&i: rcVector){
		i.setState(state);
	}
}

filec* filecs::getData(int i) {
	return &this->rcVector[i];
}

int filecs::getNum() {
	return this->rcVector.size();
}

int filecs::getValid_num(){
	int n = 0;
	for (auto& i : rcVector) {
		if (i.isShow()) {
			++n;
		}
	}
	return n;
}