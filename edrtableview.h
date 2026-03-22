#ifndef EDRTABLEVIEW_H
#define EDRTABLEVIEW_H

#include <QTableView>
#include <QMouseEvent>
#include <QModelIndex>
class edrTableView : public QTableView
{
    Q_OBJECT

public:
    edrTableView(QWidget *parent = nullptr);
protected:
    //重构鼠标按下事件，主要是区别左右键按下
    void mousePressEvent(QMouseEvent * event);
signals:
    //对应的信号，左键右键，传入index
    void mouseLeftClicked(const QModelIndex index);
    void mouseRightClicked(const QModelIndex index);
};

#endif // EDRTABLEVIEW_H
