#-------------------------------------------------
#
# Project created by QtCreator 2016-03-02T12:04:10
#
#-------------------------------------------------

QT       += core gui\
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    bullet.cpp \
    game.cpp \
    score.cpp \
    player.cpp \
    enemy.cpp \
    zombie.cpp

HEADERS  += mainwindow.h \
    bullet.h \
    game.h \
    score.h \
    player.h \
    enemy.h \
    zombie.h

FORMS    += mainwindow.ui

RESOURCES += \
    audio.qrc
