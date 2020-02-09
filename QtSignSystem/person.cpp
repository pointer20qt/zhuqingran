#include "person.h"
#include "ui_person.h"
#include<QSqlQuery>
#include<QTextCharFormat>
#include<QDebug>
Person::Person(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Person)
{
    ui->setupUi(this);
}
void Person::init(QString sno,QString sname,QString Class)
{
    ui->label->setText("学号:"+sno);
    ui->label_2->setText("姓名:"+sname);
    ui->label_3->setText("班级:"+Class);
    QSqlQuery q;
    qDebug()<<q.exec(QString("select Qtime from qiandao where Qno=%1 and date_format(Qtime,'%Y-%m')=date_format(curdate(),'%Y-%m')").arg(sno));
    ui->label_4->setText("签到次数:"+QString::number(q.size()));
    QTextCharFormat f;
    f.setBackground(Qt::green);
    while(q.next())
    {
         ui->calendarWidget->setDateTextFormat(q.value(0).toDate(),f);
    }
    ui->label_5->setText("出勤率:");
}
Person::~Person()
{
    delete ui;
}
