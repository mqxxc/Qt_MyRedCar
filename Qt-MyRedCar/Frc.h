//有关资源的操作类
#pragma once
#include<vector>
#include<string>

using std::string;
using std::vector;
enum class Source:std::uint8_t {
	CRAFT = 0,			//创意工坊
	LOCAL = 1,			//本地
	INTERNET = 2		//网络
};

//文件结构体
struct FileMag {
	string name;			//文件名字
	string vido;			//视频路径
	string photo;			//预览图的文件
	string useTime;			//最后一次使用时间
	void conversion() {
		string temp;
		temp.assign(this->name).append("/").append(this->vido);
		this->vido.assign(temp);
		temp.assign(this->name).append("/").append(this->photo);
		this->photo.assign(temp);
	}
};


//资源类
class filec {

private:
	FileMag fileMag;		//文件信息
	bool state;				//显示状态---true：显示，false：不显示 
	bool delt;				//是否删除---true：没有被删除，false：已经被删除
	Source source;			//来源
	string importTime;		//导入时间
	bool love;				//是否喜欢---true：喜欢，false：不喜欢
	
public:
	filec(FileMag fileMag);
	//访问私有成员
	string getPhoto();
	string getVido();
	string getName();
	string getUse_Time();
	Source getSource();
	string getImport_Time();
	bool getLove();
	bool getDelt();
	//设置私有变量
	void setState(bool state);			//设置资源显示状态
	void setScouce(char id);			//设置来源类型
	void setLove(int love);				//设置是否喜欢
	void setLTime(string time);			//设置最后一次播放时间
	
	//其他
	bool isShow();						//是否显示
	void deleteRc();					//删除资源
	void rename(string name);			//重命名
};


//资源集类
class filecs {

private:
	vector<filec> rcVector;		//资源容器

public:
	//访问私有成员
	filec* getData(int i);
	//获取资源数量
	int getNum();										//获取全部资源数
	int getValid_num();									//获取能显示得到资源数
	//添加资源
	void addRc(filec tmp);
	void addRc(string path,bool state=true);
	//其他资源操作
	void hideAll_Frc();									//隐藏所有资源
	//void fscreen();									//按条件检索(以后再说)TOOL
	void refresh(bool state);							//刷新资源
};
