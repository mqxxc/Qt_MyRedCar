#pragma once
#include"../Screenshot/Screenshot.h"
#include<QWidget>
class Unit;
class DetaHandle;
namespace Ui { class RcWidget; }


//窗口信息集合
struct winMag {
	int spaceW;			//间隙宽
	int unitW;			//单元宽
	int rowN;			//一行存放单元个数
	int offset;			//两边偏移量
};

class RcWidget :public QWidget {

	Q_OBJECT

private:
	Ui::RcWidget* ui;
	int widW;							//窗口宽
	int widH;							//窗口高
	DetaHandle* rc;						//资源文件集
	QString path;						//程序运行路径
	QMap<char,Unit*> units;				//图像单元集
	winMag unitMag;						//单元相关信息
	int lastUnitX;						//最后的单元X位置
	int lastUnitY;						//最后的单元Y位置
	QList<int> idList;					//单元显示顺序
	char controlSig;					//控制信号
	/*    
	*从右边第一位管理是否刷新，第二为判断正序或者倒序，第三位--第六位管理排序依据
	*1.	为1则刷新单元
	*2.	为1则正序，为0则倒序
	*3---6.  3为1-名字；4为1-添加时间；5为1-最后使用；6为1-喜欢。
	*/
	//bool isRefresh;						//是否刷新单元
	//bool orderState;					//true--正序，false--倒序列
	//char oldCondition;					//上次值改变的条件

public:
	RcWidget(QWidget* parent = Q_NULLPTR);
	~RcWidget();
	void setScaling(float Scaling);					//设置缩放比例
	void setPath(QString path);						//设置程序路径
	bool moveFile(QString path);					//转移文件
	void refresh();									//刷新资源单元为全显示

private:
	//尝试初始化资源
	void initRc();
	//读取本地文件
	//bool redRecord();						//读取上一次关闭时的资源记录文件
	//void redRc_Name(QString* names);		//读取本地资源文件夹中的名字
	void redLocal_Rc();						//读取本地资源文件夹中的资源
	//保存资源信息到本地
	//void saveRc_to_local();					
	//子控件相关操作
	void initMember();					//初始化成员变量
	void initUnitSize();				//初始化图像单元大小
	void initUnit(int i);				//从i开始初始化单元
	void refreshUnit();					//刷新所有单元
	//其他辅助函数
	void showUnit(int sum);				//辅助放置单元
	void addUnit();						//添加unit单元
	void reckonNext();					//计算下一个单元的位置

signals:
	void selectUnit(QString path);				//选中单元信息
	void up_ScrSize_sig(int range);				//滚动条大小更新
	void up_ScrValue(int value,bool code=true);	//滚动条位置更新
	void newFinish();							//初始化完成

public slots:
	void release(int id);						//选中单元取消选择其他单元
	void fileRename(int id,QString name);		//文件重命名
	void fileDelete(int id);					//文件删除
	void up_ScrSize();							//更新滚动条大小
	void moveUnit(int offset);					//上下移动unit单元
	void searchUnit(QString name);				//筛选单元
	void changeCondition(int condition);		//修改单元排序的条件
	void changeOrder(bool state);				//改变单元的顺序

private slots:
	void resizeEvent(QResizeEvent* e);			//大小改变事件
	void wheelEvent(QWheelEvent* e);			//鼠标滚轮事件
	void mousePressEvent(QMouseEvent* event);	//鼠标点击事件
};