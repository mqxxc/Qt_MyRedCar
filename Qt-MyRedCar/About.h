/*
* 
* 关于窗口类
* 
*/
#pragma once
#include<QWidget>
class QEventLoop;
namespace Ui { class About; }


class About : public QWidget {

	Q_OBJECT

private:
	Ui::About* ui;
	QEventLoop* loop;

public:
	About(QObject* parent= Q_NULLPTR);
	~About();

private slots:
	void on_copy_clicked();
	void closeEvent(QCloseEvent* e);
};