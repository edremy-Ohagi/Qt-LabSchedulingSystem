#ifndef ROOMDIALOG_H
#define ROOMDIALOG_H

#include <QDialog>

namespace Ui {
class roomDialog;
}

class roomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit roomDialog(QWidget *parent = nullptr);
    ~roomDialog();
    //以下三个函数用于获得对话框内输入框的内容
    int AreaChoice();
    QString getName();
    int getppl();//在ui设计中限制了最大值120，最小值30
private:
    Ui::roomDialog *ui;
};

#endif // ROOMDIALOG_H
