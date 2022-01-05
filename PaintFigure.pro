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
    circle.cpp \
    commands.cpp \
    json_utilities.cpp \
    line.cpp \
    painttable.cpp \
    paintwindow.cpp \
    rectangle.cpp \
    paintscene.cpp \
    figure.cpp \
    triangle.cpp \
    welcomewindow.cpp

HEADERS  += \
    circle.h \
    commands.h \
    json_utilities.h \
    line.h \
    painttable.h \
    paintwindow.h \
    rectangle.h \
    paintscene.h \
    figure.h \
    triangle.h \
    welcomewindow.h

FORMS    += \
    closedialog.ui \
    paintwindow.ui \
    welcomewindow.ui

RESOURCES += \
    resources.qrc

RC_ICONS = icon.ico
