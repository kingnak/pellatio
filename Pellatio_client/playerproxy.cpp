#include "playerproxy.h"
#include <data/gamestatedata.h>
#include <data/interactionoptionsdata.h>
#include <data/movedata.h>
#include "gameinterface.h"
#include "confirmmodel.h"
#include "rotationmodel.h"
#include "fieldmodel.h"
#include "piecemodel.h"
#include "infomodel.h"
#include "previewmodel.h"
#include "messagemodel.h"
#include "interactioncontroller.h"

PlayerProxy::PlayerProxy()
{
}

void PlayerProxy::setGameInterface(GameInterface *lgi)
{
    m_inter = lgi;
}

void PlayerProxy::updateAllData(const GameStateData &state, const InteractionOptionsData &interactOpts, const MoveData &preview)
{
    m_inter->infoModel()->updateData(state);
    m_inter->confirmModel()->updateData(interactOpts);
    m_inter->rotationModel()->updateData(interactOpts);
    m_inter->fieldModel()->updateData(interactOpts.fields());
    m_inter->previewModel()->updateData(preview);
    m_inter->pieceModel()->updateData(state.board().pieces());

    if (state.hasWinner()) {
        m_inter->notifyWinner(state.winner());
    }
}
