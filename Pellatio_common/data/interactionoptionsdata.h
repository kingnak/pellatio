#ifndef INTERACTIONOPTIONSDATA_H
#define INTERACTIONOPTIONSDATA_H

#include "pellatiodefinitions.h"
#include "data/fielddata.h"

class PELLATIO_COMMONSHARED_EXPORT InteractionOptionsData
{
public:
    InteractionOptionsData();

    PellatioDefinitions::Rotation rotation() const { return m_rotation; }
    void setRotation(const PellatioDefinitions::Rotation &rotation) { m_rotation = rotation; }

    bool canConfirmMove() const { return m_confirmMove; }
    void setConfirmMove(bool confirmMove) { m_confirmMove = confirmMove; }

    bool canResetMove() const { return m_resetMove; }
    void setResetMove(bool resetMove) { m_resetMove = resetMove; }

    QList<FieldData> fields() const { return m_fields; }
    void setFields(const QList<FieldData> &fields) { m_fields = fields; }

protected:
    PellatioDefinitions::Rotation m_rotation;
    bool m_confirmMove;
    bool m_resetMove;
    QList<FieldData> m_fields;

    DECLARE_SERIALIZABLE_EXPORT(PELLATIO_COMMONSHARED_EXPORT, InteractionOptionsData);
};

#endif // INTERACTIONOPTIONSDATA_H
