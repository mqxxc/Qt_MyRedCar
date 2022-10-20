/*
*
* ������39
* �������ڣ�2022.05.xx
* ���һ���޸����ڣ�2022.05.24
* ���ߣ��������ǳ�
* 
*/
#include<QString>
#include<QCoreApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QSize>
#include "getScreenInformation.h"
#define PointDistance 96         //windows�涨���Ϊ96


getScreenInformation::getScreenInformation(){

}

getScreenInformation* getClassobj() {
    return new getScreenInformation();
}

QString getScreenInformation::getPath(){
	return QCoreApplication ::applicationDirPath();
}

QPoint getScreenInformation::getWid_workSize(){
    QSize work = QGuiApplication::primaryScreen()->availableSize();  //��������С
    return QPoint(work.width(),work.height());
}

float getScreenInformation::getLogicRatio(){
    QSize l = QGuiApplication::primaryScreen()->geometry().size();
    return l.width()/1920.0;
}

float getScreenInformation::getPhysicsRatio(){
    qreal phy = QGuiApplication::primaryScreen()->logicalDotsPerInchX()/ PointDistance;
    return (float)phy;
}

QString getScreenInformation::getName(){
    return QCoreApplication::applicationFilePath().section("/",-1,-1).section(".",0,0);
}
