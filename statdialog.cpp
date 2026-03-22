#include "statdialog.h"
#include "ui_statdialog.h"

statDialog::statDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::statDialog)
{
    ui->setupUi(this);
}

statDialog::statDialog(QWidget *parent, int parRow)
    : QDialog(parent)
    , ui(new Ui::statDialog)
{
    ui->setupUi(this);
    rowC = parRow;
    initUI();
    iniModel();
}

statDialog::~statDialog()
{
    delete ui;
}

void statDialog::iniModel()
{
    m_chart->setRowCount(rowC+2);
    m_chart->setColumnCount(5);
    QStandardItem * tItem = new QStandardItem;
    tItem->setSelectable(false);
    tItem->setEditable(false);
    tItem->setTextAlignment(Qt::AlignHCenter);
    tItem->setText("2024-2025学年上半年机房使用情况统计表");
    m_chart->setItem(0,0,tItem);
    m_chart->setItem(0,1,tItem);
    m_chart->setItem(0,2,tItem);
    m_chart->setItem(0,3,tItem);
    m_chart->setItem(0,4,tItem);
    tItem = new QStandardItem;
    tItem->setSelectable(false);
    tItem->setEditable(false);
    tItem->setText("学院");
    m_chart->setItem(1,0,tItem);
    tItem = new QStandardItem;
    tItem->setSelectable(false);
    tItem->setEditable(false);
    tItem->setText("教师");
    m_chart->setItem(1,1,tItem);
    tItem = new QStandardItem;
    tItem->setSelectable(false);
    tItem->setEditable(false);
    tItem->setText("班级");
    m_chart->setItem(1,2,tItem);
    tItem = new QStandardItem;
    tItem->setSelectable(false);
    tItem->setEditable(false);
    tItem->setText("课程名");
    m_chart->setItem(1,3,tItem);
    tItem = new QStandardItem;
    tItem->setSelectable(false);
    tItem->setEditable(false);
    tItem->setText("使用次数");
    m_chart->setItem(1,4,tItem);
    ui->tableView->setModel(m_chart);
}

void statDialog::initUI()
{
    m_chart = new QStandardItemModel;//这句不能忘！！
    ui->tableView->setSpan(0,0,1,5);//合并单元格
}

void statDialog::resize()
{
    ui->tableView->resizeColumnsToContents();
}
