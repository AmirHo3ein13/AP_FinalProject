#-------------------------------------------------
#
# Project created by QtCreator 2016-06-21T12:53:57
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SocceerStars
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    game.cpp \
    realplayer.cpp \
    player.cpp \
    circle.cpp \
    ball.cpp \
    formatation.cpp \
    socketthread.cpp

HEADERS  += mainwindow.h \
    game.h \
    realplayer.h \
    player.h \
    circle.h \
    ball.h \
    formatation.h \
    socketthread.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    ../Downloads/rsz_sockerfield.jpg
