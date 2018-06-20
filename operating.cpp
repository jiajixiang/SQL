#include "operating.h"
#include "mainwindow.h"
operating::operating(QString a,QWidget *parent)
    : strU(a),QMainWindow(parent)
{
    QScrollArea *s = new QScrollArea(this);
    s->setGeometry(0, 0, 200, 200);
    //垂直滚动条不可见，只能通过鼠标滑动
    s->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //窗体1，其父窗体为滚动区域
    QWidget *w = new MainWindow(strU,s);
    //设置滚动区域的窗体
    s->setWidget(w);
    w->setGeometry(0, 0, 300, 300);
}
