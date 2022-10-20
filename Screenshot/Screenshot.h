#pragma once
#include "screenshot_global.h"
#include<QObject>
#pragma execution_character_set("utf-8")
#include <QtMultimedia/QAbstractVideoSurface>

class QMediaPlayer;
class QEventLoop;


class VideoSurface : public QAbstractVideoSurface {
    Q_OBJECT

public:
    VideoSurface(QObject* parent = Q_NULLPTR);

    virtual QList<QVideoFrame::PixelFormat>
        supportedPixelFormats
        (QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;
    virtual bool present(const QVideoFrame& frame);

signals:
    void frameAvailable(QVideoFrame frame);
    void finish();
};


class Screenshot : public QObject {
private:
    QMediaPlayer* mediaPlayer;
    VideoSurface* videoOut;
    QString savePath;
    bool success;
    QEventLoop* loop;

public:
    Screenshot();
    virtual ~Screenshot();
    virtual bool isSuccess();
    virtual void getJpg(QString path);
    virtual void setLoop(QEventLoop* loop);
    virtual void finish();

private:
    virtual void ProcessFrame(QVideoFrame frame);

};

extern "C" SCREENSHOT_EXPORT Screenshot * getScrObj();