#ifndef STATDIALOG_H
#define STATDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
namespace Ui {
class statDialog;
}

class statDialog : public QDialog//这部分与chartdialog基本一致
{
    Q_OBJECT

public:
    explicit statDialog(QWidget *parent = nullptr);
    statDialog(QWidget *parent = nullptr,int parRow =0);
    ~statDialog();
    void iniModel();
    void initUI();
    QStandardItemModel * m_chart;
    void resize();
private:
    Ui::statDialog *ui;
    int rowC;
};

#endif // STATDIALOG_H
