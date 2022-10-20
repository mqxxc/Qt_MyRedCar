#pragma once
namespace Ui { class Unit; }
#include<QWidget>
class QMenu;
class QEventLoop;
class Msg;
#pragma execution_character_set("utf-8")					


class Unit:public QWidget{

	Q_OBJECT

private:
	Ui::Unit* ui;								//ui����
	QMenu* rMenu;								//�Ҽ��˵�
	QAction** menuList;							//�˵���
	QEventLoop* input_loop;						//�������ı��������¼�ѭ��
	Msg* rc;									//��Դ��
	QString photo;								//ͼƬ·��
	int id;										//��ԪID

	static int widW;							//���ڿ�
	static int selectId;						//��ѡ�еĵ�Ԫ��id
	static QString exePath;						//��������·��


public:
	Unit(Msg* rc,int id, QWidget* parent = Q_NULLPTR);
	~Unit();
	static void setScaling(float scaling);		//���ô������ű���
	static int getWid_W();						//��ȡ���ڴ�С
	static int getUnit_Id();					//��ȡ��ǰѡ�еĵ�Ԫid��
	static void setExe_Path(QString path);		//���ó�������·��
	void onRelease();							//ȡ��ѡ��

private:
	void initUi();								//��ʼ��ui����
	void initMember();							//��ʼ������
	void initR_Menu();							//��ʼ���Ҽ��˵�
	void setWid_W();							//���ô��ڵĿ�
	void onSelect();							//��ѡ��
	void menuFinish();							//�������˵��������
	void up_UnitPath(QString name);				//�޸ĵ�Ԫ�����Լ�ͼƬ·��

signals:
	void upUnits(int oldId);					//�������ָ��id�ŵĵ�Ԫ״̬
	void rename_sig(int id,QString name);		//�������ź�
	void delete_sig(int id);					//ɾ���ź�

private slots:
	void mousePressEvent(QMouseEvent* ev);				//��갴����Ϣ
	bool eventFilter(QObject* object, QEvent* event);   //�ӿؼ��¼�������
	//�Ҽ��˵�����
	/*dxg�Ժ���windows���ӽ�����������������*/
	void menuRename(bool b);					//������
	void menuIsLove(bool b);					//�Ƿ�ϲ��
	void menuDelete(bool b);					//ɾ��
	//bool event(QEvent* event) override;				//�������˫���¼�
};