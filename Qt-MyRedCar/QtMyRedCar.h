#pragma once
#include<QWidget>
class playVideo;
class Elastic;
class QLibrary;
class QLineEdit;
class QPushButton;
namespace Ui { class QtMyRedCar; }
#pragma execution_character_set("utf-8")

class QtMyRedCar : public QWidget{

    Q_OBJECT 

private:
    Ui::QtMyRedCar* ui;
    Elastic* evenRoot;      //窗口移动缩放管理者
    QSize leftTop_point;    //左上角坐标
    int old_SrcValue;       //滚动条的value值
    playVideo* player;      //右上角视频播放器
    QLibrary* dll;          //库实例
    QString path;           //选中的视频路径
    QLineEdit* input;       //搜索输入框
    QPushButton* button;    //搜索按钮
    bool minState;          ///最大化最小化按钮的状态
    bool orderState;        //true--顺序，false--倒序

    QString exePath;

public:
    QtMyRedCar(QWidget *parent = Q_NULLPTR);
    ~QtMyRedCar();

private:
//联系信号与信号槽
    void connects();    
//初始化控件样式   
    void initMember();                                              //初始化变量
    void initWid(QPoint& workSize,float& ration);                   //初始化窗口
    void initUi(float& ration);                                     //初始化窗口Ui
//其他初始化操作
    //top   
    void initSearch();                      
    //right
    void initVidewid();

signals:
    //title
    void mainWidClear();                                //窗口最小化托盘消息
    //top
    void changeOrder(bool state);                       //修改正序or倒叙
    //middle
    void upUnitSrc(int value);                          //通过滑块值更新资源窗口
    void search(QString name);                          //搜索信号
    //bottom
    void mainExit();                                    //主程序退出
    void upDesk(QString path);                          //更换壁纸
    //other
    void loaded();                                      //主窗口加载完成信号

private slots:
    //title
    void on_maxsize_clicked();                          //最大化最小化按钮
    void on_off_clicked();                              //关闭按钮
    //top
    void on_filter_clicked();                           //筛选按钮
    void on_order_clicked();                            //正序or倒叙
    void on_setbox_clicked();                           //设置按钮
    //middle
    void setSrcSize(int range);                         //更新滚动条大小
    void setSrcValue(int value,bool code);              //更新滑块的值
    void changeValue(int value);                        //转化移动值
    void emitLoaded();                                  //资源窗口加载完成稿
    //bottom
    void on_originality_clicked();                      //浏览创意工坊
    void on_about_clicked();                            //嘤起up
    void on_lod_clicked();                              //加载本地文件
    void on_Refresh_clicked();                          //刷新
    //right
    void on_deletebo_clicked();                         //移除壁纸
    void on_OK_clicked();                               //更换壁纸
    void on_endbo_clicked();                            //退出程序
    void previewVideo(QString path);                    //预览窗口播放视频
    bool eventFilter(QObject* obj, QEvent* even);       //事件过滤器
};