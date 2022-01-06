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
    about.cpp \
    circle.cpp \
    commands.cpp \
    json_utilities.cpp \
    line.cpp \
    messagedialog.cpp \
    painttable.cpp \
    paintwindow.cpp \
    rectangle.cpp \
    paintscene.cpp \
    figure.cpp \
    triangle.cpp \
    welcomewindow.cpp

HEADERS  += \
    about.h \
    circle.h \
    commands.h \
    json_utilities.h \
    line.h \
    messagedialog.h \
    painttable.h \
    paintwindow.h \
    rectangle.h \
    paintscene.h \
    figure.h \
    triangle.h \
    welcomewindow.h

FORMS    += \
    about.ui \
    messagedialog.ui \
    paintwindow.ui \
    welcomewindow.ui

RESOURCES += \
    resources.qrc

RC_ICONS = icon.ico
