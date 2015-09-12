#include "previewmodel.h"

PreviewModel::PreviewModel(QObject *parent) :
    QAbstractListModel(parent)
{
    QHash<int, QByteArray> roles;
    roles[typeRole] = "type";
    roles[fieldRole] = "field";
    roles[directionRole] = "direction";
    roles[lengthRole] = "length";
    roles[rotationRole] = "rotationDirection";
    setRoleNames(roles);
}

int PreviewModel::rowCount(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return m_data.steps().size();
}

QVariant PreviewModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
    MoveData::MoveStep step = m_data.steps()[index.row()];
    switch (role) {
    case typeRole: return step.type;
    case fieldRole: return step.field;
    case directionRole: return step.direction;
    case lengthRole: return step.moveLength;
    case rotationRole: return step.rotation;
    }
    return QVariant();
}

void PreviewModel::updateData(MoveData data)
{
    m_data = data;
    reset();
}
