
#QT       += network

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    pellatiomainwindow.cpp \
    gameinterface.cpp \
    confirmmodel.cpp \
    fieldmodel.cpp \
    piecemodel.cpp \
    rotationmodel.cpp \
    localgameinterface.cpp \
    pellatioqmldefinitions.cpp \
    localplayer.cpp \
    infomodel.cpp \
    previewmodel.cpp \
    animationmodel.cpp

RESOURCES += qml.qrc

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick1applicationviewer/qtquick1applicationviewer.pri)

# Default rules for deployment.
include(deployment.pri)

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Pellatio_common/release/ -lPellatio_common
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Pellatio_common/debug/ -lPellatio_common
else:unix: LIBS += -L$$OUT_PWD/../Pellatio_common/ -lPellatio_common

INCLUDEPATH += $$PWD/../Pellatio_common
DEPENDPATH += $$PWD/../Pellatio_common

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Pellatio_server/release/ -lPellatio_server
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Pellatio_server/debug/ -lPellatio_server
else:unix: LIBS += -L$$OUT_PWD/../Pellatio_server/ -lPellatio_server

INCLUDEPATH += $$PWD/../Pellatio_server
DEPENDPATH += $$PWD/../Pellatio_server

HEADERS += \
    pellatiomainwindow.h \
    gameinterface.h \
    confirmmodel.h \
    fieldmodel.h \
    piecemodel.h \
    rotationmodel.h \
    localgameinterface.h \
    pellatioqmldefinitions.h \
    localplayer.h \
    infomodel.h \
    previewmodel.h \
    animationmodel.h
