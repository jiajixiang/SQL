#ifndef LOGIN_H
#define LOGIN_H

#include "head.h"

class mysql;
class MainWindow;
class operating;
class login : public QMainWindow
{
    Q_OBJECT

public:
    login(QWidget *parent = 0);
    ~login();
    void paintEvent(QPaintEvent *);
    int getFlag();
    QString getStrU();
    QString getStrP();
private:
    QPushButton *pB;
    QPushButton *pD;
    QLabel *pUserName;
    QLabel *pLogin;
    operating *Main;
    QLineEdit *pNameEdit;
    QLineEdit *pLoginEdit;
    QString strU;
    QString strP;
    mysql *my;
    int flag;
    //创建槽
public slots:
    QString Login();
    void end();
};


#endif // LOGIN_H
