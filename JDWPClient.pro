#-------------------------------------------------
#
# Project created by QtCreator 2014-10-26T10:38:17
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = JDWPClient
CONFIG   += console c++11
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    JDWPProtocol.cpp \
    JDWPCommand.cpp \
    JDWPReply.cpp \
    JDWPClient.cpp

HEADERS += \
    JDWPProtocol.h \
    JDWPCommand.h \
    JDWPReply.h \
    JDWPClient.h
