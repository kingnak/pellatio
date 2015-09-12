#include "localplayer.h"
#include "localgameinterface.h"
#include "confirmmodel.h"
#include "rotationmodel.h"
#include "fieldmodel.h"
#include "piecemodel.h"
#include "infomodel.h"
#include "previewmodel.h"

LocalPlayer::LocalPlayer(PellatioDefinitions::Color playerColor)
    : Player(playerColor)
{
}

void LocalPlayer::setGameInterface(LocalGameInterface *lgi)
{
    m_inter = lgi;
    lgi->addLocalPlayer(this);
}

void LocalPlayer::commitUpdates()
{
    m_inter->infoModel()->updateData(this->m_gameState);
    m_inter->confirmModel()->updateData(this->m_options);
    m_inter->rotationModel()->updateData(this->m_options);
    m_inter->fieldModel()->updateData(this->m_options.fields());
    m_inter->previewModel()->updateData(this->m_previewMove);
    m_inter->pieceModel()->updateData(this->m_gameState.board().pieces());
}

void LocalPlayer::showMove(MoveData move, BoardData board)
{
    m_inter->animateMove(move);
}
