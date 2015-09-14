#include "animationmodel.h"
#include <data/boarddata.h>
#include "gameinterface.h"
#include "piecemodel.h"
#include <QEventLoop>
#include <QTimer>
#include <iostream>
#include "flankmodel.h"

AnimationModel::AnimationModel(GameInterface *inter, QObject *parent) :
    QObject(parent), m_inter(inter), m_animCt(0)
{
    m_loop = new QEventLoop(this);
    m_flanks = new FlankModel;
}

void AnimationModel::animate(MoveData move)
{
    m_anims.append(move.steps());
    doAnimate();
}

void AnimationModel::animationStarted()
{
    m_animCt++;
}

void AnimationModel::animationFinished()
{
    m_animCt--;
    if (m_animCt == 0)
        doAnimateStep();
}

void AnimationModel::doAnimate()
{
    if (m_loop->isRunning()) return;

    if (!m_anims.isEmpty()) {
        doAnimateStep();
        m_loop->exec();
    }

    m_flanks->clear();
}

void AnimationModel::doAnimateStep()
{
    if (m_anims.isEmpty()) {
        m_loop->quit();
        return;
    }

    MoveData::MoveStep s = m_anims.takeFirst();

    // Dummy animation: Prevent end of animation before any started
    animationStarted();

    QString t;
    switch (s.type) {
    case MoveData::MoveStep::Move:
        t = QString(" %1->%2").arg(BoardData::fieldName(s.field), BoardData::fieldName(s.moveField));
        m_inter->pieceModel()->updateSinglePieceField(s.activePieceId, s.moveField);
        break;
    case MoveData::MoveStep::Rotate:
        t = s.rotation == PellatioDefinitions::ClockWise ? "rCW" : "rCCW";
        m_inter->pieceModel()->updateSinglePieceDirection(s.activePieceId, s.rotation);
        break;
    case MoveData::MoveStep::MoveCapture:
        t = QString(" %1->%2").arg(BoardData::fieldName(s.field), BoardData::fieldName(s.moveField));
        t += " X " + s.passivePieceId;
        m_inter->pieceModel()->updateSinglePieceField(s.activePieceId, s.moveField);
        m_inter->pieceModel()->updateSinglePieceCapture(s.passivePieceId, true);
        break;
    case MoveData::MoveStep::MoveSelfCapture:
        t = QString(" %1->%2").arg(BoardData::fieldName(s.field), BoardData::fieldName(s.moveField));
        t += " X self by " + s.passivePieceId;
        m_inter->pieceModel()->updateSinglePieceField(s.activePieceId, s.moveField);
        m_inter->pieceModel()->updateSinglePieceCapture(s.activePieceId, true);
        break;
    case MoveData::MoveStep::FlankedCapture:
        t = " XF " + s.passivePieceId;
        m_flanks->updateData(QList<MoveData::MoveStep>() << s);
        break;
    case MoveData::MoveStep::None:
        break;
    }

    std::cout << qPrintable(s.activePieceId) << qPrintable(t) << std::endl;

    // Dummy Animation
    QTimer::singleShot(10, this, SLOT(animationFinished()));

    // Real animation are handled in QML, through model updates above
}

