#include "piecedata.h"

PieceData::PieceData()
    : m_color(PellatioDefinitions::Black), m_type(PellatioDefinitions::Aggressor), m_direction(PellatioDefinitions::North), m_field(-1)
{
}

PieceData::PieceData(QString id, PellatioDefinitions::Color color, PellatioDefinitions::PieceType type, PellatioDefinitions::Direction dir, PellatioDefinitions::FieldIndex idx)
    : m_id(id), m_color(color), m_type(type), m_direction(dir), m_field(idx)
{

}

void operator << (QVariant &data, const PieceData &target)
{
    QVariantMap m;
    m["id"] << target.m_id;
    m["color"] << target.m_color;
    m["type"] << target.m_type;
    m["direction"] << target.m_direction;
    m["field"] << target.m_field;
    data << m;
}

void operator >> (const QVariant &data, PieceData &target)
{
    QVariantMap m;
    data >> m;
    m["id"] >> target.m_id;
    m["color"] >> target.m_color;
    m["type"] >> target.m_type;
    m["direction"] >> target.m_direction;
    m["field"] >> target.m_field;
}

