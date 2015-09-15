#include "message.h"

void operator <<(QVariant &data, const Message &target)
{
    QVariantMap map;
    map["type"] << target.type;
    map["payload"] << target.payload;
    data << map;
}

void operator >>(const QVariant &data, Message &target)
{
    QVariantMap map;
    data >> map;
    map["type"] >> target.type;
    map["payload"] >> target.payload;
}

DEFINE_ENUM_SERIALIZER(Message::Type)
