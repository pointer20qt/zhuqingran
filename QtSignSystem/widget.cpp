#include "widget.h"
#include "ui_widget.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QCheckBox>
#include <QString>
#include <QDateTime>
#include<QVariant>
#include<QMessageBox>
#include<QPushButton>
#include<QComboBox>
#include"person.h"
#include"login.h"
Widget::Widget(QWidget *parent,QString sno) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->sno=sno;
    dataToTable("select * from stu");
    displayClass();
    displaySno();
    connect(ui->tableWidget,QTableWidget::cellDoubleClicked,[=](int r,int c)
    {
        Person *p=new Person();
        p->setWindowTitle("个人界面");
        p->init(ui->tableWidget->item(r,0)->text(),ui->tableWidget->item(r,1)->text(),ui->tableWidget->item(r,2)->text());
        p->show();
    });
}
//将数据显示到表格
void Widget::dataToTable(QString sql)
{
    QSqlQuery q;
    q.exec(QString("select Sno from stu where Sno='%1'").arg(this->sno));
    q.next();
    QString curSno=q.value(0).toString();
    if(q.exec(sql)) //exec 执行
    {
        ui->tableWidget->setRowCount(q.size());//设置行
        int i=0;
        while(q.next())
        {
            QCheckBox *c=new QCheckBox("未签到");
            QString sno1=q.value(0).toString();
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(sno1));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(q.value(1).toString()));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(q.value(2).toString()));
            ui->tableWidget->setCellWidget(i,3,c);
            QSqlQuery q3;
            q3.exec(QString("select Qtime from qiandao where Qno='%1' and date(Qtime)=curdate()order by Qtime desc ").arg(sno1));
            q3.next();
            if(sno1!=curSno)
            {
                c->setDisabled(true);
            }
            if(q3.size())
            {
                c->setChecked(true);
                c->setDisabled(true);
                c->setText("已签到");
            }
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(q3.value(0).toString()));
            connect(c,QCheckBox::clicked,[=]()
            {
                //1.修改控件本身的状态
                c->setText("已签到");
                c->setDisabled(true);
                //2.向表格中添加本人签到时间
                ui->tableWidget->setItem(i,4,new QTableWidgetItem(QDateTime::currentDateTime().toString()));
                //3.向数据库中插入一条数据
                QSqlQuery q1;
                qDebug()<<q1.exec(QString("insert into qiandao values(%1,now())").arg(sno1));
            });
            i++;
        }
    }
}
Widget::~Widget()
{
    delete ui;
}
//按班级查看学生信息
void Widget::displayClass()
{
    QSqlQuery q4;
    q4.exec("select distinct Class from stu");
    ui->comboBox->addItem("全部班级");
    while(q4.next())
    {
        ui->comboBox->addItem(q4.value(0).toString());
    }
    connect(ui->comboBox,QComboBox::currentTextChanged,[=](QString str)
    {
        if(str=="全部班级")
        {
            dataToTable("select *from stu");
        }
        else
        {
            dataToTable(QString("select *from stu where Class='%1'").arg(str));
        }
    });
}
//按学号查看学生信息
void Widget::displaySno()
{
    connect(ui->pushButton,QPushButton::clicked,[=]()
    {
        if(ui->lineEdit->text().isEmpty())
        {
            QMessageBox::warning(this,"warn","您输入为空");
        }
        else
        {
            dataToTable(QString("select *from stu where Sno like %1").arg(ui->lineEdit->text()));
        }
    });
}

