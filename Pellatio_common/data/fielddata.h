#ifndef FIELDDATA_H
#define FIELDDATA_H

#include "pellatiodefinitions.h"

class PELLATIO_COMMONSHARED_EXPORT FieldData
{
public:
    FieldData(PellatioDefinitions::FieldIndex idx = -1);

    PellatioDefinitions::FieldIndex index() const { return m_idx; }
    void setIndex(const PellatioDefinitions::FieldIndex &idx) { m_idx = idx; }

    bool isSelected() const { return m_selected; }
    void setSelected(bool selected) { m_selected = selected; }

    bool isSelectable() const { return m_selectable; }
    void setSelectable(bool selectable) { m_selectable = selectable; }

    bool isParade() const { return m_parade; }
    void setParade(bool parade) { m_parade = parade; }

    bool isMovable() const { return m_movable; }
    void setMovable(bool movable) { m_movable = movable; }

protected:
    PellatioDefinitions::FieldIndex m_idx;
    bool m_selected;
    bool m_selectable;
    bool m_parade;
    bool m_movable;

    DECLARE_SERIALIZABLE_EXPORT(PELLATIO_COMMONSHARED_EXPORT, FieldData);
};

#endif // FIELDDATA_H
