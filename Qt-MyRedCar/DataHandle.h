#pragma once
#include<QMap>

class Msg {

public:
	enum class Source :std::uint8_t {//��Դö��
		CRAFT = 0,			//���⹤��
		LOCAL = 1,			//����
		INTERNET = 2		//����
	};

private:
	QString name;				//��Դ����
	QString photo;				//Ԥ��ͼ·��
	QString video;				//��Ƶ·��
	QString importTime;			//����ʱ��
	QString useTime;			//���һ��ʹ��ʱ��
	Source source;				//��Դ
	char state;					//״̬
	/*state˵��
	*���ҵ���
	* 1.Ϊ1��ϲ����Ϊ0Ϊ��ϲ��
	* 2.Ϊ1�����أ�Ϊ0��û������
	*/

public:
	Msg(QString name,QString video,QString photo,
		QString importTime,QString Source,QString useTime,QString state);
	Msg(QString fileName,QString time,bool success=true);
	Msg(QString fileName,QString videoNmae,QString photoName,QString time="",
		bool success = true);

	//����˽�г�Ա
	QString getName();
	QString getPhoto(bool save=false);
	QString getVideo(bool save=false);
	QString getImport_time();
	QString getSource();
	QString getUse_time();
	bool getLove();
	bool isHide();
	char getState();
	//����˽�г�Ա
	void setName(QString name);
	void setPhoto(QString path);
	void setVideo(QString path);
	void setImport_time(QString time);
	void setUse_time(QString time);
	void setSource(Source source);
	void setLove(bool value);
	void setHide(bool value);
};

class DetaHandle{

public:
	//enum class Term :std::uint16_t {
	//	NMAE = 0,			//����
	//	PHOTO = 1,			//ͼƬ
	//	VIDEO = 2,			//��Ƶ
	//	IMPORTTIME = 3,		//����ʱ��
	//	USETIME = 4,		//���һ��ʹ��ʱ��
	//	SOURCE = 5,			//��Դ
	//	LOVE = 6,			//�Ƿ�ϲ��
	//	DELETE = 7,			//ɾ��
	//	HIDE = 8			//�Ƿ�����
	//};

private:
	QMap<char, Msg*> database;			//���ݼ�

public:
	DetaHandle();
	~DetaHandle();
	//������ɾ�Ĳ�
	void addData(QString fileNmae,bool success=true);
	void addData(Msg* msg);
	void deleteData(char id);
	//void updataData(char id,Term term,QString newValue);
	Msg* getData(char id);
	//����
	int getNum();								//ͳ����Դ��
	//int getValidNum();							//ͳ�ƿɹ���ʾ����Դ��
	void refresh(bool state);					//ȫ������Ϊ��ʾ״̬
	
private:
	void saveMsg();								//�������ݵ�����
	void readMsg();								//�ӱ��ض�ȡ����
};