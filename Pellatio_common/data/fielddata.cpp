#include "fielddata.h"

FieldData::FieldData(PellatioDefinitions::FieldIndex idx)
    : m_idx(idx), m_selected(false), m_selectable(false), m_parade(false), m_movable(false)
{
}

void operator << (QVariant &data, const FieldData &target)
{
    QVariantMap m;
    m["index"] << target.m_idx;
    m["selected"] << target.m_selected;
    m["selectable"] << target.m_selectable;
    m["parade"] << target.m_parade;
    m["movable"] << target.m_movable;
    data << m;
}

void operator >> (const QVariant &data, FieldData &target)
{
    QVariantMap m;
    data >> m;
    m["index"] >> target.m_idx;
    m["selected"] >> target.m_selected;
    m["selectable"] >> target.m_selectable;
    m["parade"] >> target.m_parade;
    m["movable"] >> target.m_movable;
}
