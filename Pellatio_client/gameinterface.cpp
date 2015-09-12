#include "gameinterface.h"
#include "fieldmodel.h"
#include "piecemodel.h"
#include "rotationmodel.h"
#include "confirmmodel.h"
#include "infomodel.h"
#include "previewmodel.h"
#include "animationmodel.h"
#include "board.h"
#include <iostream>

GameInterface::GameInterface(QObject *parent) :
    QObject(parent)
{
    m_rotation = new RotationModel(this);
    m_confim = new ConfirmModel(this);
    m_fields = new FieldModel(this);
    m_pieces = new PieceModel;
    m_info = new InfoModel;
    m_preview = new PreviewModel;
    m_anim = new AnimationModel(this);
}

void GameInterface::animateMove(MoveData move)
{
    m_anim->animate(move);
}
