#pragma once
#include "getScreenInformation_global.h"
#pragma execution_character_set("utf-8")

class INITDLL_EXPORT getScreenInformation {
public:
    getScreenInformation();
    virtual QString getPath();                       //��ȡ��������·��
    virtual QPoint getWid_workSize();                //��ȡ���湤�����Ĵ�С
    virtual float getLogicRatio();                   //��ȡ��ʾ���뿪������Ļ�߼�����
    virtual float getPhysicsRatio();                 //��ȡϵͳ���ű�
    virtual QString getName();                       //��ȡӦ�õ�����
};

extern "C" INITDLL_EXPORT getScreenInformation * getClassobj();