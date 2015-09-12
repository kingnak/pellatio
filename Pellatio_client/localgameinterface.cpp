#include "localgameinterface.h"
#include "infomodel.h"
#include "localplayer.h"
#include "confirmmodel.h"

LocalGameInterface::LocalGameInterface(QObject *parent)
    : GameInterface(parent), m_anim(false)
{
}

void LocalGameInterface::addLocalPlayer(LocalPlayer *p)
{
    m_player[p->thisPlayer()] = p;
}

void LocalGameInterface::confirmMove()
{
    PellatioDefinitions::Color c = static_cast<PellatioDefinitions::Color> (m_info->currentPlayer());
    if (m_player.contains(c)) {
        m_player[c]->confirmMove();
    }
}

void LocalGameInterface::resetMove()
{
    PellatioDefinitions::Color c = static_cast<PellatioDefinitions::Color> (m_info->currentPlayer());
    if (m_player.contains(c)) {
        m_player[c]->resetMove();
    }
}

void LocalGameInterface::select(PellatioDefinitions::FieldIndex idx)
{
    PellatioDefinitions::Color c = static_cast<PellatioDefinitions::Color> (m_info->currentPlayer());
    if (m_player.contains(c)) {
        m_player[c]->selectField(idx, m_confim->autoConfirm());
    }
}

void LocalGameInterface::rotateSelected(PellatioDefinitions::Rotation rot)
{
    PellatioDefinitions::Color c = static_cast<PellatioDefinitions::Color> (m_info->currentPlayer());
    if (m_player.contains(c)) {
        m_player[c]->rotateSelected(rot, m_confim->autoConfirm());
    }
}

PellatioDefinitions::Color LocalGameInterface::thisPlayer()
{
    if (m_player.size() != 1)
        return PellatioDefinitions::Black;
    return m_player.begin().key();
}

void LocalGameInterface::animateMove(MoveData move)
{
    if (m_player.size() == 1) {
        GameInterface::animateMove(move);
    } else if (m_anim) {
        GameInterface::animateMove(move);
    }
    m_anim = !m_anim;
}
