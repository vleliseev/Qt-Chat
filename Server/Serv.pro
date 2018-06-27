#-------------------------------------------------
#
# Project created by QtCreator 2018-06-22T14:24:05
#
#-------------------------------------------------

QT       -= gui
QT       += network


CONFIG += c++11 console
CONFIG -= app_bundle

TARGET = Serv
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    connectionhandler.cpp \
    datahandler.cpp \
    ../Data/authanswer.cpp \
    ../Data/authdata.cpp \
    ../Data/basedata.cpp \
    ../Data/userlist.cpp

HEADERS += \
    connectionhandler.h \
    datahandler.h \
    ../Data/authanswer.h \
    ../Data/authdata.h \
    ../Data/basedata.h \
    ../Data/userlist.h

