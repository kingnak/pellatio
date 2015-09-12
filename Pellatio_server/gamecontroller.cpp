#include "gamecontroller.h"
#include "player.h"

#include <QEventLoop>
#include <QTimer>

GameController::GameController()
{
    m_curPlayer = PellatioDefinitions::Red;
    m_board.initializeStartBoard();
}

GameController::~GameController()
{
    qDeleteAll(m_interactors.values());
}

bool GameController::applyMove(MoveData move)
{
    MoveData finishedMove;
    // Transform all moves
    foreach (MoveData::MoveStep step, move.steps()) {
        Piece p = m_board.getPiece(step.activePieceId);
        if (!p.isValid()) {
            continue;
        }
        QList<MoveData::MoveStep> transformed = transformMove(step);
        foreach (MoveData::MoveStep s, transformed) {
            finishedMove.addStep(s);
        }
    }

    // Apply all transformed moves
    foreach (MoveData::MoveStep step, finishedMove.steps()) {
        Piece act = m_board.getPiece(step.activePieceId);
        Piece pass = m_board.getPiece(step.passivePieceId);
        switch (step.type) {
        case MoveData::MoveStep::Rotate:
            act.setDirection(PellatioDefinitions::rotated(act.direction(), step.rotation));
            m_board.updatePiece(act);
            break;
        case MoveData::MoveStep::Move:
            act.setField(step.moveField);
            m_board.updatePiece(act);
            break;
        case MoveData::MoveStep::MoveCapture:
            pass.setField(-1);
            m_board.updatePiece(pass);
            act.setField(step.moveField);
            m_board.updatePiece(act);
            break;
        case MoveData::MoveStep::MoveSelfCapture:
            act.setField(-1);
            m_board.updatePiece(act);
            break;
        }
    }


    foreach (InteractionController *c, m_interactors.values()) {
        c->publishMove(finishedMove, m_board);
    }

    changePlayer();

    return true;
}

bool GameController::addPlayer(Player *player)
{
    if (m_interactors.contains(player->thisPlayer())) {
        return false;
    }
    m_interactors[player->thisPlayer()] = new InteractionController(this, player);
    return true;
}

void GameController::changePlayer()
{
    PellatioDefinitions::Color oldPlayer = m_curPlayer;
    if (m_curPlayer == PellatioDefinitions::Black) {
        m_curPlayer = PellatioDefinitions::Red;
    } else {
        m_curPlayer = PellatioDefinitions::Black;
    }
    m_interactors[oldPlayer]->deactivate();
    m_interactors[m_curPlayer]->activate();
}

QList<MoveData::MoveStep> GameController::transformMove(MoveData::MoveStep move)
{
    if (move.type == MoveData::MoveStep::Rotate)
        return QList<MoveData::MoveStep>() << move;

    Q_ASSERT(move.type == MoveData::MoveStep::Move);

    QList<MoveData::MoveStep> ret;
    Piece act = m_board.getPiece(move.activePieceId);
    if (!act.isValid())
        return ret;

    const Field *to = m_board.field(move.moveField);
    if (!to)
        return ret;

    if (!to->hasPiece()) {
        // Nothing on destination, just move
        ret << move;
        return ret;
    }

    Piece pass = m_board.getPiece(to->pieceId());
    Q_ASSERT(pass.isValid());
    Q_ASSERT(pass.color() != act.color());

    move.passivePieceId = pass.id();

    // Aggressor => Aggressor => Selfcapture
    // (Other) => Aggressor => Capture
    if (pass.type() == PellatioDefinitions::Aggressor) {
        if (act.type() == PellatioDefinitions::Aggressor) {
            move.type = MoveData::MoveStep::MoveSelfCapture;
        } else {
            move.type = MoveData::MoveStep::MoveCapture;
        }
        ret << move;
        return ret;
    }

    // (Any) => (Non Aggressor) ==> Check if from Parade
    QList<PellatioDefinitions::MoveOffset> parDirs = pass.getParadeFields();
    PellatioDefinitions::Direction fromDir = PellatioDefinitions::reversed(move.direction);
    bool fromParade = false;
    foreach (PellatioDefinitions::MoveOffset m, parDirs) {
        if (m.toDirection() == fromDir) {
            fromParade = true;
            break;
        }
    }

    if (fromParade) {
        // Special: Phalangit can capture General / Kavalerist from parade
        if (act.type() == PellatioDefinitions::Phalangit) {
            if (pass.type() == PellatioDefinitions::Phalangit) {
                // Phalangit => Phalangit(parade) ==> Self Capture
                move.type = MoveData::MoveStep::MoveSelfCapture;
            } else {
                // Phalangit => (non-Phalangit)(Parade) ==> Capture
                move.type = MoveData::MoveStep::MoveCapture;
            }
        } else {
            // (Non-Phalangit) => (Any)(Parade) ==> Self Capture
            move.type = MoveData::MoveStep::MoveSelfCapture;
        }
    } else {
        // (Any) => (Any)(Non-Parade) ==> Capture
        move.type = MoveData::MoveStep::MoveCapture;
    }

    return QList<MoveData::MoveStep>() << move;
}
