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

    PellatioDefinitions::Color currentPlayer() const { return m_curPlayer; }
    void changePlayer();

private:
    QList<MoveData::MoveStep> transformMove(MoveData::MoveStep move);

    QList<MoveData::MoveStep> checkFlankingCaptures(MoveData::MoveStep baseMove);

private:
    Board m_board;
    PellatioDefinitions::Color m_curPlayer;
    QMap<PellatioDefinitions::Color, InteractionController *> m_interactors;
};

#endif // GAMECONTROLLER_H
