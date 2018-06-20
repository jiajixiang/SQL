#-------------------------------------------------
#
# Project created by QtCreator 2017-12-24T13:45:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sql
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



QT       += core gui
TEMPLATE = app

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    login.cpp \
    mysql.cpp \
    information.cpp \
    operating.cpp \
    client.cpp

HEADERS += \
        mainwindow.h \
    login.h \
    mysql.h \
    head.h \
    information.h \
    operating.h \
    client.h

RESOURCES += \
    tu.qrc

QT       += network

QT += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32:QMAKE_CXXFLAGS += -std=c++11
QT += widgets
CONFIG += shared

QT += sql

QT += multimediawidgets
QT += multimedia
