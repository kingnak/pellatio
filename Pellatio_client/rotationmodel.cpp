#include "rotationmodel.h"
#include "gameinterface.h"

RotationModel::RotationModel(GameInterface *ctrl, QObject *parent) :
    QObject(parent), m_ctrl(ctrl)
{
}

bool RotationModel::canRotateCW() const
{
    return (m_data.rotation() & PellatioDefinitions::ClockWise) != 0;
}

bool RotationModel::canRotateCCW() const
{
    return (m_data.rotation() & PellatioDefinitions::CounterClockWise) != 0;
}

void RotationModel::updateData(InteractionOptionsData data)
{
    InteractionOptionsData old = m_data;
    m_data = data;
    if (old.rotation() != m_data.rotation()) {
        emit canRotateCCWChanged();
        emit canRotateCWChanged();
    }
}

void RotationModel::rotateCW()
{
    m_ctrl->rotateSelected(PellatioDefinitions::ClockWise);
}

void RotationModel::rotateCCW()
{
    m_ctrl->rotateSelected(PellatioDefinitions::CounterClockWise);
}
