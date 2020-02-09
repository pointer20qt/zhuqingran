#include "register.h"
#include "ui_register.h"
#include<QSqlQuery>
#include<QDebug>
#include<QString>
#include<QMessageBox>
Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}
Register::~Register()
{
    delete ui;
}
void Register::on_pushButton_clicked()
{
    QString sno=ui->lineEdit->text();
    QString password=ui->lineEdit_2->text();
    QString sname=ui->lineEdit_3->text();
    QString Class=ui->lineEdit_4->text();
    QSqlQuery q;
    q.exec(QString("select * from login where login_name='%1' ").arg(sno));
    if(q.size()>0)
    {
        QMessageBox::warning(this,"warn","登录账号已存在！");
    }
    else if(sno==NULL)
    {
        QMessageBox::warning(this,"warn","登录账号为空！");
    }
    else if(password==NULL)
    {
        QMessageBox::warning(this,"warn","密码为空！");
    }
    else if(sname==NULL)
    {
        QMessageBox::warning(this,"warn","姓名为空！");
    }
    else if(Class==NULL)
    {
        QMessageBox::warning(this,"warn","班级为空！");
    }
    else
    {
        QSqlQuery q1;
        qDebug()<<q1.exec(QString("insert into login values('%1','%2')").arg(sno).arg(password));
        QSqlQuery q2;
        qDebug()<<q2.exec(QString("insert into stu values('%1','%2','%3')").arg(sno).arg(sname).arg(Class));
        QMessageBox::warning(this,"warn","注册成功！");
    }
}
void Register::on_pushButton_2_clicked()
{
    this->close();
}
