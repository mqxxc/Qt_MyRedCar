#pragma once
#include"../Screenshot/Screenshot.h"
#include<QWidget>
class Unit;
class DetaHandle;
namespace Ui { class RcWidget; }


//������Ϣ����
struct winMag {
	int spaceW;			//��϶��
	int unitW;			//��Ԫ��
	int rowN;			//һ�д�ŵ�Ԫ����
	int offset;			//����ƫ����
};

class RcWidget :public QWidget {

	Q_OBJECT

private:
	Ui::RcWidget* ui;
	int widW;							//���ڿ�
	int widH;							//���ڸ�
	DetaHandle* rc;						//��Դ�ļ���
	QString path;						//��������·��
	QMap<char,Unit*> units;				//ͼ��Ԫ��
	winMag unitMag;						//��Ԫ�����Ϣ
	int lastUnitX;						//���ĵ�ԪXλ��
	int lastUnitY;						//���ĵ�ԪYλ��
	QList<int> idList;					//��Ԫ��ʾ˳��
	char controlSig;					//�����ź�
	/*    
	*���ұߵ�һλ�����Ƿ�ˢ�£��ڶ�Ϊ�ж�������ߵ��򣬵���λ--����λ������������
	*1.	Ϊ1��ˢ�µ�Ԫ
	*2.	Ϊ1������Ϊ0����
	*3---6.  3Ϊ1-���֣�4Ϊ1-���ʱ�䣻5Ϊ1-���ʹ�ã�6Ϊ1-ϲ����
	*/
	//bool isRefresh;						//�Ƿ�ˢ�µ�Ԫ
	//bool orderState;					//true--����false--������
	//char oldCondition;					//�ϴ�ֵ�ı������

public:
	RcWidget(QWidget* parent = Q_NULLPTR);
	~RcWidget();
	void setScaling(float Scaling);					//�������ű���
	void setPath(QString path);						//���ó���·��
	bool moveFile(QString path);					//ת���ļ�
	void refresh();									//ˢ����Դ��ԪΪȫ��ʾ

private:
	//���Գ�ʼ����Դ
	void initRc();
	//��ȡ�����ļ�
	//bool redRecord();						//��ȡ��һ�ιر�ʱ����Դ��¼�ļ�
	//void redRc_Name(QString* names);		//��ȡ������Դ�ļ����е�����
	void redLocal_Rc();						//��ȡ������Դ�ļ����е���Դ
	//������Դ��Ϣ������
	//void saveRc_to_local();					
	//�ӿؼ���ز���
	void initMember();					//��ʼ����Ա����
	void initUnitSize();				//��ʼ��ͼ��Ԫ��С
	void initUnit(int i);				//��i��ʼ��ʼ����Ԫ
	void refreshUnit();					//ˢ�����е�Ԫ
	//������������
	void showUnit(int sum);				//�������õ�Ԫ
	void addUnit();						//���unit��Ԫ
	void reckonNext();					//������һ����Ԫ��λ��

signals:
	void selectUnit(QString path);				//ѡ�е�Ԫ��Ϣ
	void up_ScrSize_sig(int range);				//��������С����
	void up_ScrValue(int value,bool code=true);	//������λ�ø���
	void newFinish();							//��ʼ�����

public slots:
	void release(int id);						//ѡ�е�Ԫȡ��ѡ��������Ԫ
	void fileRename(int id,QString name);		//�ļ�������
	void fileDelete(int id);					//�ļ�ɾ��
	void up_ScrSize();							//���¹�������С
	void moveUnit(int offset);					//�����ƶ�unit��Ԫ
	void searchUnit(QString name);				//ɸѡ��Ԫ
	void changeCondition(int condition);		//�޸ĵ�Ԫ���������
	void changeOrder(bool state);				//�ı䵥Ԫ��˳��

private slots:
	void resizeEvent(QResizeEvent* e);			//��С�ı��¼�
	void wheelEvent(QWheelEvent* e);			//�������¼�
	void mousePressEvent(QMouseEvent* event);	//������¼�
};