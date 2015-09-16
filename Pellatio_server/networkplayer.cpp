#include "networkplayer.h"
#include "interactioncontroller.h"

NetworkPlayer::NetworkPlayer(ClientConnection *conn, PellatioDefinitions::Color color, QObject *parent) :
    QObject(parent), Player(color), m_conn(conn)
{
    connect(m_conn, SIGNAL(messageReceived(Message)), this, SLOT(handleMessage(Message)));

}

void NetworkPlayer::activate()
{
    m_conn->sendMessage(Message::S_ACTIVATE_PLAYER, QVariant());
}

void NetworkPlayer::deactivate()
{
    m_conn->sendMessage(Message::S_DEACTIVATE_PLAYER, QVariant());
}

void NetworkPlayer::showMove(MoveData move, BoardData board)
{
    QVariantMap m;
    m["move"] << move;
    m["board"] << board;
    m_conn->sendMessage(Message::S_PUBLISH_MOVE, m);
}

void NetworkPlayer::commitUpdates()
{
    QVariantMap m;
    m["state"] << m_gameState;
    m["options"] << m_options;
    m["preview"] << m_previewMove;
    m_conn->sendMessage(Message::S_COMMIT_UPDATES, m);
}

void NetworkPlayer::askForRemis()
{
    m_conn->sendMessage(Message::S_REMIS_OFFERED, QVariant());
}

void NetworkPlayer::remisDeclined()
{
    m_conn->sendMessage(Message::S_REMIS_DECLINED, QVariant());
}

void NetworkPlayer::handleMessage(const Message &msg)
{
    switch (msg.type) {
    case Message::C_SELECT_FIELD: {
        QVariantMap v;
        msg.payload >> v;
        PellatioDefinitions::FieldIndex idx;
        bool autoConfirm;
        v["field"] >> idx;
        v["autoConfirm"] >> autoConfirm;
        m_ctrl->selectField(idx, autoConfirm);
    }
    case Message::C_SELECT_ROTATE: {
        QVariantMap v;
        msg.payload >> v;
        PellatioDefinitions::Rotation rot;
        bool autoConfirm;
        v["rotation"] >> rot;
        v["autoConfirm"] >> autoConfirm;
        m_ctrl->rotateSelected(rot, autoConfirm);
    }
        break;
    case Message::C_CONFIRM_MOVE:
        m_ctrl->confirmMove();
        break;
    case Message::C_RESET_MOVE:
        m_ctrl->resetMove();
        break;
    case Message::C_OFFER_REMIS:
        m_ctrl->offerRemis();
        break;
    case Message::C_ACCEPT_REMIS:
        m_ctrl->acceptRemis();
        break;
    case Message::C_DECLINE_REMIS:
        m_ctrl->declineRemis();
        break;
    default:
        m_conn->sendMessage(Message::DONT_UNDERSTAND, QVariant());
        break;
    }
}
