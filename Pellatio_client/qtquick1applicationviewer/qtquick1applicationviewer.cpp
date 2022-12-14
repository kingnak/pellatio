// checksum 0x55ce version 0x90018
/*
  This file was generated by the Qt Quick 1 Application wizard of Qt Creator.
  QtQuick1ApplicationViewer is a convenience class containing mobile device
  specific code such as screen orientation handling. Also QML paths are
  handled here.
  It is recommended not to modify this file, since newer versions of Qt Creator
  may offer an updated version of it.
*/

#include "qtquick1applicationviewer.h"

#include <QQmlComponent>
#include <QQmlEngine>
#include <QQmlContext>


QtQuick1ApplicationViewer::QtQuick1ApplicationViewer(QWindow *parent)
    : QQuickView(parent)
{
    connect(engine(), SIGNAL(quit()), SLOT(close()));
    setResizeMode(QQuickView::SizeRootObjectToView);
}

QtQuick1ApplicationViewer::~QtQuick1ApplicationViewer()
{
}

QtQuick1ApplicationViewer *QtQuick1ApplicationViewer::create()
{
    return new QtQuick1ApplicationViewer();
}

void QtQuick1ApplicationViewer::setMainQmlFile(const QString &file)
{
    setSource(file);
}

void QtQuick1ApplicationViewer::addImportPath(const QString &path)
{
    engine()->addImportPath(path);
}

void QtQuick1ApplicationViewer::setOrientation(ScreenOrientation orientation)
{
#if QT_VERSION < 0x050000
    Qt::WidgetAttribute attribute;
    switch (orientation) {
    case ScreenOrientationLockPortrait:
        attribute = Qt::WA_LockPortraitOrientation;
        break;
    case ScreenOrientationLockLandscape:
        attribute = Qt::WA_LockLandscapeOrientation;
        break;
    default:
    case ScreenOrientationAuto:
        attribute = Qt::WA_AutoOrientation;
        break;
    };
    setAttribute(attribute, true);
#else // QT_VERSION < 0x050000
    Q_UNUSED(orientation)
#endif // QT_VERSION < 0x050000
}

void QtQuick1ApplicationViewer::showExpanded()
{
#if defined(Q_WS_SIMULATOR) || defined(Q_OS_QNX)
    showFullScreen();
#else
    show();
#endif
}
