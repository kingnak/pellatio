#include "optionmodel.h"
#include "gameinterface.h"
#include "messagemodel.h"

OptionModel::OptionModel(GameInterface *ctrl, QObject *parent) :
    QObject(parent), m_inter(ctrl)
{
}

void OptionModel::offerRemis()
{
    m_inter->messageModel()->ask("Really offer Remis?", "Yes", "No", this, "confirmOfferRemis", "dontOfferRemis");
}

void OptionModel::giveUp()
{
    m_inter->messageModel()->ask("Really offer Remis?", "Yes", "No", this, "confirmGiveUp", "dontGiveUp");
}

void OptionModel::confirmOfferRemis()
{
    m_inter->messageModel()->generalMessage("Waiting for response...");
    m_inter->offerRemis();
}

void OptionModel::confirmGiveUp()
{
    m_inter->giveUp();
}

void OptionModel::remisAccepted()
{
    m_inter->messageModel()->confirm("Opponent accepted Remis", "Ok");
}

void OptionModel::remisDeclined()
{
    m_inter->messageModel()->confirm("Opponent declined Remis", "Ok");
}

void OptionModel::remisOffered()
{
    m_inter->messageModel()->ask("Opponent offered Remis", "Accept", "Decline", this, "acceptRemis", "declineRemis");
}

void OptionModel::acceptRemis()
{
    m_inter->acceptRemis();
}

void OptionModel::declineRemis()
{
    m_inter->declineRemis();
}

