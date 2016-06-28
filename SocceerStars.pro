#-------------------------------------------------
#
# Project created by QtCreator 2016-06-21T12:53:57
#
#-------------------------------------------------

QT  += core gui multimedia
QT += network
QT += multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SocceerStars
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    realplayer.cpp \
    player.cpp \
    circle.cpp \
    ball.cpp \
    formatation.cpp \
    border.cpp \
    game.cpp \
    socketthread.cpp \
    waiting.cpp

HEADERS  += mainwindow.h \
    realplayer.h \
    player.h \
    circle.h \
    ball.h \
    formatation.h \
    border.h \
    game.h \
    socketthread.h \
    waiting.h

FORMS    += mainwindow.ui \
    waiting.ui

    waiting.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    ../Downloads/rsz_sockerfield.jpg
