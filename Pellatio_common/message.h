#ifndef MESSAGE_H
#define MESSAGE_H

#include "pellatio_common_global.h"
#include "pellatiodefinitions.h"
#include <QVariant>
#include <serializer.hpp>

struct PELLATIO_COMMONSHARED_EXPORT Message
{
    static const quint32 PROTOCOL_VERSION = 0x000100;

    enum Type {
        NO_MESSAGE,

        C_VERSION,
        S_VERSION,

        MSG_PING,
        MSG_PONG,

        S_CANNOT_ADD_PLAYER,
        S_PLAYER_ADDED,

        S_ACTIVATE_PLAYER,
        S_DEACTIVATE_PLAYER,
        S_COMMIT_UPDATES,
        S_PUBLISH_MOVE,

        C_SELECT_FIELD,
        C_SELECT_ROTATE,
        C_CONFIRM_MOVE,
        C_RESET_MOVE,

        DONT_UNDERSTAND = 0xFFFFFFFE,
        INVALID_MESSAGE = 0xFFFFFFFF
    } type;
    QVariant payload;

    DECLARE_SERIALIZABLE_EXPORT(PELLATIO_COMMONSHARED_EXPORT, Message);
};


DECLARE_ENUM_SERIALIZER_EXPORT(PELLATIO_COMMONSHARED_EXPORT, Message::Type);
Q_DECLARE_METATYPE(Message::Type)

#endif // MESSAGE_H
