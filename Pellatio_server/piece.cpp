#include "piece.h"
#include <data/boarddata.h>

Piece::Piece(QString id, PellatioDefinitions::Color color, PellatioDefinitions::PieceType type, PellatioDefinitions::Direction dir, PellatioDefinitions::FieldIndex idx)
    : PieceData(id, color, type, dir, idx)
{
}

QList<PellatioDefinitions::MoveOffset> Piece::getMovableFields() const
{
    switch (m_type) {
    case PellatioDefinitions::Aggressor:
        return QList<PellatioDefinitions::MoveOffset>()
                << PellatioDefinitions::MoveOffset::fromDirection(PellatioDefinitions::North)
                << PellatioDefinitions::MoveOffset::fromDirection(PellatioDefinitions::NorthEast)
                << PellatioDefinitions::MoveOffset::fromDirection(PellatioDefinitions::NorthWest)
                << PellatioDefinitions::MoveOffset::fromDirection(PellatioDefinitions::West)
                << PellatioDefinitions::MoveOffset::fromDirection(PellatioDefinitions::East)
                << PellatioDefinitions::MoveOffset::fromDirection(PellatioDefinitions::South)
                << PellatioDefinitions::MoveOffset::fromDirection(PellatioDefinitions::SouthEast)
                << PellatioDefinitions::MoveOffset::fromDirection(PellatioDefinitions::SouthWest);

    case PellatioDefinitions::Phalangit:
        return QList<PellatioDefinitions::MoveOffset>()
                << PellatioDefinitions::MoveOffset::fromDirection(m_direction);

    case PellatioDefinitions::Kavalerist:
    case PellatioDefinitions::General:
        return QList<PellatioDefinitions::MoveOffset>()
                << PellatioDefinitions::MoveOffset::fromDirection(m_direction, 2)
                << PellatioDefinitions::MoveOffset::fromDirection(PellatioDefinitions::rotated(m_direction, PellatioDefinitions::ClockWise, 3), 2)
                << PellatioDefinitions::MoveOffset::fromDirection(PellatioDefinitions::rotated(m_direction, PellatioDefinitions::CounterClockWise, 3), 2);
    }

    Q_ASSERT(false);
    return QList<PellatioDefinitions::MoveOffset>();
}

PellatioDefinitions::Rotation Piece::getRotationModes() const
{
    if (m_type == PellatioDefinitions::Aggressor) return PellatioDefinitions::None;
    return PellatioDefinitions::Both;
}

QList<PellatioDefinitions::MoveOffset> Piece::getParadeFields() const
{
    if (m_type == PellatioDefinitions::Aggressor) return QList<PellatioDefinitions::MoveOffset>();

    return QList<PellatioDefinitions::MoveOffset>()
            << PellatioDefinitions::MoveOffset::fromDirection(m_direction)
            << PellatioDefinitions::MoveOffset::fromDirection(PellatioDefinitions::rotated(m_direction, PellatioDefinitions::ClockWise))
            << PellatioDefinitions::MoveOffset::fromDirection(PellatioDefinitions::rotated(m_direction, PellatioDefinitions::CounterClockWise));
}

int Piece::moveCount() const
{
    if (m_type == PellatioDefinitions::Kavalerist || m_type == PellatioDefinitions::General) {
        return 2;
    }
    return 1;
}

bool Piece::generateId()
{
    if (!m_id.isEmpty()) {
        return false;
    }
    QString c = QChar(color() == PellatioDefinitions::Red ? 'r' : 'b');
    QString t;
    switch (type()) {
    case PellatioDefinitions::Aggressor: t = 'A'; break;
    case PellatioDefinitions::Phalangit: t = 'P'; break;
    case PellatioDefinitions::Kavalerist: t = 'K'; break;
    case PellatioDefinitions::General: t = 'G'; break;
    default: t = '?';
    }
    QString s = BoardData::fieldName(field());

    m_id = QString("%1%2-%3").arg(c,t,s);
    return true;
}
