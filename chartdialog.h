#ifndef CHARTDIALOG_H
#define CHARTDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
namespace Ui {
class chartDialog;
}

class chartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit chartDialog(QWidget *parent = nullptr);
    chartDialog(QWidget *parent = nullptr,int parRow =0);
    ~chartDialog();
    void iniModel();
    void initUI();
    QStandardItemModel * m_chart;
    void resize();
private:
    Ui::chartDialog *ui;
    int rowC;
};

#endif // CHARTDIALOG_H
