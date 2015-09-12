#include "field.h"
#include "piece.h"

Field::Field(PellatioDefinitions::FieldIndex idx)
    : FieldData(idx), m_moveDirection(PellatioDefinitions::North), m_moveLength(0)
{
}

bool Field::placePiece(const Piece &piece)
{
    if (!hasPiece()) {
        m_piece = piece.id();
        return true;
    }
    return false;
}
PellatioDefinitions::Direction Field::moveDirection() const
{
    return m_moveDirection;
}

void Field::setMoveDirection(const PellatioDefinitions::Direction &moveDirection)
{
    m_moveDirection = moveDirection;
}
int Field::moveLength() const
{
    return m_moveLength;
}

void Field::setMoveLength(int moveLength)
{
    m_moveLength = moveLength;
}


