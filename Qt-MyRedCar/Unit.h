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
	Ui::Unit* ui;								//ui界面
	QMenu* rMenu;								//右键菜单
	QAction** menuList;							//菜单项
	QEventLoop* input_loop;						//重命名文本输入框的事件循环
	Msg* rc;									//资源类
	QString photo;								//图片路径
	int id;										//单元ID

	static int widW;							//窗口宽
	static int selectId;						//被选中的单元的id
	static QString exePath;						//程序运行路径


public:
	Unit(Msg* rc,int id, QWidget* parent = Q_NULLPTR);
	~Unit();
	static void setScaling(float scaling);		//设置窗口缩放比例
	static int getWid_W();						//获取窗口大小
	static int getUnit_Id();					//获取当前选中的单元id号
	static void setExe_Path(QString path);		//设置程序运行路径
	void onRelease();							//取消选中

private:
	void initUi();								//初始化ui界面
	void initMember();							//初始化变量
	void initR_Menu();							//初始化右键菜单
	void setWid_W();							//设置窗口的宽
	void onSelect();							//被选中
	void menuFinish();							//重命名菜单操作完成
	void up_UnitPath(QString name);				//修改单元名字以及图片路径

signals:
	void upUnits(int oldId);					//请求更新指定id号的单元状态
	void rename_sig(int id,QString name);		//重命名信号
	void delete_sig(int id);					//删除信号

private slots:
	void mousePressEvent(QMouseEvent* ev);				//鼠标按键消息
	bool eventFilter(QObject* object, QEvent* event);   //子控件事件监听器
	//右键菜单处理
	/*dxg以后用windows钩子解决重命名输入框问题*/
	void menuRename(bool b);					//重命名
	void menuIsLove(bool b);					//是否喜欢
	void menuDelete(bool b);					//删除
	//bool event(QEvent* event) override;				//屏蔽鼠标双击事件
};