#include "boarddata.h"

BoardData::BoardData()
{
}


int BoardData::xForIndex(PellatioDefinitions::FieldIndex idx)
{
    return idx % PellatioDefinitions::BOARD_SIZE;
}

int BoardData::yForIndex(PellatioDefinitions::FieldIndex idx)
{
    return idx / PellatioDefinitions::BOARD_SIZE;
}

PellatioDefinitions::FieldIndex BoardData::indexForXandY(int x, int y)
{
    return y*PellatioDefinitions::BOARD_SIZE + x;
}

bool BoardData::validXandY(int x, int y)
{
    return
            x >= 0 && x < PellatioDefinitions::BOARD_SIZE &&
            y >= 0 && y < PellatioDefinitions::BOARD_SIZE;
}

QString BoardData::fieldName(PellatioDefinitions::FieldIndex idx)
{
    int x = xForIndex(idx);
    int y = yForIndex(idx);
    return QString("%1%2").arg(QChar('A'+x)).arg(y+1);
}


void operator << (QVariant &data, const BoardData &target)
{
    QVariantMap m;
    m["pieces"] << target.m_pieces;
    data << m;
}

void operator >> (const QVariant &data, BoardData &target)
{
    QVariantMap m;
    data >> m;
    m["pieces"] >> target.m_pieces;
}
