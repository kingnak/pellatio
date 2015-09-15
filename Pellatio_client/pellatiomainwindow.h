#ifndef PELLATIOMAINWINDOW_H
#define PELLATIOMAINWINDOW_H

#include <QWidget>

class QDeclarativeView;
class QDeclarativeItem;

class Player;
class GameInterface;
class GameController;
class QtQuick1ApplicationViewer;
class DualGameInterface;
class PellatioQMLDefinitions;

class PellatioMainWindow : public QObject
{
    Q_OBJECT
public:
    explicit PellatioMainWindow(QObject *parent = 0);
    ~PellatioMainWindow();

public slots:
    void startLocalSingleWindow();
    void startLocalMultipleWindow();
    void hostGame();
    void jointGame(QString host);
    void start();

private slots:

private:
    void setupInterface(QtQuick1ApplicationViewer &viewer, GameInterface *lgi, PellatioQMLDefinitions *d);

    GameController *m_game;
    QList<Player *> m_players;
    QList<GameInterface *> m_interfaces;
    QList<QWidget *> m_windows;
    PellatioQMLDefinitions *m_defs;

    QtQuick1ApplicationViewer *m_startWindow;
};

#endif // PELLATIOMAINWINDOW_H
