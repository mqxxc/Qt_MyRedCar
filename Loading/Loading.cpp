#include "Loading.h"
#include"ui_Loading.h"
#include<QGraphicsScene>
#include<QPropertyAnimation>
#include<QParallelAnimationGroup>
#include<QGraphicsRotation>
#include<QLibrary>
#include<QTimer>
#include<QSplashScreen>
#include"../getScreenInformation/getScreenInformation.h"


//Item
Item::Item(QRect rect) {
    index = 0;
    change = true;
    this->rect = rect;
    //设置该item的变换
    QGraphicsRotation* m_itemRotation = new QGraphicsRotation(this);
    m_itemRotation->setAxis(Qt::YAxis); //沿Y轴旋转
    m_itemRotation->setOrigin(QVector3D((rect.x()+rect.width()/2), 0, 0)); //旋转基准位置为item的中心线
    this->setTransformations(QList<QGraphicsTransform*>() << m_itemRotation);//<--关键-->

    //动画效果
    m_roateAnimation = new QPropertyAnimation(m_itemRotation, "angle"); //动画与m_itemRotation绑定
    m_roateAnimation->setDuration(1500);
    m_roateAnimation->setStartValue(0);
    m_roateAnimation->setEndValue(180);
    connect(m_roateAnimation, SIGNAL(finished()), this, SLOT(animationFinished()));
    connect(m_roateAnimation, SIGNAL(valueChanged(QVariant)), this, SLOT(animationValueChanged(QVariant)));
}

Item::~Item(){
    delete m_roateAnimation;
}

void Item::addPoxmap(int i,QString path){
    QPixmap pixmap(path);
    pixmap = pixmap.scaled(rect.width(), rect.height(), Qt::KeepAspectRatioByExpanding);
    pixmapList[i]=pixmap;
    QImage img(path);
    img = img.mirrored(true, false);
    pixmapList[3-i] = QPixmap::fromImage(img);
}

QRectF Item::boundingRect() const{
    return QRectF(0,0,900,520);
}

void Item::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
    painter->drawPixmap(rect,pixmapList[index]);
}

void Item::animationValueChanged(const QVariant& value) {
    if (change) {
        if (value.toFloat() >= 88 && value.toFloat() <= 92) {
            if (++index >= pixmapList.size()) {
                index = 0;
            }
            change = false;
            update();
        }
    }
}

void Item::animationFinished() {
    emit next();
}

void Item::animationStart(){
    if (!change) {
        if (++index >= pixmapList.size()) {
            index = 0;
        }
    }
    change = true;
    m_roateAnimation->start();
}

//View
View::View(){
	//初始化
	init();
    connects();
}

View::~View(){
    for (auto& i : items) {
        delete i;
    }
    delete scene;
}

void View::strat(){
    items[0]->animationStart();
}

QString View::getPath(){
    return path;
}

void View::init(){
	initMember();
	initUi();
}

void View::initMember(){
    getExePath();
    scene = new QGraphicsScene;
}

void View::initUi(){
    this->setScene(scene);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setViewportUpdateMode(FullViewportUpdate);   //刷新方式
    setCacheMode(CacheBackground);
    setRenderHints(QPainter::Antialiasing
        | QPainter::SmoothPixmapTransform
        | QPainter::TextAntialiasing);

    Item* temp1 = new Item(QRect(20,  10, 164, 500));
    Item* temp2 = new Item(QRect(194, 10, 164, 500));
    Item* temp3 = new Item(QRect(542, 10, 164, 500));
    Item* temp4 = new Item(QRect(716, 10, 164, 500));
    items.append(temp1);
    items.append(temp2);
    items.append(temp3);
    items.append(temp4);
    items[0]->addPoxmap(0,path + "q22_10.jpg");
    items[0]->addPoxmap(1,path + "22_10.jpg");
    items[1]->addPoxmap(0,path + "q33_20.jpg");
    items[1]->addPoxmap(1,path + "33_20.jpg");
    items[2]->addPoxmap(0,path + "q33_40.jpg");
    items[2]->addPoxmap(1,path + "33_40.jpg");
    items[3]->addPoxmap(0,path + "q22_50.jpg");
    items[3]->addPoxmap(1,path + "22_50.jpg");
    for (int  i = 0; i < 4; ++i){
        scene->addItem(items[i]);
    }
    this->resize(900, 520);
   
}

void View::getExePath(){
    QLibrary pathDll("getScreenInformation");
    if (pathDll.load()) {
        getScreenInformation* gScrIn =
            ((getScreenInformation * (*)())(pathDll.resolve("getClassobj")))();

        path = gScrIn->getPath();
        delete gScrIn;
        pathDll.unload();
        path.append("/rc/Loading/");
    }
}

void View::connects(){
    connect(items[0], &Item::next, items[1], &Item::animationStart);
    connect(items[1], &Item::next, items[2], &Item::animationStart);
    connect(items[2], &Item::next, items[3], &Item::animationStart);
    connect(items[3], &Item::next, items[0], &Item::animationStart);
}

void View::wheelEvent(QWheelEvent* e){
}

void View::drawBackground(QPainter* painter, const QRectF& rect) {
    painter->drawPixmap(rect, QPixmap(path+"backdrop.jpg"), QRectF());
}

//Loading
Loading::Loading() {
    ui = new Ui::Loading;
    ui->setupUi(this);
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    setFixedSize(900, 520);
    view = new View;
    view->setParent(this);
    ui->middle->raise();
    time = new QTimer;
    connect(time,&QTimer::timeout,this,&Loading::middleChange);
    sum = 0;
    state = false;
    pohotoPath = view->getPath()+"22330.jpg";
}

Loading::~Loading(){
    delete view;
    time->stop();
    delete time;
    delete ui;
}

void Loading::ing() {
    show();
    QTimer::singleShot(10, this, [=]() {
        view->strat();
        time->start(525);
        });
    
}

void Loading::wheelEvent(QWheelEvent* e){
    return;
}

void Loading::middleChange() {
    if (state) {
        if (sum == 0) {
            state = false;
        }
        else {
            sum -= 10;
        }
    }
    else {
        if (sum == 100) {
            state = true;
        }
        else {
            sum += 10;
        }
    }
    QPixmap pixmap(pohotoPath);
    QPixmap temp(pixmap.size());
    temp.fill(Qt::transparent);
    QPainter painter(&temp);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.drawPixmap(0, 0, pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    painter.fillRect(temp.rect(), QColor(0, 0, 0, 2.5*sum));
    painter.end();
    ui->middle->setPixmap(temp);
}