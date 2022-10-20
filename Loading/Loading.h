#pragma once
#include<QGraphicsObject>
#include<QGraphicsView>
class QPropertyAnimation;
namespace Ui { class Loading; }
#pragma execution_character_set("utf-8")


class Item : public QGraphicsObject {

	Q_OBJECT

private:
	bool change;									 //�Ƿ�ת
	QMap<int,QPixmap> pixmapList;					 //ͼƬ�б�
	int index;										 //��ǰ��ʾ��ͼƬ���±�
	QPropertyAnimation* m_roateAnimation;			 //m_itemRotation�Ķ��� 
	QRect rect;										 //ͼԪ���ƾ���

public:
	Item(QRect rect);
	~Item();
//����˽�б���
	void addPoxmap(int i,QString path);

private:
	QRectF boundingRect() const;				//ȷ�ϳ�����С���»��Ʊ���
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
		QWidget* widget);						//ͼԪ�ػ溯��

signals:
	void next();								//��һ��ͼԪ��ʼ��ת

private slots:
	void animationValueChanged(const QVariant& value);	//��ʼ��ת
	void animationFinished();							//��ת���

public slots:
	void animationStart();								//��ͼԪ��ʼ��ת
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