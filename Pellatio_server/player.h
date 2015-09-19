#ifndef PLAYER_H
#define PLAYER_H

#include "pellatio_server_global.h"
#include <pellatiodefinitions.h>
#include <data/boarddata.h>
#include <data/fielddata.h>
#include <data/gamestatedata.h>
#include <data/interactionoptionsdata.h>
#include <data/movedata.h>

class InteractionController;

class PELLATIO_SERVERSHARED_EXPORT Player
{
public:
    Player(PellatioDefinitions::Color playerColor);
    virtual ~Player() {}

    PellatioDefinitions::Color thisPlayer() const { return m_thisPlayer; }

    virtual void setInteractionController(InteractionController *ctrl);

    virtual void activate() = 0;
    virtual void deactivate() = 0;
    virtual void showMove(MoveData move, BoardData board) = 0;

    virtual void updateGameState(GameStateData state) { m_gameState = state; }
    virtual void updateInteractions(InteractionOptionsData options) { m_options = options; }
    virtual void updatePreviewMove(MoveData move) { m_previewMove = move; }

    virtual void commitUpdates() = 0;

    virtual void askForRemis() = 0;
    virtual void remisDeclined() = 0;

    virtual void notifyTerminatedConnection() = 0;

protected:
    PellatioDefinitions::Color m_thisPlayer;
    GameStateData m_gameState;
    InteractionOptionsData m_options;
    MoveData m_previewMove;

    InteractionController *m_ctrl;
};

#endif // PLAYER_H
