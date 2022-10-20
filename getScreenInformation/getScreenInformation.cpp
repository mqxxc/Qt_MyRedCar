/*
*
* 行数：39
* 创建日期：2022.05.xx
* 最后一次修改日期：2022.05.24
* 作者：寐晴下星辰
* 
*/
#include<QString>
#include<QCoreApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QSize>
#include "getScreenInformation.h"
#define PointDistance 96         //windows规定点矩为96


getScreenInformation::getScreenInformation(){

}

getScreenInformation* getClassobj() {
    return new getScreenInformation();
}

QString getScreenInformation::getPath(){
	return QCoreApplication ::applicationDirPath();
}

QPoint getScreenInformation::getWid_workSize(){
    QSize work = QGuiApplication::primaryScreen()->availableSize();  //工作区大小
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
