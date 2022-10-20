#pragma once
#include "getScreenInformation_global.h"
#pragma execution_character_set("utf-8")

class INITDLL_EXPORT getScreenInformation {
public:
    getScreenInformation();
    virtual QString getPath();                       //获取程序运行路径
    virtual QPoint getWid_workSize();                //获取桌面工作区的大小
    virtual float getLogicRatio();                   //获取显示屏与开发机屏幕逻辑比例
    virtual float getPhysicsRatio();                 //获取系统缩放比
    virtual QString getName();                       //获取应用的名字
};

extern "C" INITDLL_EXPORT getScreenInformation * getClassobj();