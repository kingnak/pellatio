#-------------------------------------------------
#
# Project created by QtCreator 2015-09-10T12:24:58
#
#-------------------------------------------------

include(../Pellatio_global.pri)

QT       += network

QT       -= gui

TARGET = Pellatio_server
TEMPLATE = lib

DEFINES += PELLATIO_SERVER_LIBRARY

SOURCES += gamecontroller.cpp \
    board.cpp \
    interactioncontroller.cpp \
    piece.cpp \
    field.cpp \
    player.cpp \
    networkplayer.cpp \
    gameserver.cpp \
    clientconnection.cpp

HEADERS += gamecontroller.h\
        pellatio_server_global.h \
    board.h \
    interactioncontroller.h \
    piece.h \
    field.h \
    player.h \
    networkplayer.h \
    gameserver.h \
    clientconnection.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Pellatio_common/release/ -lPellatio_common
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Pellatio_common/debug/ -lPellatio_common
else:unix: LIBS += -L$$OUT_PWD/../Pellatio_common/ -lPellatio_common

INCLUDEPATH += $$PWD/../Pellatio_common
DEPENDPATH += $$PWD/../Pellatio_common
