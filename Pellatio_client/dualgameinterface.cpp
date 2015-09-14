#include "dualgameinterface.h"
#include "infomodel.h"
#include "localplayer.h"
#include "confirmmodel.h"

DualGameInterface::DualGameInterface(PlayerProxy *p1, PlayerProxy *p2, QObject *parent)
    : GameInterface(p1, parent), m_anim(false)
{
    m_player[p1->thisPlayer()] = p1;
    m_player[p2->thisPlayer()] = p2;
    p2->setGameInterface(this);
}

void DualGameInterface::confirmMove()
{
    m_thisPlayer = m_player[static_cast<PellatioDefinitions::Color> (m_info->currentPlayer())];
    GameInterface::confirmMove();
}

void DualGameInterface::resetMove()
{
    m_thisPlayer = m_player[static_cast<PellatioDefinitions::Color> (m_info->currentPlayer())];
    GameInterface::resetMove();
}

void DualGameInterface::select(PellatioDefinitions::FieldIndex idx)
{
    m_thisPlayer = m_player[static_cast<PellatioDefinitions::Color> (m_info->currentPlayer())];
    GameInterface::select(idx);
}

void DualGameInterface::rotateSelected(PellatioDefinitions::Rotation rot)
{
    m_thisPlayer = m_player[static_cast<PellatioDefinitions::Color> (m_info->currentPlayer())];
    GameInterface::rotateSelected(rot);
}

PellatioDefinitions::Color DualGameInterface::thisPlayer()
{
    return PellatioDefinitions::Black;
}

void DualGameInterface::animateMove(MoveData move)
{
    if (m_anim) {
        GameInterface::animateMove(move);
    }
    m_anim = !m_anim;
}
