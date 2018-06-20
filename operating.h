#ifndef OPERATING_H
#define OPERATING_H
#include "head.h"
class mainwindow;
class operating:public QWidget
{
public:
    operating(QString a,QWidget *parent = 0);
private:
    QString strU;
};

#endif // OPERATING_H
