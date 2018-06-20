#include "login.h"
#include "mysql.h"
#include "mainwindow.h"
#include "operating.h"
login::login(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(300,180);
    this->setWindowTitle("登陆");
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉窗口标题栏方式1
    pUserName=new QLabel("账号",this);
    pUserName->setGeometry(140,50,30,30);
    pLogin=new QLabel("密码",this);
    pLogin->setGeometry(140,77,30,30);
    pNameEdit = new QLineEdit(this);
    pNameEdit->setGeometry(165,55,100,20);
    pNameEdit->setMaxLength(12);
    pLoginEdit = new QLineEdit(this);
    pLoginEdit->setGeometry(165,82,100,20);

    pLoginEdit->setEchoMode(QLineEdit::Password);
    //登陆按钮
    pB = new QPushButton("登陆/注册",this);
    pB->setGeometry(140,120,75,20);
    pD = new QPushButton("退出",this);
    pD->setGeometry(225,120,60,20);

    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    connect(pB,SIGNAL(clicked(bool)),this,SLOT(Login()));
    connect(pD,SIGNAL(clicked(bool)),this,SLOT(end()));
    this->setWindowModality(Qt::ApplicationModal);
    this->show();
}

login::~login()
{
    delete this;
}
void login::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/17.jpg");
    painter.drawPixmap(0,25,582/4,558/4,pix);
}
QString login::Login()
{
    //获取文本框中的信息
    strU="";
    strU = pNameEdit->text();
    strP = pLoginEdit->text();
    my=new mysql;
    //qDebug()<< "Login Login";
    if(strU==NULL||strP==NULL)
        QMessageBox::warning(NULL, "warning", "用户名/密码不能为空");
    else{
        flag=my->verification(strU,strP);
        qDebug()<<flag<<" login";
        if(flag==3)
            QMessageBox::warning(NULL, "sucessful", "注册成功,请登陆");
        else
            if(flag==0)
                QMessageBox::warning(NULL, "warning", "登陆失败，请重新输入");
            else
                if(flag==1||flag==2){
                    QMessageBox::warning(NULL, "warning", "登陆成功");
                    this->hide();
                    Main=new operating(strU);
                }
        pNameEdit->clear();
        pLoginEdit->clear();
    }
    qDebug()<<flag<<" login";
    return strU;
}
void login::end(){
    this->close();
}
int login::getFlag(){
    qDebug()<<"getFlag";
    qDebug()<<flag;
    return flag;
}
QString login::getStrU(){
    return strU;
}
QString login::getStrP(){
    return strP;
}
