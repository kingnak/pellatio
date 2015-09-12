#include "player.h"
#include "interactioncontroller.h"

Player::Player(PellatioDefinitions::Color playerColor)
    : m_thisPlayer(playerColor), m_ctrl(NULL)
{
}

void Player::setInteractionController(InteractionController *ctrl)
{
    Q_ASSERT(m_ctrl == NULL);
    m_ctrl = ctrl;
}

void Player::selectField(PellatioDefinitions::FieldIndex idx, bool autoConfirm)
{
    m_ctrl->selectField(idx, autoConfirm);
}

void Player::rotateSelected(PellatioDefinitions::Rotation dir, bool autoConfirm)
{
    m_ctrl->rotateSelected(dir, autoConfirm);
}

void Player::resetMove()
{
    m_ctrl->resetMove();
}

void Player::confirmMove()
{
    m_ctrl->confirmMove();
}
