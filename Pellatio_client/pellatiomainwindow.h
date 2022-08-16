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
    Q_PROPERTY(bool allowTestBoard READ allowTestBoard NOTIFY allowTestBoardChanged_Dummy)
public:
    explicit PellatioMainWindow(QObject *parent = 0);
    ~PellatioMainWindow();

    bool allowTestBoard() const;

public slots:
    void startLocalSingleWindow();
    void startLocalMultipleWindow();
#ifdef WITH_TESTBOARD
    void startTestWindow();
#endif
    void hostGame();
    void jointGame(QString host);
    void start();

signals:
    void allowTestBoardChanged_Dummy();

private slots:

private:
    void setupInterface(QtQuick1ApplicationViewer &viewer, GameInterface *lgi, PellatioQMLDefinitions *d);

    GameController *m_game;
    QList<Player *> m_players;
    QList<GameInterface *> m_interfaces;
    QList<QWindow *> m_windows;
    PellatioQMLDefinitions *m_defs;

    QtQuick1ApplicationViewer *m_startWindow;
};

#endif // PELLATIOMAINWINDOW_H
