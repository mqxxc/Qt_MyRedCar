/*
*
* �������ڣ�2022.06.15
* ���һ���޸����ڣ�2022.07.02
* ���ߣ��������ǳ�
*
*/
#include"ui_About.h"
#include"About.h"
#include<QClipboard>
#include<QCloseEvent>

About::About(QObject* parent):ui(new Ui::About){
	ui->setupUi(this);
	setWindowFlag(Qt::Tool);

	this->show();
	loop=new QEventLoop(this);
	loop->exec();
}

About::~About(){
	delete ui;
	delete loop;
}

void About::closeEvent(QCloseEvent* e){
	loop->exit();
}

void About::on_copy_clicked(){
	QClipboard* clip = QApplication::clipboard();
	clip->setText(ui->mage->toPlainText());
}