/*
*
* 创建日期：2022.05.24
* 最后一次修改日期：2022.06.21
* 作者：寐晴下星辰
* 
*/
#include "playVideo.h"
#include<QWidget>
#include<QtMultimedia/QMediaPlayer>
#include<QtMultimediaWidgets/QVideoWidget>
#include<QtMultimedia/QMediaPlaylist>

playVideo::playVideo(QWidget* parent){
	player = new QMediaPlayer();
	video = new QVideoWidget(parent);
	video->resize(parent->size());
	video->show();
	list = new QMediaPlaylist();
	player->setPlaylist(list);
	player->setVideoOutput(video);
	player->duration();
	connect(player, &QMediaPlayer::positionChanged, this, &playVideo::getduration);
}

playVideo::~playVideo(){
	stopPlay();
	delete player;
	delete video;
	delete list;
}


void playVideo::setVideo(QString vpath){
	list->clear();
	list->addMedia(QUrl(vpath));
}

void playVideo::flyVideo(){
	player->play();
}

void playVideo::setVolume(int volume){
	player->setVolume(volume);
}

void playVideo::stopPlay(){
	player->stop();
	list->clear();
}

void playVideo::pauseVideo(){
	player->pause();
}

void playVideo::startVideo(){
	player->play();
}

void playVideo::refreshLoop(){
	player->setPosition(0);
}

void playVideo::getduration(qint64 playtime) {
	if (playtime>player->duration()-1000) {
		player->setPosition(0);
	}
}

playVideo* getpvobj(QWidget* parent){
	return new playVideo(parent);
}