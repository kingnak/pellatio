#ifndef PIECE_H
#define PIECE_H

#include <data/piecedata.h>

class Piece : public PieceData
{
public:
    Piece() : PieceData() {}
    Piece(QString id, PellatioDefinitions::Color color, PellatioDefinitions::PieceType type, PellatioDefinitions::Direction dir = PellatioDefinitions::North, PellatioDefinitions::FieldIndex idx = -1);

    QList<PellatioDefinitions::MoveOffset> getMovableFields() const;
    PellatioDefinitions::Rotation getRotationModes() const;
    QList<PellatioDefinitions::MoveOffset> getParadeFields() const;

    int moveCount() const;

    bool isValid() const { return !m_id.isNull(); }
    bool onField() const { return m_field >= 0; }

    bool generateId();
};

#endif // PIECE_H
