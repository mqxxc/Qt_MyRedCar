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

    virtual bool pathExist();           //���·���ļ��ܷ���Լ���һ�������Ƿ�Ϊ��
    virtual void saveFile();            //�����¼������
    virtual void readFile();            //��ȡ���ؼ�¼
};

extern "C" SAVEORREAD_EXPORT SaveOrRead* getSOR(QString filePath, QList<QString>* list);