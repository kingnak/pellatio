#ifndef PIECEDATA_H
#define PIECEDATA_H

#include "pellatio_common_global.h"
#include "pellatiodefinitions.h"
#include "serializer.hpp"

class PELLATIO_COMMONSHARED_EXPORT PieceData
{
public:
    PieceData();
    PieceData(QString id, PellatioDefinitions::Color color, PellatioDefinitions::PieceType type, PellatioDefinitions::Direction dir = PellatioDefinitions::North, PellatioDefinitions::FieldIndex idx = -1);

    QString id() const { return m_id; }
    void setId(const QString &id) { m_id = id; }

    PellatioDefinitions::Color color() const { return m_color; }
    void setColor(const PellatioDefinitions::Color &color) { m_color = color; }

    PellatioDefinitions::PieceType type() const { return m_type; }
    void setType(const PellatioDefinitions::PieceType &type) { m_type = type; }

    PellatioDefinitions::Direction direction() const { return m_direction; }
    void setDirection(const PellatioDefinitions::Direction &direction) { m_direction = direction; }

    PellatioDefinitions::FieldIndex field() const { return m_field; }
    void setField(const PellatioDefinitions::FieldIndex &field) { m_field = field; }

protected:
    QString m_id;
    PellatioDefinitions::Color m_color;
    PellatioDefinitions::PieceType m_type;
    PellatioDefinitions::Direction m_direction;
    PellatioDefinitions::FieldIndex m_field;

    DECLARE_SERIALIZABLE_EXPORT(PELLATIO_COMMONSHARED_EXPORT, PieceData);
};

#endif // PIECEDATA_H
