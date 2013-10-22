#-------------------------------------------------
#
# Project created by QtCreator 2013-10-14T16:48:36
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    invoker.cpp \
    command.cpp

HEADERS  += widget.h \
    invoker.h \
    command.h

FORMS    += widget.ui
