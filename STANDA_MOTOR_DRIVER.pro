#-------------------------------------------------
#
# Project created by QtCreator 2014-12-10T17:18:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport

TARGET = STANDA_MOTOR_DRIVER
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
    port.cpp \
    protocol_8smc4.cpp

HEADERS  += mainwindow.h\
    port.h \
    protocol_8smc4.h

FORMS    += mainwindow.ui
