#include "interactioncontroller.h"
#include "gamecontroller.h"
#include "player.h"
#include <QPoint>

InteractionController::InteractionController(GameController *ctrl, Player *player)
    : m_ctrl(ctrl), m_player(player)
{
    m_player->setInteractionController(this);
}

void InteractionController::activate()
{
    reset();
    m_player->activate();
    postMoveUpdates(false);
}

void InteractionController::deactivate()
{
    reset();
    m_player->deactivate();
    postMoveUpdates(false);
}

void InteractionController::publishMove(MoveData move, Board board)
{
    m_player->showMove(move, board.toData());
}

void InteractionController::selectField(PellatioDefinitions::FieldIndex idx, bool autoConfirm)
{
    const Field *f = m_workingBoard.field(idx);
    Piece p = m_workingBoard.getPiece(m_selectedPieceId);

    if (isCurrentPlayerActive()) {
        // Current player.
        // If movable to, move
        if (p.isValid()) {
            if (f->isMovable()) {
                // Move to this field
                if (canMove(f->moveLength())) {
                    m_move.addStep(MoveData::MoveStep::move(p, f->moveDirection(), f->moveLength(), f->index()));
                    p.setField(f->index());
                    m_workingBoard.updatePiece(p);
                    postMoveUpdates(autoConfirm);
                    return;
                }
            }
        }
        // Check if piece can be changed
        if (moveStarted()) {
            return;
            /*
            if (f->hasPiece()) {
                // Don't change piece if move has started
                return;
            }
            */
        }
    }

    // Not movable to, or piece can be changed.
    // Set piece active
    m_selectedPieceId = f->pieceId();
    postMoveUpdates(autoConfirm);
}

void InteractionController::rotateSelected(PellatioDefinitions::Rotation dir, bool autoConfirm)
{
    if (!isCurrentPlayerActive())
        return;

    Piece p = m_workingBoard.getPiece(m_selectedPieceId);
    if (p.isValid()) {
        if (p.getRotationModes() & dir) {
            if (canRotate()) {
                // Update move
                m_move.addStep(MoveData::MoveStep::rotate(p, dir));
                p.setDirection(PellatioDefinitions::rotated(p.direction(), dir));
                m_workingBoard.updatePiece(p);
            }
            postMoveUpdates(autoConfirm);
        }
    }
}

void InteractionController::resetMove()
{
    if (!isCurrentPlayerActive())
        return;

    reset();
    //m_player->updateBoard(m_workingBoard.toData());
    postMoveUpdates(false);
}

void InteractionController::confirmMove()
{
    if (!isCurrentPlayerActive())
        return;

    m_ctrl->applyMove(m_move);
}

void InteractionController::reset()
{
    m_workingBoard = m_ctrl->board();
    m_move.clear();
    m_selectedPieceId = QString::null;
}

void InteractionController::postMoveUpdates(bool autoConfirm)
{
    if (autoConfirm && moveFinished()) {
        confirmMove();
        return;
    }

    updateFields();
    //m_player->updateBoard(m_workingBoard.toData());
    GameStateData st;
    //st.setBoard(m_workingBoard.toData());
    st.setBoard(m_ctrl->board().toData());
    st.setCurrentPlayer(m_ctrl->currentPlayer());
    m_player->updateGameState(st);

    InteractionOptionsData iod;
    iod.setConfirmMove(moveStarted());
    iod.setResetMove(moveStarted());
    if (canRotate()) {
        Piece p = m_workingBoard.getPiece(m_selectedPieceId);
        if (p.isValid() && p.color() == m_player->thisPlayer()) iod.setRotation(p.getRotationModes());
    }
    iod.setFields(m_workingBoard.getFieldData());
    m_player->updateInteractions(iod);

    m_player->updatePreviewMove(m_move);
    m_player->commitUpdates();
}

