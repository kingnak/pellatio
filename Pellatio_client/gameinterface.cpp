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
#include <iostream>

GameInterface::GameInterface(PlayerProxy *thisPlayer, QObject *parent) :
    QObject(parent), m_thisPlayer(thisPlayer)
{
    m_rotation = new RotationModel(this);
    m_confim = new ConfirmModel(this);
    m_fields = new FieldModel(this);
    m_pieces = new PieceModel;
    m_info = new InfoModel;
    m_preview = new PreviewModel;
    m_anim = new AnimationModel(this);

    thisPlayer->setGameInterface(this);
}

void GameInterface::confirmMove()
{
    return m_thisPlayer->confirmMove();
}

void GameInterface::resetMove()
{
    return m_thisPlayer->resetMove();
}

void GameInterface::select(PellatioDefinitions::FieldIndex idx)
{
    return m_thisPlayer->selectField(idx, m_confim->autoConfirm());
}

void GameInterface::rotateSelected(PellatioDefinitions::Rotation rot)
{
    return m_thisPlayer->rotateSelected(rot, m_confim->autoConfirm());
}

PellatioDefinitions::Color GameInterface::thisPlayer()
{
    return m_thisPlayer->thisPlayer();
}

void GameInterface::animateMove(MoveData move)
{
    m_anim->animate(move);
}
