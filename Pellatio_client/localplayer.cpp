#include "localplayer.h"
#include "gameinterface.h"
#include "confirmmodel.h"
#include "rotationmodel.h"
#include "fieldmodel.h"
#include "piecemodel.h"
#include "infomodel.h"
#include "previewmodel.h"
#include "interactioncontroller.h"

LocalPlayer::LocalPlayer(PellatioDefinitions::Color playerColor)
    : Player(playerColor)
{
}

PellatioDefinitions::Color LocalPlayer::thisPlayer() const
{
    return Player::thisPlayer();
}

void LocalPlayer::setGameInterface(GameInterface *lgi)
{
    m_inter = lgi;
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

void LocalPlayer::selectField(PellatioDefinitions::FieldIndex idx, bool autoConfirm)
{
    m_ctrl->selectField(idx, autoConfirm);
}

void LocalPlayer::rotateSelected(PellatioDefinitions::Rotation dir, bool autoConfirm)
{
    m_ctrl->rotateSelected(dir, autoConfirm);
}

void LocalPlayer::resetMove()
{
    m_ctrl->resetMove();
}

void LocalPlayer::confirmMove()
{
    m_ctrl->confirmMove();
}
