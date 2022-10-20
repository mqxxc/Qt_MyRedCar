#pragma once
#include<QGraphicsObject>
#include<QGraphicsView>
class QPropertyAnimation;
namespace Ui { class Loading; }
#pragma execution_character_set("utf-8")


class Item : public QGraphicsObject {

	Q_OBJECT

private:
	bool change;									 //是否翻转
	QMap<int,QPixmap> pixmapList;					 //图片列表
	int index;										 //当前显示的图片的下标
	QPropertyAnimation* m_roateAnimation;			 //m_itemRotation的动画 
	QRect rect;										 //图元绘制矩形

public:
	Item(QRect rect);
	~Item();
//设置私有变量
	void addPoxmap(int i,QString path);

private:
	QRectF boundingRect() const;				//确认场景大小定下绘制比例
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
		QWidget* widget);						//图元重绘函数

signals:
	void next();								//下一个图元开始旋转

private slots:
	void animationValueChanged(const QVariant& value);	//开始旋转
	void animationFinished();							//旋转完成

public slots:
	void animationStart();								//此图元开始旋转
};

class View:public QGraphicsView {

	Q_OBJECT

private:
	QGraphicsScene* scene;
	QList<Item*> items;
	QString path;

public:
	View();
	~View();

	void strat();
	QString getPath();
	
private:
	void init();
	void initMember();
	void initUi();
	void getExePath();
	void connects();

private slots:
	void drawBackground(QPainter* painter, const QRectF& rect);
	void wheelEvent(QWheelEvent* e);
};

class Loading :public QWidget {

	Q_OBJECT
		
private:
	Ui::Loading* ui;
	View* view;
	QTimer* time;
	int sum;
	bool state;
	QString pohotoPath;

public:
	Loading();
	~Loading();
	void ing();
	
private slots:
	void middleChange();
	void wheelEvent(QWheelEvent* e);
};