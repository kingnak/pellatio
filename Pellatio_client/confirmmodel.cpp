#include "confirmmodel.h"
#include "gameinterface.h"

ConfirmModel::ConfirmModel(GameInterface *ctrl, QObject *parent) :
    QObject(parent), m_ctrl(ctrl), m_autoConfirm(false)
{
}

void ConfirmModel::setAutoConfirm(bool ac)
{
    if (ac == m_autoConfirm)
        return;
    m_autoConfirm = ac;
    emit autoConfirmChanged();
}


void ConfirmModel::updateData(InteractionOptionsData data)
{
    InteractionOptionsData old = m_data;
    m_data = data;
    if (old.canConfirmMove() != m_data.canConfirmMove()) emit canConfirmChanged();
    if (old.canResetMove() != m_data.canResetMove()) emit canResetChanged();
}

void ConfirmModel::confirm()
{
    m_ctrl->confirmMove();
}

void ConfirmModel::reset()
{
    m_ctrl->resetMove();
}
