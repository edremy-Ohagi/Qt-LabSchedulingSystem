#ifndef EDRMAINWINDOW_H
#define EDRMAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QDate>
#include <QLabel>
#include <QMessageBox>
#include <QInputDialog>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
QT_BEGIN_NAMESPACE
namespace Ui {
class edrMainWindow;
}
QT_END_NAMESPACE
//这次的命名太乱了，像这种项目很多的下次要好好命名
struct CourseInfo
{
    QString mName;//课程名称
    QString mTeacher;//教师名称
    QString mTeacherDepar;//教师学院
    QString mStuDepar;//学生学院
    QString mClass;//班级名称
    int mNum;//总排课次数
    int mRemaining;//剩余排课次数
    CourseInfo() {}
};

struct ChartInfo
{
    int row=0;//新排课的行数
    int line=0;//列数
    QDate date;//日期
    QString Week;//周几
    QString WuBie;//午别
    QString JiFang;//机房
    ChartInfo() {}
};

class edrMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    edrMainWindow(QWidget *parent = nullptr);
    ~edrMainWindow();
    void initUI();
    void initModel(QStandardItemModel * new_model);//模型初始化，表头啊那些
    void initSignal();
    void saveModel(QStandardItemModel * tModel, QDataStream &fStream, int total);
    void loadModel(QStandardItemModel * tModel, QDataStream &fStream, int total);
private slots:
    void do_btn_Other_Room_clicked();//连接槽函数，新增的那些机房的操作
    void do_mouseLeftClicked(const QModelIndex index);//左键显示信息
    void do_mouseRightClicked(const QModelIndex index);//右键取消排课
    //void init_buttons(QPushButton * newBtn= nullptr);//本来是打算初始化按钮的一些额外操作的，后来发现没有用上
    void on_btn_Exp_toggled(bool checked);

    void on_btn_310_clicked();

    void on_btn_311_clicked();

    void on_btn_312_clicked();

    void on_btn_417_clicked();

    void on_btn_418_clicked();

    void on_btn_R1_clicked();

    void on_btn_R2_clicked();

    void on_btn_R3_clicked();

    void on_btn_RA_clicked();

    void on_btn_RB_clicked();

    void on_btn_RC_clicked();

    void on_btn_RD_clicked();

    void on_btn_RE_clicked();

    void on_btn_Arr_toggled(bool checked);

    void on_pushButton_arrN_clicked();

    void on_btn_ppl_clicked();

    void on_pushButton_arr_toggled(bool checked);

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_stackedWidget_currentChanged(int arg1);

    void on_bttn_Chart_toggled(bool checked);

    void on_btn_generateChart_clicked();

    void on_pushButton_addroom_clicked();

    void on_btn_Stat_clicked();

    void on_act_save_triggered();

    void on_act_load_triggered();

private:
    Ui::edrMainWindow *ui;
    QModelIndex index = (new QStandardItemModel)->index(0,0,QModelIndex());//测试不同模型同一索引是否相同
    //↑并不能，index专指某个模型的某个位置，并不在不同模型之间通用
    QLabel lb_room;//状态栏标签
    QLabel lb_arr;//排课编号
    QLabel lb_class;//课程名
    QLabel lb_teacher;//教师名
    QLabel lb_ppl;//表示人数
    //以下为可能会改变的数据
    QDate iniDate = QDate(2024,9,2);//2024-2025学年上半年初始日期
    QStandardItemModel mo_310;//自带的教室
    QStandardItemModel mo_311;
    QStandardItemModel mo_312;
    QStandardItemModel mo_417;
    QStandardItemModel mo_418;
    QStandardItemModel mo_R1;
    QStandardItemModel mo_R2;
    QStandardItemModel mo_R3;
    QStandardItemModel mo_RA;
    QStandardItemModel mo_RB;
    QStandardItemModel mo_RC;
    QStandardItemModel mo_RD;
    QStandardItemModel mo_RE;
    QList<CourseInfo> data;//存储排课码对应的排课信息
    QList<QStandardItemModel*> moList;//新增机房list
    QList<QMap<int,ChartInfo>*> ChartList;//用双重指针存储用于报表功能的数据
    QList<QPushButton *> btnList;
    //使用map来自动按照日期排序，key后文有说明
};
#endif // EDRMAINWINDOW_H

