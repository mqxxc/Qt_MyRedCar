#pragma once
#include"ui_SearchFrame.h"
#include<QTextEdit>
#include<QHBoxLayout>

class SearchFrame : public QWidget {
	Q_OBJECT

public:

private:
	Ui::SearchFrame ui;

public:
	SearchFrame(QWidget* prerte=Q_NULLPTR);
	~SearchFrame();
	
private:
	void init();
	void initUi();
};