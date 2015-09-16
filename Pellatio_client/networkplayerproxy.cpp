#include "networkplayerproxy.h"
#include "message.h"
#include <QTcpSocket>
#include <networkconnection.h>
#include "gameinterface.h"
#include <data/gamestatedata.h>
#include <data/movedata.h>
#include <data/interactionoptionsdata.h>
#include "confirmmodel.h"
#include "rotationmodel.h"
#include "fieldmodel.h"
#include "piecemodel.h"
#include "infomodel.h"
#include "previewmodel.h"
#include "optionmodel.h"
#include <QDebug>

NetworkPlayerProxy::NetworkPlayerProxy(QTcpSocket *sock, QObject *parent) :
    QObject(parent)
{
    m_conn = new NetworkConnection(sock, this);
    connect(m_conn, SIGNAL(messageReceived(Message)), this, SLOT(handleMessage(Message)));
    connect(m_conn, SIGNAL(shutdown()), this, SLOT(shutdown()));
    m_conn->startup();
}

void NetworkPlayerProxy::start()
{
    sendVersion();
}

PellatioDefinitions::Color NetworkPlayerProxy::thisPlayer() const
{
    return m_color;
}

void NetworkPlayerProxy::selectField(PellatioDefinitions::FieldIndex idx, bool autoConfirm)
{
    QVariantMap m;
    m["field"] << idx;
    m["autoConfirm"] << autoConfirm;
    m_conn->sendMessage(Message::C_SELECT_FIELD, m);
}

void NetworkPlayerProxy::rotateSelected(PellatioDefinitions::Rotation dir, bool autoConfirm)
{
    QVariantMap m;
    m["rotation"] << dir;
    m["autoConfirm"] << autoConfirm;
    m_conn->sendMessage(Message::C_SELECT_ROTATE, m);
}

void NetworkPlayerProxy::resetMove()
{
    m_conn->sendMessage(Message::C_RESET_MOVE, QVariant());
}

void NetworkPlayerProxy::confirmMove()
{
    m_conn->sendMessage(Message::C_CONFIRM_MOVE, QVariant());
}

void NetworkPlayerProxy::giveUp()
{
    m_conn->sendMessage(Message::C_GIVE_UP, QVariant());
}

void NetworkPlayerProxy::offerRemis()
{
    m_conn->sendMessage(Message::C_OFFER_REMIS, QVariant());
}

void NetworkPlayerProxy::acceptRemis()
{
    m_conn->sendMessage(Message::C_ACCEPT_REMIS, QVariant());
}

void NetworkPlayerProxy::declineRemis()
{
    m_conn->sendMessage(Message::C_DECLINE_REMIS, QVariant());
}

void NetworkPlayerProxy::sendVersion()
{
    QVariant v;
    v << 0x000100;//Message::PROTOCOL_VERSION;
    m_conn->sendMessage(Message::C_VERSION, v);
}

void NetworkPlayerProxy::shutdown()
{

}

void NetworkPlayerProxy::handleMessage(const Message &msg)
{
    switch (msg.type) {
    case Message::S_VERSION: {
        quint32 vers;
        msg.payload >> vers;
        if (vers != Message::PROTOCOL_VERSION) {
            qDebug("Protocol Missmatch");
        }
        break;
    }

    case Message::S_PLAYER_ADDED: {
        PellatioDefinitions::Color c;
        msg.payload >> c;
        m_color = c;
        m_inter->thisPlayerChanged();
        break;
    }
    case Message::S_CANNOT_ADD_PLAYER:
        qDebug("Cannot add Player");
        break;

    case Message::S_ACTIVATE_PLAYER:
    case Message::S_DEACTIVATE_PLAYER:
        break;


    case Message::S_COMMIT_UPDATES: {
        QVariantMap m;
        GameStateData st;
        InteractionOptionsData op;
        MoveData mov;
        msg.payload >> m;
        m["state"] >> st;
        m["options"] >> op;
        m["preview"] >> mov;
        updateAllData(st, op, mov);
        break;
    }

    case Message::S_PUBLISH_MOVE: {
        MoveData move;
        BoardData board;
        QVariantMap m;
        msg.payload >> m;
        m["move"] >> move;
        m["board"] >> board;
        m_inter->animateMove(move);
        break;
    }

    case Message::S_REMIS_OFFERED:
        m_inter->optionModel()->remisOffered();
        break;

    case Message::S_REMIS_DECLINED:
        m_inter->optionModel()->remisDeclined();
        break;

    default:
        qDebug() << "Did not understand message" << msg.type;
    }
}
