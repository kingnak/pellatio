#-------------------------------------------------
#
# Project created by QtCreator 2015-09-10T11:27:09
#
#-------------------------------------------------

include(../Pellatio_global.pri)

QT       += network

QT       -= gui

TARGET = Pellatio_common
TEMPLATE = lib

DEFINES += PELLATIO_COMMON_LIBRARY

SOURCES += pellatiodefinitions.cpp \
    data/piecedata.cpp \
    data/fielddata.cpp \
    data/interactionoptionsdata.cpp \
    data/boarddata.cpp \
    data/gamestatedata.cpp \
    data/movedata.cpp \
    message.cpp \
    networkconnection.cpp

HEADERS += pellatiodefinitions.h\
        pellatio_common_global.h \
    serializer.hpp \
    data/piecedata.h \
    data/fielddata.h \
    data/interactionoptionsdata.h \
    data/boarddata.h \
    data/gamestatedata.h \
    data/movedata.h \
    message.h \
    networkconnection.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
