#include "mainwindow.h"
#include "login.h"
#include "client.h"
#include <QtGui\QPainter>
#include <QtCore\QPoint>
#include "mysql.h"
#include <QDesktopServices>
MainWindow::MainWindow(QString a,QWidget *parent)
    : strU(a),QWidget(parent)
{
    resize(610,500);
    setWindowTitle(tr("视频播放系统"));
    SQL=new mysql;
    OnBtnClicked();

    QScrollArea *s = new QScrollArea(this);
    s->setGeometry(0, 0, 610, 500);
    //垂直滚动条不可见，只能通过鼠标滑动
    //s->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //窗体1，其父窗体为滚动区域
    w = new QWidget(s);
    //设置滚动区域的窗体
    s->setWidget(w);
    w->setGeometry(0, 25, 610, 500);
    /*
    QPainter painter;
    int l=0,r=25;
    for(int i=0;i<qt.size();i++){
        if(l==600){
            l=0;
            r+=200;
        }
        painter.drawPixmap(l,r,200,200,QPixmap(qt[i].da[7]));
        l+=200;
    }
    w->paintEvent(painter);*/
    A1=new QAction(tr("增加/删除/修改"),this);
    A1->setShortcuts(QKeySequence::Open);
    A1->setStatusTip(tr("&Add books..."));

    A2=new QAction(tr("查看"),this);
    A2->setShortcuts(QKeySequence::Open);
    A2->setStatusTip(tr("&Drop books..."));
    /*
    A3=new QAction(tr("修改视频信息"),this);
    A3->setShortcuts(QKeySequence::Open);
    A3->setStatusTip(tr("&Modify the book..."));

    A4=new QAction(tr("查询视频"),this);
    A4->setShortcuts(QKeySequence::Open);
    A4->setStatusTip(tr("&Check the book..."));*/
    //myftp =new FtpCLient;
    A1->setShortcuts(QKeySequence::Open);
    A2->setShortcuts(QKeySequence::Open);
    QToolBar *t1 = new  QToolBar;
    t1->addToolBar(tr("Tool Bar 1"));
    QToolBar *t2 = new  QToolBar;
    t2->addToolBar(tr("Tool Bar 2"));
    if(strU=="admin")
        t1->addAction(A1);
    t2->addAction(A2);
    QObject::connect(A1,&QAction::triggered,this,&MainWindow::User_admin);
    QObject::connect(A2,&QAction::triggered,this,&MainWindow::check);
    // QObject::connect(A3,&QAction::triggered,this,&MainWindow::modifyNBook);
    // QObject::connect(A4,&QAction::triggered,this,&MainWindow::checkBook);
    this->setMouseTracking(true);

    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    //this->setWindowModality(Qt::ApplicationModal);
    this->show();
    /*
    playlist = new QMediaPlaylist;
    player = new QMediaPlayer;
    videoWidget = new QVideoWidget;

    setCentralWidget(videoWidget);

    playlist->addMedia(QUrl("http://player.youku.com/embed/XNTE2NTg0NTI4"));
    playlist->setCurrentIndex(1);
    player->setPlaylist(playlist);
    player->setVideoOutput(videoWidget);

    videoWidget->show();
    player->play();
*/
}
void MainWindow::paintEvent(QPaintEvent *)
{
    /* QUrl url("http://img0.bdstatic.com/img/image/shouye/dengni63.jpg");
    QNetworkAccessManager manager;
    QEventLoop loop;

    QNetworkReply *reply = manager.get(QNetworkRequest(url));

    loop.exec();
    QByteArray jpegData = reply->readAll();
    QPixmap pixmap;
    pixmap.loadFromData(jpegData);*/
    QPainter painter(this);
    int a=0,b=25;
    for(int i=0;i<qt.size();i++){
        if(a==600){
            a=0;
            b+=200;
        }
        painter.drawPixmap(a,b,200,200,QPixmap(qt[i].da[7]));
        a+=200;
    }
}
MainWindow::~MainWindow()
{

}

void MainWindow::mousePressEvent(QMouseEvent *e)//鼠标单击事件响应
{
    QString str="("+QString::number(e->x())+","+QString::number(e->y())+")";
    //qDebug()<<str;
    int fl=((int)(e->x()))/200+(((int)(e->y()))/200)*3;
    QDesktopServices::openUrl(QUrl(qt[fl].da[6]));
    /*
    if(e->button()==Qt::LeftButton)
        statusBar()->showMessage (tr("Mouse Left Button Pressed:")+str);//显示临时信息
    else if(e->button()==Qt::RightButton)
        statusBar()->showMessage (tr("Mouse Right Button Pressed:")+str);
    else if(e->button()==Qt::MidButton)
        statusBar()->showMessage (tr("Mouse Middle Button Pressed:")+str);
        */
}

int MainWindow::getRant(){
    return rant;
}

