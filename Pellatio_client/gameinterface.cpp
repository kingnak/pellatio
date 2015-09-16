#include "gameinterface.h"
#include "fieldmodel.h"
#include "piecemodel.h"
#include "rotationmodel.h"
#include "confirmmodel.h"
#include "infomodel.h"
#include "previewmodel.h"
#include "animationmodel.h"
#include "board.h"
#include "playerproxy.h"
#include "messagemodel.h"
#include "optionmodel.h"
#include <iostream>

GameInterface::GameInterface(PlayerProxy *thisPlayer, QObject *parent) :
    QObject(parent), m_msg(NULL), m_thisPlayer(thisPlayer)
{
    m_rotation = new RotationModel(this);
    m_confim = new ConfirmModel(this);
    m_fields = new FieldModel(this);
    m_pieces = new PieceModel;
    m_info = new InfoModel;
    m_preview = new PreviewModel;
    m_anim = new AnimationModel(this);
    m_opts = new OptionModel(this);

    thisPlayerChanged();
    thisPlayer->setGameInterface(this);
}

void GameInterface::setMessageModel(MessageModel *msg)
{
    m_msg = msg;
}

void GameInterface::confirmMove()
{
    m_thisPlayer->confirmMove();
}

void GameInterface::resetMove()
{
    m_thisPlayer->resetMove();
}

void GameInterface::select(PellatioDefinitions::FieldIndex idx)
{
    m_thisPlayer->selectField(idx, m_confim->autoConfirm());
}

void GameInterface::rotateSelected(PellatioDefinitions::Rotation rot)
{
    m_thisPlayer->rotateSelected(rot, m_confim->autoConfirm());
}

void GameInterface::giveUp()
{
    m_thisPlayer->giveUp();
}

void GameInterface::offerRemis()
{
    m_thisPlayer->offerRemis();
}

void GameInterface::acceptRemis()
{
    m_thisPlayer->acceptRemis();
}

void GameInterface::declineRemis()
{
    m_thisPlayer->declineRemis();
}

PellatioDefinitions::Color GameInterface::thisPlayer()
{
    return m_thisPlayer->thisPlayer();
}

void GameInterface::thisPlayerChanged()
{
    m_info->setThisPlayer(static_cast<ColorType::Color> (m_thisPlayer->thisPlayer()));
}

void GameInterface::animateMove(MoveData move)
{
    m_anim->animate(move);
}

void GameInterface::notifyWinner(PellatioDefinitions::Color winner)
{
    if (winner == m_thisPlayer->thisPlayer() && m_msg) {
        m_msg->win();
    } else {
        m_msg->lose();
    }
}

void GameInterface::notifyRemis()
{
    m_msg->endRemis();
}
