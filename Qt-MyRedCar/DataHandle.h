#pragma once
#include<QMap>

class Msg {

public:
	enum class Source :std::uint8_t {//来源枚举
		CRAFT = 0,			//创意工坊
		LOCAL = 1,			//本地
		INTERNET = 2		//网络
	};

private:
	QString name;				//资源名字
	QString photo;				//预览图路径
	QString video;				//视频路径
	QString importTime;			//导入时间
	QString useTime;			//最后一次使用时间
	Source source;				//来源
	char state;					//状态
	/*state说明
	*从右到左
	* 1.为1则喜欢，为0为非喜欢
	* 2.为1则隐藏，为0则没有隐藏
	*/

public:
	Msg(QString name,QString video,QString photo,
		QString importTime,QString Source,QString useTime,QString state);
	Msg(QString fileName,QString time,bool success=true);
	Msg(QString fileName,QString videoNmae,QString photoName,QString time="",
		bool success = true);

	//访问私有成员
	QString getName();
	QString getPhoto(bool save=false);
	QString getVideo(bool save=false);
	QString getImport_time();
	QString getSource();
	QString getUse_time();
	bool getLove();
	bool isHide();
	char getState();
	//设置私有成员
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
	//	NMAE = 0,			//名字
	//	PHOTO = 1,			//图片
	//	VIDEO = 2,			//视频
	//	IMPORTTIME = 3,		//导入时间
	//	USETIME = 4,		//最后一次使用时间
	//	SOURCE = 5,			//来源
	//	LOVE = 6,			//是否喜欢
	//	DELETE = 7,			//删除
	//	HIDE = 8			//是否隐藏
	//};

private:
	QMap<char, Msg*> database;			//数据集

public:
	DetaHandle();
	~DetaHandle();
	//数据增删改查
	void addData(QString fileNmae,bool success=true);
	void addData(Msg* msg);
	void deleteData(char id);
	//void updataData(char id,Term term,QString newValue);
	Msg* getData(char id);
	//其他
	int getNum();								//统计资源数
	//int getValidNum();							//统计可供显示的资源数
	void refresh(bool state);					//全部设置为显示状态
	
private:
	void saveMsg();								//保存数据到本地
	void readMsg();								//从本地读取数据
};