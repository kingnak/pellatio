#ifndef INTERACTIONCONTROLLER_H
#define INTERACTIONCONTROLLER_H

#include "board.h"
#include <data/movedata.h>

class GameController;
class Player;

class InteractionController
{
public:
    InteractionController(GameController *ctrl, Player *player);

    void activate();
    void deactivate();
    void publishMove(MoveData move, Board board);

    void selectField(PellatioDefinitions::FieldIndex idx, bool autoConfirm);
    void rotateSelected(PellatioDefinitions::Rotation dir, bool autoConfirm);
    void resetMove();
    void confirmMove();

private:
    void reset();
    void postMoveUpdates(bool autoConfirm);
    void updateFields();

    bool moveStarted() const;
    bool moveFinished() const;
    bool canRotate() const;
    bool canMove(int len) const;
    bool checkFieldFlankedForMove(PellatioDefinitions::FieldIndex idx, PellatioDefinitions::Color forColor);

    bool isCurrentPlayerActive() const;

private:
    GameController *m_ctrl;
    Player *m_player;
    Board m_workingBoard;

    MoveData m_move;

    QString m_selectedPieceId;

};

#endif // INTERACTIONCONTROLLER_H
