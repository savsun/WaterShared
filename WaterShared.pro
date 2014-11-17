#-------------------------------------------------
#
# Project created by QtCreator 2014-11-17T09:18:25
#
#-------------------------------------------------

QT       += core testlib

QT       -= gui

TARGET = WaterShared
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    countthreshold.cpp

HEADERS += \
    countthreshold.h \
    all.h
LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui
