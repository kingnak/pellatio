#ifndef NETWORKPLAYERPROXY_H
#define NETWORKPLAYERPROXY_H

#include <QObject>
#include "playerproxy.h"

struct Message;
class NetworkConnection;
class QTcpSocket;

class NetworkPlayerProxy : public QObject, public PlayerProxy
{
    Q_OBJECT
public:
    explicit NetworkPlayerProxy(QTcpSocket *sock, QObject *parent = 0);

    void start();

    virtual PellatioDefinitions::Color thisPlayer() const;
    virtual void selectField(PellatioDefinitions::FieldIndex idx, bool autoConfirm);
    virtual void rotateSelected(PellatioDefinitions::Rotation dir, bool autoConfirm);
    virtual void resetMove();
    virtual void confirmMove();

    virtual void giveUp();
    virtual void offerRemis();
    virtual void acceptRemis();
    virtual void declineRemis();

signals:

public slots:

private slots:
    void sendVersion();
    void shutdown();
    void handleMessage(const Message &msg);

private:
    NetworkConnection *m_conn;
    PellatioDefinitions::Color m_color;
};

#endif // NETWORKPLAYERPROXY_H
