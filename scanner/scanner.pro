QT += core
QT -= gui

TARGET = scanner
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    dirscanner.cpp

HEADERS += \
    dirscanner.h

