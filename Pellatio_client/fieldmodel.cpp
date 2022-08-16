#include "fieldmodel.h"
#include "gameinterface.h"

FieldModel::FieldModel(GameInterface *ctrl, QObject *parent)
:   QAbstractListModel(parent),
    m_ctrl(ctrl)
{
}

int FieldModel::rowCount(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return m_fields.size();
}

QVariant FieldModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
    switch (role) {
    case movableRole: return m_fields[index.row()].isMovable();
    case selectableRole: return m_fields[index.row()].isSelectable();
    case selectedRole: return m_fields[index.row()].isSelected();
    case paradeRole: return m_fields[index.row()].isParade();
    case stateStringRole: return stateStringFromFlags(m_fields[index.row()]);
    }
    return QVariant();
}

void FieldModel::updateData(QList<FieldData> fields)
{
    beginResetModel();
    /*
    bool updating = false;
    if (m_fields.size() != fields.size()) {
        updating = true;
        if (m_fields.size() > 0) {
            beginRemoveRows(QModelIndex(), 0, m_fields.size());
            m_fields.clear();
            endRemoveRows();
        }

        beginInsertRows(QModelIndex(), 0, fields.size());
        m_fields.reserve(fields.size());
    }

    m_fields = fields;
    if (updating) {
        endInsertRows();
    } else {
        emit dataChanged(index(0), index(m_fields.size()));
    }
    */
    m_fields = fields;
    endResetModel();
}

QHash<int, QByteArray> FieldModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[movableRole] = "isMovableTo";
    roles[selectableRole] = "isSelectable";
    roles[selectedRole] = "isSelected";
    roles[paradeRole] = "isParade";
    roles[stateStringRole] = "stateStringFromFlags";
    return roles;
}

void FieldModel::select(int idx)
{
    m_ctrl->select(idx);
}

QString FieldModel::stateStringFromFlags(FieldData f)
{
    if (f.isMovable()) {
        if (f.isParade()) {
            return "paradeMovable";
        }
        return "movable";
    }
    if (f.isParade()) {
        return "parade";
    }
    if (f.isSelected()) {
        return "selected";
    }
    if (f.isSelectable()) {
        return "selectable";
    }
    return "normal";
}

/*
void FieldModel::updateData(FieldData data)
{
    //FieldData old = m_data;
    m_data = data;
    // Most certainly...
    stateStringFromFlagsChanged();
}

void FieldModel::select()
{
    m_ctrl->select(index());
}
*/

