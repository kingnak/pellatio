#ifndef BOARDDATA_H
#define BOARDDATA_H

#include "piecedata.h"
#include "fielddata.h"

class PELLATIO_COMMONSHARED_EXPORT BoardData
{
public:
    BoardData();

    QList<PieceData> pieces() const { return m_pieces; }
    void setPieces(const QList<PieceData> &pieces) { m_pieces = pieces; }

    static int xForIndex(PellatioDefinitions::FieldIndex idx);
    static int yForIndex(PellatioDefinitions::FieldIndex idx);
    static PellatioDefinitions::FieldIndex indexForXandY(int x, int y);
    static bool validXandY(int x, int y);

    static QString fieldName(PellatioDefinitions::FieldIndex idx);

protected:
    QList<PieceData> m_pieces;

    DECLARE_SERIALIZABLE_EXPORT(PELLATIO_COMMONSHARED_EXPORT, BoardData);
};

#endif // BOARDDATA_H
