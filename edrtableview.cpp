#include "edrtableview.h"

edrTableView::edrTableView(QWidget *parent):QTableView(parent) {}

void edrTableView::mousePressEvent(QMouseEvent *event)
{
    {
        if(event->button()==Qt::LeftButton){
            const QModelIndex index = indexAt(event->pos());
            emit  mouseLeftClicked(index);//刚写完这部分的时候报错不能reference 后来发现是少写了Qobject，还得删makefile重置一下
        }
        if(event->button()==Qt::RightButton){
            const QModelIndex index = indexAt(event->pos());
            emit  mouseRightClicked(index);
        }
        QTableView::mousePressEvent(event);//事件传递给基类
    }
}


