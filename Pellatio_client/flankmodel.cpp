#include "flankmodel.h"

#include <data/piecedata.h>
#include <data/boarddata.h>


FlankModel::FlankModel(QObject *parent) :
    QAbstractListModel(parent)
{
    QHash<int, QByteArray> roles;
    roles[fieldRole] = "field";
    roles[directionRole] = "direction";
    setRoleNames(roles);

    /*
    PieceData a("A", PellatioDefinitions::Red, PellatioDefinitions::Aggressor, PellatioDefinitions::North, BoardData::indexForXandY(4,4));
    PieceData p("B", PellatioDefinitions::Red, PellatioDefinitions::Aggressor, PellatioDefinitions::North, BoardData::indexForXandY(4,3));
    m_data << MoveData::MoveStep::flank(a, p, PellatioDefinitions::SouthEast);
    */
}

int FlankModel::rowCount(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return m_data.size();
}

QVariant FlankModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
    switch (role) {
    case fieldRole: return m_data[index.row()].field;
    case directionRole: return m_data[index.row()].direction;
    }
    return QVariant();
}

void FlankModel::updateData(QList<MoveData::MoveStep> flanks)
{
    m_data = flanks;
    reset();
}

void FlankModel::clear()
{
    m_data.clear();
    reset();
}
