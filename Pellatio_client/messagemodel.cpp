#include "messagemodel.h"

MessageModel::MessageModel(QObject *parent) :
    QObject(parent), m_recv(NULL)
{
}

void MessageModel::win()
{
    emit won();
    emit show();
}

void MessageModel::lose()
{
    emit lost();
    emit show();
}

void MessageModel::endRemis()
{
    emit remis();
    emit show();
}

void MessageModel::terminate()
{
    emit terminated();
    emit show();
}

void MessageModel::generalMessage(QString msg)
{
    emit message(msg);
    emit show();
}

void MessageModel::confirm(QString msg, QString btn, QObject *recevier, const char *act)
{
    m_recv = recevier;
    m_func1 = act;
    emit dialog(msg, btn);
    emit show();
}

void MessageModel::ask(QString msg, QString op1, QString op2, QObject *receiver, const char *act1, const char *act2)
{
    m_recv = receiver;
    m_func1 = act1;
    m_func2 = act2;
    emit question(msg, op1, op2);
    emit show();
}

void MessageModel::chooseOption1()
{
    emit hide();
    QObject *obj = m_recv;
    m_recv = NULL;
    QMetaObject::invokeMethod(obj, m_func1.data());
}

void MessageModel::chooseOption2()
{
    emit hide();
    QObject *obj = m_recv;
    m_recv = NULL;
    QMetaObject::invokeMethod(obj, m_func2.data());
}

void MessageModel::confirmDialog()
{
    emit hide();
    QObject *obj = m_recv;
    m_recv = NULL;
    if (obj)
        QMetaObject::invokeMethod(obj, m_func1.data());
}
