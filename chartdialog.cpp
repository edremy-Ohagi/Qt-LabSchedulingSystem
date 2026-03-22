#include "chartdialog.h"
#include "ui_chartdialog.h"

chartDialog::chartDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::chartDialog)
{
    ui->setupUi(this);
    initUI();
}

chartDialog::chartDialog(QWidget *parent, int parRow)
    : QDialog(parent)
    , ui(new Ui::chartDialog)
{
    ui->setupUi(this);
    rowC = parRow;//构建时传入parrow确定表格行数
    initUI();//UI初始化，主要是视图合并单元格
    iniModel();//模型初始化，主要用于设置表头等数据
}


chartDialog::~chartDialog()
{
    delete ui;
}

void chartDialog::iniModel()
{
    //qDebug()<<rowC;//先前出过给m_chart设置行数越界问题，后发现是没有对指针进行new初始化
    m_chart->setRowCount(rowC+4);
    m_chart->setColumnCount(5);
    QStandardItem * tItem = new QStandardItem;//表头item
    tItem->setSelectable(false);
    tItem->setEditable(false);
    tItem->setText("机房排课信息表");
    tItem->setTextAlignment(Qt::AlignHCenter);
    m_chart->setItem(0,0,tItem);
    m_chart->setItem(0,1,tItem);
    m_chart->setItem(0,2,tItem);
    m_chart->setItem(0,3,tItem);
    m_chart->setItem(0,4,tItem);
    tItem = new QStandardItem;//其他item
    tItem->setSelectable(false);
    tItem->setEditable(false);
    tItem->setText("课程名称");
    m_chart->setItem(1,0,tItem);
    tItem = new QStandardItem;
    tItem->setSelectable(false);
    tItem->setEditable(false);
    tItem->setText("任课老师");
    m_chart->setItem(1,3,tItem);
    tItem = new QStandardItem;
    tItem->setSelectable(false);
    tItem->setEditable(false);
    tItem->setText("班级");
    m_chart->setItem(2,0,tItem);
    tItem = new QStandardItem;
    tItem->setSelectable(false);
    tItem->setEditable(false);
    tItem->setText("序号");
    m_chart->setItem(3,0,tItem);
    tItem = new QStandardItem;
    tItem->setSelectable(false);
    tItem->setEditable(false);
    tItem->setText("日期");
    m_chart->setItem(3,1,tItem);
    tItem = new QStandardItem;
    tItem->setSelectable(false);
    tItem->setEditable(false);
    tItem->setText("星期");
    m_chart->setItem(3,2,tItem);
    tItem = new QStandardItem;
    tItem->setSelectable(false);
    tItem->setEditable(false);
    tItem->setText("午别");
    m_chart->setItem(3,3,tItem);
    tItem = new QStandardItem;
    tItem->setSelectable(false);
    tItem->setEditable(false);
    tItem->setText("机房");
    m_chart->setItem(3,4,tItem);
    ui->tableView->setModel(m_chart);//这句不能忘！！
}

void chartDialog::initUI()
{
    m_chart = new QStandardItemModel;//这句不能忘！！
    ui->tableView->setSpan(0,0,1,5);//合并单元格
    ui->tableView->setSpan(1,1,1,2);//合并单元格
    ui->tableView->setSpan(2,1,1,4);//合并单元格


}

void chartDialog::resize()//用于将表格列宽自适应内容
{
    ui->tableView->resizeColumnsToContents();
}
