#-------------------------------------------------
#
# Project created by QtCreator 2018-07-15T07:29:50
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = LosslessJpegCrop
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += $$PWD/include
LIBS+=$$PWD/lib/libturbojpeg.a

SOURCES += main.cpp \
    losslessjpegcrop.cpp

HEADERS += \
    losslessjpegcrop.h
