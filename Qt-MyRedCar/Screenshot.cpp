#include "Screenshot.h"

//VideoSurface class
VideoSurface::VideoSurface(QObject* parent) :QAbstractVideoSurface(parent){

}

VideoSurface::~VideoSurface(){
    this->stop();
}

QList<QVideoFrame::PixelFormat> VideoSurface::
supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const{
    
    QList<QVideoFrame::PixelFormat> listPixelFormats;

    listPixelFormats.append(QVideoFrame::Format_ARGB32);
    listPixelFormats.append(QVideoFrame::Format_ARGB32_Premultiplied);
    listPixelFormats.append(QVideoFrame::Format_RGB32);
    listPixelFormats.append(QVideoFrame::Format_RGB24);
    listPixelFormats.append(QVideoFrame::Format_RGB565);
    listPixelFormats.append(QVideoFrame::Format_RGB555);
    listPixelFormats.append(QVideoFrame::Format_ARGB8565_Premultiplied);
    listPixelFormats.append(QVideoFrame::Format_BGRA32);
    listPixelFormats.append(QVideoFrame::Format_BGRA32_Premultiplied);
    listPixelFormats.append(QVideoFrame::Format_BGR32);
    listPixelFormats.append(QVideoFrame::Format_BGR24);
    listPixelFormats.append(QVideoFrame::Format_BGR565);
    listPixelFormats.append(QVideoFrame::Format_BGR555);
    listPixelFormats.append(QVideoFrame::Format_BGRA5658_Premultiplied);

    listPixelFormats.append(QVideoFrame::Format_Jpeg);

    listPixelFormats.append(QVideoFrame::Format_CameraRaw);
    listPixelFormats.append(QVideoFrame::Format_AdobeDng);

    return listPixelFormats;
}

bool VideoSurface::present(const QVideoFrame& frame){
    if (frame.isValid()) {
        emit frameAvailable(frame);
        return true;
    }
    else {
        emit finish();
        return false;
    }  
}

//Screenshot class
Screenshot::Screenshot(){
    qRegisterMetaType<QVideoFrame>("QVideoFrame&");
    mediaPlayer = new QMediaPlayer;
    videoOut = new VideoSurface;
    success = false;
    mediaPlayer->setVideoOutput(videoOut);
    mediaPlayer->setMuted(true);
    connect(videoOut, &VideoSurface::frameAvailable, 
        this, &Screenshot::ProcessFrame, Qt::QueuedConnection);
    connect(videoOut, &VideoSurface::finish,
        this, &Screenshot::emitFinish, Qt::QueuedConnection);
}

Screenshot::~Screenshot(){
    delete mediaPlayer;
    delete videoOut;
}

bool Screenshot::isSuccess(){
    return success;
}

void Screenshot::ProcessFrame(QVideoFrame frame){
    static int count = 0;
    count++;
    if (count == 5){
        mediaPlayer->pause();
        frame.map(QAbstractVideoBuffer::ReadOnly);
        int w = frame.width();
        int h = frame.height();
        QImage recvImage(frame.bits(), w, h, QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat()));
        recvImage = recvImage.copy((w-h) / 2, 0, h, h);
        recvImage.save(savePath.arg(count), "JPG");
        frame.unmap();
        success = true;
        emit finish();
    }
}

void Screenshot::emitFinish(){
    emit finish();
}

void Screenshot::getJpg(QString path) {
    mediaPlayer->setMedia(QUrl(path));
    savePath = path.left(path.lastIndexOf(".")).append("z.jpg");
    mediaPlayer->play();
}