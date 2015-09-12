#include "interactionoptionsdata.h"

InteractionOptionsData::InteractionOptionsData()
    : m_rotation(PellatioDefinitions::None), m_confirmMove(false), m_resetMove(false)
{
}

void operator << (QVariant &data, const InteractionOptionsData &target)
{
    QVariantMap m;
    m["rotation"] << target.m_rotation;
    m["confirmMove"] << target.m_confirmMove;
    m["resetMove"] << target.m_resetMove;
    m["fields"] << target.m_fields;
    data << m;
}

void operator >> (const QVariant &data, InteractionOptionsData &target)
{
    QVariantMap m;
    data >> m;
    m["rotation"] >> target.m_rotation;
    m["confirmMove"] >> target.m_confirmMove;
    m["resetMove"] >> target.m_resetMove;
    m["fields"] >> target.m_fields;
}
