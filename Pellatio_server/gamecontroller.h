#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "pellatio_server_global.h"
#include "board.h"
#include "interactioncontroller.h"
#include <QMap>

class PELLATIO_SERVERSHARED_EXPORT GameController
{
public:
    GameController();
    ~GameController();

    Board board() const { return m_board; }

    bool applyMove(MoveData move);

    bool addPlayer(Player *player);

    bool start();

    void playerGivesUp(PellatioDefinitions::Color player);
    void playerOffersRemis(PellatioDefinitions::Color player);
    void playerAcceptsRemis();
    void playerDeclinesRemis(PellatioDefinitions::Color player);

    GameStateData getGameState() const;

    PellatioDefinitions::Color currentPlayer() const { return m_curPlayer; }
    void changePlayer();

    bool getNextPlayerColor(PellatioDefinitions::Color &c);

    QMap<PellatioDefinitions::Color, quint8> countPoints(bool *hasWinner = NULL, PellatioDefinitions::Color *winner = NULL)  const;
    //bool hasWinner(PellatioDefinitions::Color *c = NULL) const;

    void connectionTerminated();

private:
    QList<MoveData::MoveStep> transformMove(MoveData::MoveStep move);

    QList<MoveData::MoveStep> checkFlankingCaptures(MoveData::MoveStep baseMove);

private:
    bool m_started;
    Board m_board;
    PellatioDefinitions::Color m_curPlayer;
    QMap<PellatioDefinitions::Color, InteractionController *> m_interactors;
};

#endif // GAMECONTROLLER_H
