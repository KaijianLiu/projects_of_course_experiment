#include"def.h"

#include "mainwindow.h"
#include<QApplication>
#include<QMessageBox>
#include<QDebug>
#include<QStringList>
#include<QSqlDatabase>
#include<QSqlQuery>

bool initDatabase(void);

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
   // if(!initDatabase()){
   //     return -1;
   // }

    MainWindow w;
   //   mainqq();
    socket_test();
  //  w.show();

    return a.exec();
}


bool initDatabase(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //设置数据库名称
    db.setDatabaseName("./smarthome.sqlite.db");
    if(!db.open())
    {
        QMessageBox::critical(0, "Cannot open database", "Unable to establisha database connection."
                      , QMessageBox::Cancel);
        return false;
    }
    bool res = true;
    QSqlQuery query;
    //创建湿度表
    res &= query.exec("create table IF NOT EXISTS humidity (id INTEGER PRIMARY KEY AUTOINCREMENT, datestamp DATETIME, data DECIMAL(6,3) )");
    //temperature
    res &= query.exec("create table IF NOT EXISTS temperature (id INTEGER PRIMARY KEY AUTOINCREMENT, datestamp DATETIME, data DECIMAL(6,3)  )");
    //bathroom
    res &= query.exec("create table IF NOT EXISTS bathroom (id INTEGER PRIMARY KEY AUTOINCREMENT, datestamp DATETIME, operation CHARACTER(5)  )");
    //gate
    res &= query.exec("create table IF NOT EXISTS gate (id INTEGER PRIMARY KEY AUTOINCREMENT, datestamp DATETIME, cardid INT  )");
    if(!res){
        QMessageBox::critical(0, "Error init data tables", "failed to to create tables."
                      , QMessageBox::Cancel);
        return false;
    }
    testDB();
    return true;
}
