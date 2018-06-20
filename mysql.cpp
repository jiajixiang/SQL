#include "mysql.h"
#include "information.h"
information get;
mysql::mysql()
{
    flag=-1;
    name[0]="Bno";
    name[1]="Title";
    name[2]="Category";
    name[3]="Press";
    name[4]="Added_Time";
    name[5]="Author";
    name[6]="Url";
    name[7]="tu";
}
int mysql::verification(QString strU,QString strP){
    flag=0;
    QSqlDatabase::drivers();
    /* if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else*/
    QSqlDatabase db;
    db =QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("118.89.51.72");
    db.setDatabaseName("mybook");
    db.setUserName("pig");
    db.setPassword("123456");
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString time=current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
    QString name=get.getName();
    name.trimmed();
    QString ip=get.getIP();
    QString mac=get.getMac();
    if(db.open()){
        QString in="select id,password from User where id='";
        in.insert(in.size(),strU);
        in.insert(in.size(),"';");
        //qDebug()<<in;
        QSqlQuery query(db);
        int i=0;
        if(query.exec(in)){
            int len=query.size();
            if(len==0){
                QString two="insert into User values('";
                two.insert(two.size(),strU);
                two.insert(two.size(),"','");
                two.insert(two.size(),strP);
                two.insert(two.size(),"','");
                two.insert(two.size(),ip);
                two.insert(two.size(),"','");
                two.insert(two.size(),mac);
                two.insert(two.size(),"');");
                if(query.exec(two)){
                    flag=3;
                    // qDebug()<< "Mysql insert";
                }
            }
            else{
                while(query.next()){
                    i++;
                    QString qs = query.value(1).toString();
                    if(qs==strP){
                        if(strU=="admin")
                            flag=1;
                        else
                            flag=2;
                        break;
                    }
                }
            }
        }
        db.close();
    }
    //qDebug()<< flag;
    return flag;
}
bool mysql::insert(QString data[]){
    QSqlDatabase::drivers();
    /* if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else*/
    QSqlDatabase db;
    db =QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("118.89.51.72");
    db.setDatabaseName("mybook");
    db.setUserName("pig");
    db.setPassword("123456");
    QString in="insert into video values(";
    in.insert(in.size(),data[0]);
    in.insert(in.size(),",'");
    in.insert(in.size(),data[1]);
    in.insert(in.size(),"','");
    in.insert(in.size(),data[2]);
    in.insert(in.size(),"','");
    in.insert(in.size(),data[3]);
    in.insert(in.size(),"','");
    in.insert(in.size(),data[4]);
    in.insert(in.size(),"','");
    in.insert(in.size(),data[5]);
    in.insert(in.size(),"','");
    in.insert(in.size(),data[6]);
    in.insert(in.size(),"','");
    in.insert(in.size(),data[7]);
    in.insert(in.size(),"');");
    if(db.open()){
        QSqlQuery query(db);
        if(query.exec(in))
            QMessageBox::warning(NULL, "warning", "添加成功");
        db.close();
        return true;
    }
    else
        QMessageBox::warning(NULL, "warning", "添加失败");
    return false;
}

bool mysql::deleteId(QString a){
    QSqlDatabase::drivers();
    /* if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else*/
    QSqlDatabase db;
    db =QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("118.89.51.72");
    db.setDatabaseName("mybook");
    db.setUserName("pig");
    db.setPassword("123456");
    QString in="delete from video where Bno=";
    in.insert(in.size(),a);
    in.insert(in.size(),";");
    if(db.open()){
        QSqlQuery query(db);
        if(query.exec(in))
            QMessageBox::warning(NULL, "warning", "删除成功");
        else
            QMessageBox::warning(NULL, "warning", "删除失败");
        db.close();
        return true;
    }
    else
        QMessageBox::warning(NULL, "warning", "删除失败");
    return false;
}
bool mysql::updateDate(QString data[]){
    QSqlDatabase::drivers();
    /* if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else*/
    QSqlDatabase db;
    db =QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("118.89.51.72");
    db.setDatabaseName("mybook");
    db.setUserName("pig");
    db.setPassword("123456");
    if(db.open()){
        QSqlQuery query(db);
        for(int i=1;i<8;i++){
            if(data[i].size()>0){
                QString in="update video set ";
                in.insert(in.size(),name[i]);
                in.insert(in.size(),"='");
                in.insert(in.size(),data[i]);
                in.insert(in.size(),"' where Bno=");
                in.insert(in.size(),data[0]);
                in.insert(in.size(),";");
                query.exec(in);
            }
        }
        QMessageBox::warning(NULL, "warning", "更新成功");
        db.close();
        return true;
    }
    else
        QMessageBox::warning(NULL, "warning", "更新失败");
    return false;
}
