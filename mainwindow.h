#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "head.h"

class login;
class FtpCLient;
class mysql;
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QString a,QWidget *parent = 0);
    void paintEvent(QPaintEvent *event = 0);
    void User_ordinary();
    int getRant();
    ~MainWindow();
private:
    typedef struct node{
        int Bno;
        QString da[10];
    }node;

    QString strU;
    QList<node> qt;
    int rant;
    mysql *SQL;
    login *Login;

    QWidget *w;

    QNetworkAccessManager *manager;
    FtpCLient *myftp;
    QAction *A1,*A2;
    QTimer theTimer;
    QLabel *imageLabel;
    QPainter *painter;
    QMediaPlaylist *playlist;
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QTableWidget *table;
    QLabel *labelStatus;
    QLabel *labelMousePos;
public slots:
    void User_admin();
    void check();
    void OnBtnClicked();
    void Add();
    void Delete();
    void Modiify();
protected :
    void mousePressEvent(QMouseEvent *e);
};

#endif // MAINWINDOW_H
