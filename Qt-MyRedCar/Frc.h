//�й���Դ�Ĳ�����
#pragma once
#include<vector>
#include<string>

using std::string;
using std::vector;
enum class Source:std::uint8_t {
	CRAFT = 0,			//���⹤��
	LOCAL = 1,			//����
	INTERNET = 2		//����
};

//�ļ��ṹ��
struct FileMag {
	string name;			//�ļ�����
	string vido;			//��Ƶ·��
	string photo;			//Ԥ��ͼ���ļ�
	string useTime;			//���һ��ʹ��ʱ��
	void conversion() {
		string temp;
		temp.assign(this->name).append("/").append(this->vido);
		this->vido.assign(temp);
		temp.assign(this->name).append("/").append(this->photo);
		this->photo.assign(temp);
	}
};


//��Դ��
class filec {

private:
	FileMag fileMag;		//�ļ���Ϣ
	bool state;				//��ʾ״̬---true����ʾ��false������ʾ 
	bool delt;				//�Ƿ�ɾ��---true��û�б�ɾ����false���Ѿ���ɾ��
	Source source;			//��Դ
	string importTime;		//����ʱ��
	bool love;				//�Ƿ�ϲ��---true��ϲ����false����ϲ��
	
public:
	filec(FileMag fileMag);
	//����˽�г�Ա
	string getPhoto();
	string getVido();
	string getName();
	string getUse_Time();
	Source getSource();
	string getImport_Time();
	bool getLove();
	bool getDelt();
	//����˽�б���
	void setState(bool state);			//������Դ��ʾ״̬
	void setScouce(char id);			//������Դ����
	void setLove(int love);				//�����Ƿ�ϲ��
	void setLTime(string time);			//�������һ�β���ʱ��
	
	//����
	bool isShow();						//�Ƿ���ʾ
	void deleteRc();					//ɾ����Դ
	void rename(string name);			//������
};


//��Դ����
class filecs {

private:
	vector<filec> rcVector;		//��Դ����

public:
	//����˽�г�Ա
	filec* getData(int i);
	//��ȡ��Դ����
	int getNum();										//��ȡȫ����Դ��
	int getValid_num();									//��ȡ����ʾ�õ���Դ��
	//�����Դ
	void addRc(filec tmp);
	void addRc(string path,bool state=true);
	//������Դ����
	void hideAll_Frc();									//����������Դ
	//void fscreen();									//����������(�Ժ���˵)TOOL
	void refresh(bool state);							//ˢ����Դ
};
