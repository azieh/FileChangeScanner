QT += core
QT -= gui

TARGET = scanner
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11
CONFIG += static

TEMPLATE = app

SOURCES += main.cpp \
    dirscanner.cpp

HEADERS += \
    dirscanner.h

