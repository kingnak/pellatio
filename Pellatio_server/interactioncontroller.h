#ifndef INTERACTIONCONTROLLER_H
#define INTERACTIONCONTROLLER_H

#include "board.h"
#include <data/gamestatedata.h>
#include <data/movedata.h>
#include "pellatio_server_global.h"

class GameController;
class Player;

class PELLATIO_SERVERSHARED_EXPORT InteractionController
{
public:
    InteractionController(GameController *ctrl, Player *player);

    // OUTGOING: SERVER => CLIENT
    void activate();
    void deactivate();
    void publishMove(MoveData move, Board board);
    void publishGameState(GameStateData st);
    void askForRemis();
    void remisDeclined();

    // INCOMMING: CLIENT => SERVER
    void selectField(PellatioDefinitions::FieldIndex idx, bool autoConfirm);
    void rotateSelected(PellatioDefinitions::Rotation dir, bool autoConfirm);
    void resetMove();
    void confirmMove();

    void giveUp();
    void offerRemis();
    void acceptRemis();
    void declineRemis();

    void connectionTerminated();
    void notifyTerminatedConnection();

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
