#-------------------------------------------------
#
# Project created by QtCreator 2016-08-27T13:42:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ABG
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    board.cpp \
    cube.cpp \
    fish.cpp \
    SelectingPlayers.cpp \
    triangle.cpp \
    variantmoves.cpp \
    variantmovestri.cpp \
    selectplayers.cpp \
    endgame.cpp \
    about.cpp

HEADERS  += mainwidget.h \
    board.h \
    cube.h \
    fish.h \
    SelectingPlayers.h \
    globalvar.h \
    triangle.h \
    variantmoves.h \
    variantmovestri.h \
    selectplayers.h \
    endgame.h \
    about.h

RESOURCES += \
    resource.qrc

#windows:TARGET	= ../ABG

DISTFILES += \
    pictures/black_30_32_1.png \
    pictures/white_30_32_1.png
