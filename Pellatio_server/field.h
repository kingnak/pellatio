#ifndef FIELD_H
#define FIELD_H

#include <data/fielddata.h>

class Piece;

class Field : public FieldData
{
public:
    Field(PellatioDefinitions::FieldIndex idx = -1);

    QString pieceId() const { return m_piece; }
    bool placePiece(const Piece &piece);
    void unplacePiece() { m_piece = QString::null; }

    bool hasPiece() const { return !m_piece.isNull(); }

    PellatioDefinitions::Direction moveDirection() const;
    void setMoveDirection(const PellatioDefinitions::Direction &moveDirection);

    int moveLength() const;
    void setMoveLength(int moveLength);

private:
    QString m_piece;
    PellatioDefinitions::Direction m_moveDirection;
    int m_moveLength;
};

#endif // FIELD_H
