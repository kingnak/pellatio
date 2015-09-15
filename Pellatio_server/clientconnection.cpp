#include "clientconnection.h"
#include "networkplayer.h"
#include "gamecontroller.h"

ClientConnection::ClientConnection(QTcpSocket *sock, GameController *ctrl, QObject *parent)
:   NetworkConnection(sock, parent),
    m_player(NULL),
    m_versionReceived(false),
    m_ctrl(ctrl)
{
    setPinging();
}

void ClientConnection::cleanup()
{
    if (m_player) {
        //m_player->destroy();
    }
    NetworkConnection::cleanup();
}

void ClientConnection::receivedMessage(const Message &msg)
{
    if (msg.type != Message::C_VERSION) {
        if (!m_versionReceived) {
            abort();
            return;
        }
    }

    switch (msg.type) {
    case Message::C_VERSION:
        handleVersion(msg.payload);
        break;

    default:
        NetworkConnection::receivedMessage(msg);
    }
}

void ClientConnection::handleVersion(const QVariant &v)
{
    quint32 vers;
    v >> vers;
    m_versionReceived = true;

    sendMessage(Message::S_VERSION, QVariant(Message::PROTOCOL_VERSION));
    if (vers != Message::PROTOCOL_VERSION) {
        close();
        return;
    }

    PellatioDefinitions::Color c;
    if (!m_ctrl->getNextPlayerColor(c)) {
        sendMessage(Message::S_CANNOT_ADD_PLAYER, QVariant());
        close();
        return;
    }

    m_player = new NetworkPlayer(this, c);
    if (!m_ctrl->addPlayer(m_player)) {
        sendMessage(Message::S_CANNOT_ADD_PLAYER, QVariant());
        close();
        return;
    }

    QVariant p;
    p << c;
    sendMessage(Message::S_PLAYER_ADDED, p);

    m_ctrl->start();
}
