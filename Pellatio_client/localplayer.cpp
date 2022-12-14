#include "localplayer.h"
#include "gameinterface.h"
#include "confirmmodel.h"
#include "rotationmodel.h"
#include "fieldmodel.h"
#include "piecemodel.h"
#include "infomodel.h"
#include "previewmodel.h"
#include "optionmodel.h"
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
    Q_UNUSED(board)
    // disable all options
    m_inter->animateMove(move);
}

void LocalPlayer::askForRemis()
{
    m_inter->optionModel()->remisOffered();
}

void LocalPlayer::remisDeclined()
{
    m_inter->optionModel()->remisDeclined();
}

void LocalPlayer::giveUp()
{
    m_ctrl->giveUp();
}

void LocalPlayer::offerRemis()
{
    m_ctrl->offerRemis();
}

void LocalPlayer::acceptRemis()
{
    m_ctrl->acceptRemis();
}

void LocalPlayer::declineRemis()
{
    m_ctrl->declineRemis();
}

void LocalPlayer::notifyTerminatedConnection()
{
    m_inter->connectionTerminated();
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
    InteractionOptionsData iod;
    m_inter->confirmModel()->updateData(iod);
    m_inter->rotationModel()->updateData(iod);
    m_ctrl->confirmMove();
}
