#include "pellatiomainwindow.h"
#include <QDeclarativeView>
#include <QDeclarativeItem>
#include <QDeclarativeContext>

#include "localgameinterface.h"
#include "rotationmodel.h"
#include "confirmmodel.h"
#include "fieldmodel.h"
#include "piecemodel.h"
#include "infomodel.h"
#include "previewmodel.h"
#include "animationmodel.h"
#include "flankmodel.h"
#include <localplayer.h>
#include <gamecontroller.h>
#include "qtquick1applicationviewer.h"

PellatioMainWindow::PellatioMainWindow(QObject *parent) :
    QObject(parent), m_game(NULL)
{
    m_defs = new PellatioQMLDefinitions;

    qmlRegisterType<PieceTypeType> ("Pellatio", 1, 0, "PieceType");
    qmlRegisterType<ColorType> ("Pellatio", 1, 0, "Color");
    qmlRegisterType<MoveType> ("Pellatio", 1, 0, "MoveType");
    qmlRegisterType<RotationType> ("Pellatio", 1, 0, "Rotation");

    m_startWindow = new QtQuick1ApplicationViewer;
}

void PellatioMainWindow::start() {
    m_startWindow->rootContext()->setContextProperty("window", this);
    m_startWindow->addImportPath(QLatin1String("modules"));
    m_startWindow->setOrientation(QtQuick1ApplicationViewer::ScreenOrientationAuto);
    m_startWindow->setMainQmlFile(QLatin1String("qrc:///main.qml"));
    m_startWindow->showExpanded();
}

PellatioMainWindow::~PellatioMainWindow()
{
    qDeleteAll(m_players);
    qDeleteAll(m_interfaces);
    qDeleteAll(m_windows);
    delete m_defs;
    delete m_game;
    delete m_startWindow;
}

void PellatioMainWindow::startLocalSingleWindow()
{
    m_startWindow->close();
    m_startWindow->deleteLater();
    m_startWindow = NULL;

    m_game = new GameController;
    LocalPlayer *p1 = new LocalPlayer(PellatioDefinitions::Red);
    m_game->addPlayer(p1);
    LocalPlayer *p2 = new LocalPlayer(PellatioDefinitions::Black);
    m_game->addPlayer(p2);

    m_players << p1 << p2;

    LocalGameInterface *lgi = new LocalGameInterface;
    p1->setGameInterface(lgi);
    p2->setGameInterface(lgi);


    m_interfaces << lgi;

    m_game->changePlayer();

    QtQuick1ApplicationViewer *viewer = new QtQuick1ApplicationViewer;

    m_windows << viewer;

    setupInterface(*viewer, lgi, m_defs);
}

/*
PellatioMainWindow::PellatioMainWindow(QObject *parent) :
    QObject(parent), m_view(view)
{
}

void PellatioMainWindow::changeView(QDeclarativeItem *container, QDeclarativeItem *oldItem, QDeclarativeItem *newItem)
{
    if (oldItem) {
        oldItem->hide();
    }
    newItem->show();
    container->setHeight(newItem->height());
    container->setWidth(newItem->width());
    resize(newItem->width(), newItem->height());
}

void PellatioMainWindow::resize(int w, int h)
{
    m_view->resize(w, h);
}
*/
void PellatioMainWindow::startLocalMultipleWindow()
{
    m_startWindow->close();
    m_startWindow->deleteLater();
    m_startWindow = NULL;

    m_game = new GameController;
    LocalPlayer *p1 = new LocalPlayer(PellatioDefinitions::Red);
    m_game->addPlayer(p1);
    LocalPlayer *p2 = new LocalPlayer(PellatioDefinitions::Black);
    m_game->addPlayer(p2);

    m_players << p1 << p2;

    LocalGameInterface *lgi1 = new LocalGameInterface;
    LocalGameInterface *lgi2 = new LocalGameInterface;
    p1->setGameInterface(lgi1);
    p2->setGameInterface(lgi2);

    m_interfaces << lgi1 << lgi2;

    m_game->changePlayer();

    QtQuick1ApplicationViewer *viewer1 = new QtQuick1ApplicationViewer;
    QtQuick1ApplicationViewer *viewer2 = new QtQuick1ApplicationViewer;

    m_windows << viewer1 << viewer2;

    setupInterface(*viewer1, lgi1, m_defs);
    setupInterface(*viewer2, lgi2, m_defs);
}

void PellatioMainWindow::setupInterface(QtQuick1ApplicationViewer &viewer, GameInterface *lgi, PellatioQMLDefinitions *d) {
    //viewer.rootContext()->setContextProperty("window", w);
    viewer.rootContext()->setContextProperty("def", d);
    viewer.rootContext()->setContextProperty("rotationModel", lgi->rotationModel());
    viewer.rootContext()->setContextProperty("confirmModel", lgi->confirmModel());
    viewer.rootContext()->setContextProperty("fieldModel", lgi->fieldModel());
    viewer.rootContext()->setContextProperty("pieceModel", lgi->pieceModel());
    viewer.rootContext()->setContextProperty("infoModel", lgi->infoModel());
    viewer.rootContext()->setContextProperty("previewModel", lgi->previewModel());
    viewer.rootContext()->setContextProperty("localPlayer", lgi->thisPlayer());
    viewer.rootContext()->setContextProperty("animationModel", lgi->animationModel());
    viewer.rootContext()->setContextProperty("flankModel", lgi->animationModel()->flankModel());

    viewer.addImportPath(QLatin1String("modules"));
    viewer.setOrientation(QtQuick1ApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qrc:///Game.qml"));
    viewer.showExpanded();
}
