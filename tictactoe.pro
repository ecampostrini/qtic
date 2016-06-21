#-------------------------------------------------
#
# Project created by QtCreator 2016-05-26T11:58:58
#
#-------------------------------------------------

QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tictactoe
TEMPLATE = app


SOURCES += main.cpp\
        board.cpp \
    button.cpp \
    worker.cpp \
    gameboard.cpp \
    algorithms.cpp

HEADERS  += board.h \
    button.h \
    worker.h \
    gameboard.h \
    algorithms.h

FORMS    += board.ui
