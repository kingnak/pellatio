#include "gamecontroller.h"
#include "player.h"

#include <QEventLoop>
#include <QTimer>

GameController::GameController()
{
    m_started = false;
    m_curPlayer = PellatioDefinitions::Red;
    m_board.initializeStartBoard();
}

GameController::~GameController()
{
    qDeleteAll(m_interactors.values());
}

#ifdef WITH_TESTBOARD
void GameController::loadTestBoard(QString boardFile)
{
    m_board.initializeTestBoard(boardFile);
}
#endif

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
        case MoveData::MoveStep::FlankedCapture:
            pass.setField(-1);
            m_board.updatePiece(pass);
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
    if (m_interactors.size() >= 2) {
        return false;
    }
    m_interactors[player->thisPlayer()] = new InteractionController(this, player);
    return true;
}

bool GameController::start()
{
    if (m_started) return false;
    if (m_interactors.size() == 2) {
        changePlayer();
        return true;
    }
    return false;
}

void GameController::playerGivesUp(PellatioDefinitions::Color player)
{
    GameStateData st = getGameState();
    st.setGameState(PellatioDefinitions::Winner);
    st.setHasWinner(true);
    st.setWinner(PellatioDefinitions::opponent(player));

    foreach (InteractionController *in, m_interactors.values()) {
        in->publishGameState(st);
    }
}

void GameController::playerOffersRemis(PellatioDefinitions::Color player)
{
    //GameStateData st = getGameState();
    //st.setRemisOffered(true);
    //m_interactors[PellatioDefinitions::opponent(player)]->publishGameState(st);
    m_interactors[PellatioDefinitions::opponent(player)]->askForRemis();
}

void GameController::playerAcceptsRemis()
{
    GameStateData st = getGameState();
    st.setGameState(PellatioDefinitions::Remis);
    foreach (InteractionController *in, m_interactors.values()) {
        in->publishGameState(st);
    }
}

void GameController::playerDeclinesRemis(PellatioDefinitions::Color player)
{
    m_interactors[PellatioDefinitions::opponent(player)]->remisDeclined();
}

GameStateData GameController::getGameState() const
{
    GameStateData st;
    st.setBoard(m_board.toData());
    st.setCurrentPlayer(m_curPlayer);
    st.setGameState(PellatioDefinitions::Running);

    bool hasWinner;
    PellatioDefinitions::Color winner;
    QMap<PellatioDefinitions::Color, quint8> points = countPoints(&hasWinner, &winner);
    st.setBlackPoints(points[PellatioDefinitions::Black]);
    st.setRedPoints(points[PellatioDefinitions::Red]);

    if (hasWinner) {
        st.setHasWinner(true);
        st.setWinner(winner);
        st.setGameState(PellatioDefinitions::Winner);
    }
    return st;
}

void GameController::changePlayer()
{
    PellatioDefinitions::Color oldPlayer = m_curPlayer;
    m_curPlayer = PellatioDefinitions::opponent(m_curPlayer);
    m_interactors[oldPlayer]->deactivate();
    m_interactors[m_curPlayer]->activate();
}

bool GameController::getNextPlayerColor(PellatioDefinitions::Color &c)
{
    switch (m_interactors.size()) {
    case 0:
        c = PellatioDefinitions::Black;
        return true;
    case 1:
        c = PellatioDefinitions::Red;
        return true;
    default:
        return false;
    }
}

QMap<PellatioDefinitions::Color, quint8> GameController::countPoints(bool *hasWinner, PellatioDefinitions::Color *winner) const
{
    // Dummies if pointers are null
    bool dummyHasWinner;
    PellatioDefinitions::Color dummyWinner;
    if (!hasWinner) hasWinner = &dummyHasWinner;
    if (!winner) winner = &dummyWinner;

    *hasWinner = false;
    PellatioDefinitions::Color generalCaptureColor;
    QMap<PellatioDefinitions::Color, quint8> ret;
    // Sum up
    foreach (Piece p, m_board.pieces()) {
        if (!p.onField()) {
            PellatioDefinitions::Color pointsFor = (p.color() == PellatioDefinitions::Red) ? PellatioDefinitions::Black : PellatioDefinitions::Red;
            quint8 points = 0;
            switch (p.type()) {
            case PellatioDefinitions::Aggressor: points = 1; break;
            case PellatioDefinitions::Phalangit: points = 3; break;
            case PellatioDefinitions::Kavalerist: points = 6; break;
            case PellatioDefinitions::General:
                // If general is captured, we have a winner
                points = 9;
                *hasWinner = true;
                generalCaptureColor = pointsFor;
                break;
            }
            ret[pointsFor] += points;
        }
    }

    if (*hasWinner) {
        if (ret[PellatioDefinitions::Black] == ret[PellatioDefinitions::Red]) {
            // On draw, the one that has captured the general wins
            *winner = generalCaptureColor;
        } else if (ret[PellatioDefinitions::Black] > ret[PellatioDefinitions::Red]) {
            *winner = PellatioDefinitions::Black;
        } else {
            *winner = PellatioDefinitions::Red;
        }
    }

    return ret;
}

void GameController::connectionTerminated()
{
    foreach (InteractionController *in, m_interactors) {
        in->notifyTerminatedConnection();
    }
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

        // Add Flanking
        ret.append(checkFlankingCaptures(move));

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

        // Add Flanking If Capture
        if (move.type == MoveData::MoveStep::MoveCapture) {
            ret.append(checkFlankingCaptures(move));
        }

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

    ret << move;

    //Add Flanking if Capture or Move
    if (move.type == MoveData::MoveStep::Move || move.type == MoveData::MoveStep::MoveCapture) {
        ret.append(checkFlankingCaptures(move));
    }

    return ret;
}

QList<MoveData::MoveStep> GameController::checkFlankingCaptures(MoveData::MoveStep baseMove)
{
    Q_ASSERT(baseMove.type == MoveData::MoveStep::Move || baseMove.type == MoveData::MoveStep::MoveCapture);

    QList<MoveData::MoveStep> ret;

    Piece act = m_board.getPiece(baseMove.activePieceId);

    for (int i = 0; i < 8; ++i) {
        PellatioDefinitions::Direction dir = static_cast<PellatioDefinitions::Direction> (i);

        PellatioDefinitions::MoveOffset off = PellatioDefinitions::MoveOffset::fromDirection(dir);
        int xFar = BoardData::xForIndex(baseMove.moveField) + off.dx*2;
        int yFar = BoardData::yForIndex(baseMove.moveField) + off.dy*2;

        if (BoardData::validXandY(xFar, yFar)) {
            const Field *fFar = m_board.field(BoardData::indexForXandY(xFar, yFar));
            if (fFar->hasPiece() && m_board.getPiece(fFar->pieceId()).color() == act.color()) {
                // Flanking position. Check if there is a flanked piece
                int xNear = BoardData::xForIndex(baseMove.moveField) + off.dx;
                int yNear = BoardData::yForIndex(baseMove.moveField) + off.dy;

                if (BoardData::validXandY(xNear, yNear)) {
                    const Field *fNear = m_board.field(BoardData::indexForXandY(xNear, yNear));
                    if (fNear->hasPiece()) {
                        Piece pass = m_board.getPiece(fNear->pieceId());
                        if (pass.color() != act.color()) {
                            // FLANKED!
                            MoveData::MoveStep flank = MoveData::MoveStep::flank(act, pass, dir);
                            ret << flank;
                        }
                    }
                }
            }
        }

    }

    return ret;
}
