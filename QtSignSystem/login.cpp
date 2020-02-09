#include "login.h"
#include "ui_login.h"
#include<QMessageBox>
#include<QSqlQuery>
#include"widget.h"
#include<QDebug>
#include"register.h"
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("student");
    db.setUserName("root");
    db.setPassword("123456");
    if(db.open())
    {
        qDebug()<<"打开数据库成功";
    }
    else
    {
        qDebug()<<"打开数据库失败";
    }
}
Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
   QString sno=ui->lineEdit->text();
   QString password=ui->lineEdit_2->text();
   QSqlQuery q;
   q.exec(QString("select * from login where login_name='%1' ").arg(sno));
   if(q.size()>0)
   {
       q.exec(QString("select * from login where login_name='%1' and login_password='%2' ").arg(sno).arg(password));
       if(q.size()>0)
       {
           Widget *w=new Widget(NULL,sno);
           w->setWindowTitle("签到主界面");
           w->show();
           this->close();
       }
       else
       {
           QMessageBox::warning(this,"warn","密码错误！");
       }
   }
   else
   {
       QMessageBox::warning(this,"warn","登录账号不存在！");
   }
}
void Login::on_pushButton_2_clicked()
{
    Register *r=new Register();
    r->setWindowTitle("注册界面");
    r->show();
}
