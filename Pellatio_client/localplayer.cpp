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

void LocalPlayer::commitUpdates()
{
    updateAllData(m_gameState, m_options, m_previewMove);
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
