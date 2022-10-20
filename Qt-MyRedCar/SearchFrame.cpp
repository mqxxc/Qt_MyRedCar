#include "SearchFrame.h"

SearchFrame::SearchFrame(QWidget* prerte){
	ui.setupUi(this);
	if (prerte != Q_NULLPTR) {
		setParent(prerte);
	}
	//³õÊ¼»¯
	init();
}

SearchFrame::~SearchFrame(){

}

void SearchFrame::init(){
	initUi();
}

void SearchFrame::initUi(){
	/*ui.text->setFont(QFont("Timers", 16, QFont::Bold));
	ui.text->setPlaceholderText(u8"ËÑË÷");*/
	QTextEdit* pEditTmp = new QTextEdit;
	QPushButton* pBtnTmp = new QPushButton(QString::fromLocal8Bit("¸´ÖÆ"));

	QHBoxLayout* pEditTmpLayout = new QHBoxLayout(pEditTmp);
	pEditTmpLayout->setSpacing(0);
	pEditTmpLayout->setMargin(0);
	pEditTmpLayout->addWidget(pBtnTmp);
	pEditTmpLayout->setAlignment(pBtnTmp, Qt::AlignBottom | Qt::AlignRight);

	QVBoxLayout* pMainLayout = new QVBoxLayout();
	pMainLayout->setMargin(50);
	pMainLayout->setSpacing(50);
	pMainLayout->addWidget(pEditTmp);
	pMainLayout->addStretch();

	this->setLayout(pMainLayout);

}
