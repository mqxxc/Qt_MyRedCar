#pragma once
#include "saveorread_global.h"
#include<QString>

class SAVEORREAD_EXPORT SaveOrRead{

private:
    QList<QString>* list;
    QString path;

public:
    SaveOrRead(QString path, QList<QString>* list);
    virtual ~SaveOrRead();

    virtual bool pathExist();           //监测路径文件能否打开以及第一行内容是否为空
    virtual void saveFile();            //保存记录到本地
    virtual void readFile();            //读取本地记录
};

extern "C" SAVEORREAD_EXPORT SaveOrRead* getSOR(QString filePath, QList<QString>* list);