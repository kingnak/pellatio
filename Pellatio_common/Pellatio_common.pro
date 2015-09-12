#-------------------------------------------------
#
# Project created by QtCreator 2015-09-10T11:27:09
#
#-------------------------------------------------

#QT       += network

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
    data/movedata.cpp

HEADERS += pellatiodefinitions.h\
        pellatio_common_global.h \
    serializer.hpp \
    data/piecedata.h \
    data/fielddata.h \
    data/interactionoptionsdata.h \
    data/boarddata.h \
    data/gamestatedata.h \
    data/movedata.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
