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
    Elastic* evenRoot;      //�����ƶ����Ź�����
    QSize leftTop_point;    //���Ͻ�����
    int old_SrcValue;       //��������valueֵ
    playVideo* player;      //���Ͻ���Ƶ������
    QLibrary* dll;          //��ʵ��
    QString path;           //ѡ�е���Ƶ·��
    QLineEdit* input;       //���������
    QPushButton* button;    //������ť
    bool minState;          ///�����С����ť��״̬
    bool orderState;        //true--˳��false--����

    QString exePath;

public:
    QtMyRedCar(QWidget *parent = Q_NULLPTR);
    ~QtMyRedCar();

private:
//��ϵ�ź����źŲ�
    void connects();    
//��ʼ���ؼ���ʽ   
    void initMember();                                              //��ʼ������
    void initWid(QPoint& workSize,float& ration);                   //��ʼ������
    void initUi(float& ration);                                     //��ʼ������Ui
//������ʼ������
    //top   
    void initSearch();                      
    //right
    void initVidewid();

signals:
    //title
    void mainWidClear();                                //������С��������Ϣ
    //top
    void changeOrder(bool state);                       //�޸�����or����
    //middle
    void upUnitSrc(int value);                          //ͨ������ֵ������Դ����
    void search(QString name);                          //�����ź�
    //bottom
    void mainExit();                                    //�������˳�
    void upDesk(QString path);                          //������ֽ
    //other
    void loaded();                                      //�����ڼ�������ź�

private slots:
    //title
    void on_maxsize_clicked();                          //�����С����ť
    void on_off_clicked();                              //�رհ�ť
    //top
    void on_filter_clicked();                           //ɸѡ��ť
    void on_order_clicked();                            //����or����
    void on_setbox_clicked();                           //���ð�ť
    //middle
    void setSrcSize(int range);                         //���¹�������С
    void setSrcValue(int value,bool code);              //���»����ֵ
    void changeValue(int value);                        //ת���ƶ�ֵ
    void emitLoaded();                                  //��Դ���ڼ�����ɸ�
    //bottom
    void on_originality_clicked();                      //������⹤��
    void on_about_clicked();                            //����up
    void on_lod_clicked();                              //���ر����ļ�
    void on_Refresh_clicked();                          //ˢ��
    //right
    void on_deletebo_clicked();                         //�Ƴ���ֽ
    void on_OK_clicked();                               //������ֽ
    void on_endbo_clicked();                            //�˳�����
    void previewVideo(QString path);                    //Ԥ�����ڲ�����Ƶ
    bool eventFilter(QObject* obj, QEvent* even);       //�¼�������
};