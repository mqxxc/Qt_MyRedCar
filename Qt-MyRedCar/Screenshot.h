#pragma once
#include <QtMultimedia/QMediaPlayer>
#include <QDebug>
#include <QUrl>
#include <QMetaType>
#include <QtMultimedia/QAbstractVideoSurface>
#include <QtMultimedia/QVideoSurfaceFormat>
#pragma execution_character_set("utf-8")

class VideoSurface : public QAbstractVideoSurface{
    Q_OBJECT
public:
    VideoSurface(QObject* parent = Q_NULLPTR);
    ~VideoSurface();

    QList<QVideoFrame::PixelFormat>
        supportedPixelFormats
        (QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;
    bool present(const QVideoFrame& frame);

signals:
    void frameAvailable(QVideoFrame frame);
    void finish();
};


class Screenshot : public QObject {
	Q_OBJECT

private:
	QMediaPlayer* mediaPlayer;
    VideoSurface* videoOut;
    QString savePath;
    bool success;

public:
	Screenshot();
	~Screenshot();
    bool isSuccess();
    void getJpg(QString path);

private:
    void ProcessFrame(QVideoFrame frame);
    void emitFinish();

signals:
    void finish();
};