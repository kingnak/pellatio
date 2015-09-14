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
