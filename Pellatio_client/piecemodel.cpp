#include "piecemodel.h"

PieceModel::PieceModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

int PieceModel::rowCount(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return m_data.size();
}

QVariant PieceModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
    switch (role) {
    case typeRole: return m_data[index.row()].type();
    case colorRole: return m_data[index.row()].color();
    case directionRole: return m_data[index.row()].direction();
    case fieldRole: return m_data[index.row()].field();
    case captureRole: return m_data[index.row()].isCaptured();
    }
    return QVariant();
}

void PieceModel::updateSinglePieceField(QString id, PellatioDefinitions::FieldIndex field)
{
    int idx = findPiece(id);
    if (idx < 0) return;
    m_data[idx].setField(field);
    emit dataChanged(index(idx), index(idx));
}

void PieceModel::updateSinglePieceDirection(QString id, PellatioDefinitions::Direction dir)
{
    int idx = findPiece(id);
    if (idx < 0) return;
    m_data[idx].setDirection(dir);
    emit dataChanged(index(idx), index(idx));
}

void PieceModel::updateSinglePieceDirection(QString id, PellatioDefinitions::Rotation dir)
{
    int idx = findPiece(id);
    if (idx < 0) return;
    m_data[idx].setDirection(PellatioDefinitions::rotated(m_data[idx].direction(), dir));
    emit dataChanged(index(idx), index(idx));
}

void PieceModel::updateSinglePieceCapture(QString id, bool captured)
{
    int idx = findPiece(id);
    if (idx < 0) return;
    m_data[idx].setCaptured(captured);
    emit dataChanged(index(idx), index(idx));
}

void PieceModel::updateData(QList<PieceData> data)
{
    beginResetModel();
    m_data.clear();
    foreach (PieceData p, data) {
        m_data << p;
    }

    //m_data = data;
    endResetModel();
}

QHash<int, QByteArray> PieceModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[typeRole] = "type";
    roles[colorRole] = "pieceColor";
    roles[directionRole] = "direction";
    roles[fieldRole] = "field";
    roles[captureRole] = "isCaptured";
    return roles;
}

int PieceModel::findPiece(QString id)
{
    for (int i = 0; i < m_data.size(); ++i) {
        if (m_data[i].id() == id) return i;
    }
    return -1;
}
