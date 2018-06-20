#ifndef MYSQL_H
#define MYSQL_H

#include"head.h"
class mysql
{
public:
    mysql();
    int verification(QString strU,QString strP);
    bool insert(QString data[]);
    bool deleteId(QString a);
    bool updateDate(QString data[]);
   // void InquireAll(QList<node> *qt);
    //int getFlag();
private:
    int flag;
    QString name[10];
};

#endif // MYSQL_H
