#ifndef BOARD_H
#define BOARD_H

#include <data/boarddata.h>
#include <piece.h>
#include <field.h>
#include <QList>

class Board
{
public:
    Board();

    void initializeEmptyBoard();
    void initializeStartBoard();

    BoardData toData() const;
    QList<FieldData> getFieldData() const;

    Piece getPiece(QString id) const;

    void updatePiece(Piece p);

    const Field *field(int idx) const;

    void resetFieldStates();

    QList<Field> &fields() { return m_fields; }
    QList<Piece> pieces() { return m_pieces.values(); }

private:
    void placePiece(Piece *p, Field *f);

private:
    QMap<QString, Piece> m_pieces;
    QList<Field> m_fields;
};

#endif // BOARD_H
