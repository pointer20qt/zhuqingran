#ifndef PERSON_H
#define PERSON_H

#include <QWidget>

namespace Ui {
class Person;
}

class Person : public QWidget
{
    Q_OBJECT

public:
    explicit Person(QWidget *parent = 0);
    ~Person();
    void init(QString sno,QString sname,QString Class);

private:
    Ui::Person *ui;
};

#endif // PERSON_H
