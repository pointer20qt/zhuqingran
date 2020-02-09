#-------------------------------------------------
#
# Project created by QtCreator 2020-02-06T17:14:00
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtSignSystem
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    person.cpp \
    login.cpp \
    register.cpp

HEADERS  += widget.h \
    person.h \
    login.h \
    register.h

FORMS    += widget.ui \
    person.ui \
    login.ui \
    register.ui

RESOURCES += \
    ../beijingtu/beijing.qrc
