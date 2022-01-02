#-------------------------------------------------
#
# Project created by QtCreator 2015-12-03T20:24:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PaintFigure
TEMPLATE = app


SOURCES += main.cpp\
    commands.cpp \
    json_utilities.cpp \
    line.cpp \
    mainwindow.cpp \
    paintwindow.cpp \
    romb.cpp \
    paintscene.cpp \
    figure.cpp \
    triangle.cpp \
    square.cpp \
    welcomewindow.cpp

HEADERS  += mainwindow.h \
    commands.h \
    json_utilities.h \
    line.h \
    paintwindow.h \
    romb.h \
    paintscene.h \
    figure.h \
    triangle.h \
    square.h \
    welcomewindow.h

FORMS    += mainwindow.ui \
    paintwindow.ui \
    welcomewindow.ui

RESOURCES += \
    resources.qrc