void InteractionController::updateFields()
{
    // Reset
    m_workingBoard.resetFieldStates();
    // Get selected piece (can be null, own, or enemy)
    const Piece p = m_workingBoard.getPiece(m_selectedPieceId);
    if (p.isValid() && p.onField()) {
        // SELECT ON ORIGINAL BOARD!
        //m_workingBoard.fields()[p.field()].setSelected(true);
        m_workingBoard.fields()[m_ctrl->board().getPiece(p.id()).field()].setSelected(true);

        const int cx = BoardData::xForIndex(p.field());
        const int cy = BoardData::yForIndex(p.field());

        // Show parade
        // Only if move not started!
        if (!moveStarted()) {
            QList<PellatioDefinitions::MoveOffset> parade = p.getParadeFields();
            foreach (PellatioDefinitions::MoveOffset off, parade) {
                int x = cx + off.dx;
                int y = cy + off.dy;
                if (BoardData::validXandY(x, y)) {
                    m_workingBoard.fields()[BoardData::indexForXandY(x,y)].setParade(true);
                }
            }
        }

        // Show movable. If move has stared, this will not show moveable, if already moved
        if (p.color() == m_player->thisPlayer()) {
            QList<PellatioDefinitions::MoveOffset> movable = p.getMovableFields();
            const int maxMove = p.moveCount() - m_move.getMoveLength();
            foreach (PellatioDefinitions::MoveOffset off, movable) {
                for (int l = 1; l <= off.len && l <= maxMove; ++l) {
                    if (!canMove(l)) {
                        break;
                    }
                    int x = cx + l*off.dx;
                    int y = cy + l*off.dy;
                    if (BoardData::validXandY(x,y)) {
                        Field &f = m_workingBoard.fields()[BoardData::indexForXandY(x,y)];
                        if (f.hasPiece()) {
                            // If foreign piece, can move here. But still, break!
                            Piece other = m_workingBoard.getPiece(f.pieceId());
                            if (other.color() != p.color()) {
                                f.setMovable(true);
                                f.setMoveDirection(off.dir);
                                f.setMoveLength(l);
                            }
                            break;
                        }
                        f.setMovable(true);
                        f.setMoveDirection(off.dir);
                        f.setMoveLength(l);
                    }
                }
            }
        }
    }

    if (!moveStarted() && isCurrentPlayerActive()) {
        // Show own pieces as selected
        QList<Piece> pieces = m_workingBoard.pieces();
        foreach (Piece p, pieces) {
            if (p.isValid() && p.onField() && p.color() == m_player->thisPlayer()) {
                m_workingBoard.fields()[p.field()].setSelectable(true);
            }
        }
    }
}

bool InteractionController::moveStarted() const
{
    return !m_move.steps().isEmpty();
}

bool InteractionController::moveFinished() const
{
    Piece p = m_workingBoard.getPiece(m_selectedPieceId);
    if (p.isValid()) {
        if (m_move.getMoveLength() >= p.moveCount()) {
            return true;
        }
    }

    return false;
}

bool InteractionController::canRotate() const
{
    if (!isCurrentPlayerActive())
        return false;

    Piece p = m_workingBoard.getPiece(m_selectedPieceId);
    if (!p.isValid())
        return false;

    if (m_move.getMoveLength() >= p.moveCount())
        return false;

    foreach (MoveData::MoveStep s, m_move.steps()) {
        if (s.type == MoveData::MoveStep::Rotate) {
            return false;
        }
    }
    return p.getRotationModes() != PellatioDefinitions::None;
}

bool InteractionController::canMove(int len) const
{
    if (!isCurrentPlayerActive())
        return false;
    Piece p = m_workingBoard.getPiece(m_selectedPieceId);
    if (!p.isValid())
        return false;

    // Can move only once
    foreach (MoveData::MoveStep s, m_move.steps()) {
        if (s.type == MoveData::MoveStep::Move) {
            return false;
        }
    }

    if (m_move.getMoveLength() + len <= p.moveCount())
        return true;
    return false;
}

bool InteractionController::isCurrentPlayerActive() const
{
    return m_ctrl->currentPlayer() == m_player->thisPlayer();
}
