#include "messagemodel.h"

MessageModel::MessageModel(QObject *parent) :
    QObject(parent)
{
}

void MessageModel::win()
{
    emit won();
}

void MessageModel::lose()
{
    emit lost();
}

void MessageModel::terminate()
{
    emit terminated();
}

void MessageModel::generalMessage(QString msg)
{
    emit message(msg);
}