void MainWindow::User_admin(){
    table=new QTableWidget(7,9);
    QStringList colLabs;
    colLabs<<"  "<<"ID"<<"名称"<<"类别"<<"出处"<<"添加时间"<<"作者"<<"视频链接"<<"图片位置";
    table->setHorizontalHeaderLabels(colLabs);
    table->resize(940, 230);
    table->setWindowTitle("增加/删除/修改");
    table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    //设置每一行的高度
    table->setRowHeight(0,20);
    //自动调整最后一列的宽度使它和表格的右边界对齐
    table->horizontalHeader()->setStretchLastSection(true);
    //设置表格的选择方式
    table->setSelectionBehavior(QAbstractItemView::SelectItems);
    //设置编辑方式
    table->setEditTriggers(QAbstractItemView::DoubleClicked);
    table->setSpan(6, 0, 6, 9);

    QHeaderView *headerView = table->verticalHeader();
    headerView->setHidden(true);
    table->resizeColumnsToContents();
    table->resizeRowsToContents();

    QPushButton *pBtn1 = new  QPushButton("确定增加");
    QTableWidgetItem *item0 = new QTableWidgetItem;
    item0->setText("增加视频-->");
    table->setItem(0,0,item0);
    table->setCellWidget(1,0,pBtn1);
    connect(pBtn1,SIGNAL(clicked(bool)),this,SLOT(Add()));
    QPushButton *pBtn2 = new  QPushButton("确定删除");
    QTableWidgetItem *item1 = new QTableWidgetItem;
    item1->setText("删除视频-->");
    QTableWidgetItem *item4 = new QTableWidgetItem;
    item4->setText("<--输入ID");
    table->setItem(2,0,item1);
    table->setItem(2,2,item4);
    table->setCellWidget(3,0,pBtn2);
    connect(pBtn2,SIGNAL(clicked(bool)),this,SLOT(Delete()));

    QPushButton *pBtn3 = new  QPushButton("确定修改");
    QTableWidgetItem *item2 = new QTableWidgetItem;
    item2->setText("修改视频-->");
    table->setItem(4,0,item2);
    table->setCellWidget(5,0,pBtn3);

    connect(pBtn3,SIGNAL(clicked(bool)),this,SLOT(Modiify()));
    QTableWidgetItem *item5 = new QTableWidgetItem;
    item5->setText("双击单元框克编辑，增加/修改/删除，必须填Bbo主键-->");
    table->setItem(6,0,item5);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
    table->horizontalHeader()->setSectionResizeMode(5, QHeaderView::ResizeToContents);
    table->show();
}
void MainWindow::check(){
    OnBtnClicked();
    int len=strU=="admin"?8:6;
    table = new QTableWidget(qt.size(),len);
    QStringList colLabs;
    colLabs<<"ID"<<"名称"<<"类别"<<"出处"<<"添加时间"<<"作者"<<"视频链接"<<"图片位置";
    table->setHorizontalHeaderLabels(colLabs);
    if(strU=="admin")
        table->resize(940, 230);
    else
        table->resize(640, 200);
    table->setWindowTitle("查看所有视频信息");
    table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    //设置编辑方式
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置每一行的高度
    table->setRowHeight(0,20);
    //自动调整最后一列的宽度使它和表格的右边界对齐
    table->horizontalHeader()->setStretchLastSection(true);
    //设置表格的选择方式
    table->setSelectionBehavior(QAbstractItemView::SelectItems);

    for(int i=0;i<qt.size();i++){
        QString q0 =QString::number( qt[i].Bno, 10);
        QTableWidgetItem *item0 = new QTableWidgetItem;
        item0->setText(q0);
        table->setItem(i,0,item0);
        table->setRowHeight(i,20);
        for(int j=1;j<len;j++){
            QTableWidgetItem *item1 = new QTableWidgetItem;
            item1->setText(qt[i].da[j]);
            table->setItem(i,j,item1);
        }
    }
    QHeaderView *headerView = table->verticalHeader();
    headerView->setHidden(true);
    table->resizeColumnsToContents();
    table->resizeRowsToContents();
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->show();
}
void MainWindow::OnBtnClicked()
{
    QSqlDatabase db;
    QSqlDatabase::drivers();
    db =QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("118.89.51.72");
    db.setDatabaseName("mybook");
    db.setUserName("pig");
    db.setPassword("123456");
    if(db.open()){
        QString u="select * from video";
        QSqlQuery query(db);
        qt.clear();
        if(query.exec(u)){
            while(query.next()){
                node ta;
                bool ok;
                ta.Bno=(query.value(0).toString()).toInt(&ok,10);
                for(int i=1;i<=7;i++)
                    ta.da[i]=query.value(i).toString();
                qt<<ta;
            }
        }
        db.close();
    }
    return;
}
void MainWindow::Add(){
    QString tabeDate[10];
    for(int j=1; j<=8; j++){
        if(table->item(0, j)!=NULL)
            tabeDate[j-1] = table->item(0, j)->text();
    }
    if(tabeDate[0].size()!=0){
        if(SQL->insert(tabeDate)){
            table->hide();
            OnBtnClicked();
        }
    }
}
void MainWindow::Delete(){
    QString Date;
    if(table->item(2, 1)!=NULL)
        Date=table->item(2, 1)->text();
    qDebug()<<Date;
    if(Date.size()!=0){
        if(SQL->deleteId(Date)){
            table->hide();
            OnBtnClicked();
        }
    }
}
void MainWindow::Modiify(){
    QString tabeDate[10];
    for(int j=1; j<=8; j++){
        if(table->item(4, j)!=NULL)
            tabeDate[j-1] = table->item(4, j)->text();
        else
            tabeDate[j-1] ="";
    }
    if(tabeDate[0].size()!=0){
        if(SQL->updateDate(tabeDate)){
            table->hide();
            OnBtnClicked();
        }
    }
}

