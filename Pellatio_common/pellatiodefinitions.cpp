#include "pellatiodefinitions.h"


PellatioDefinitions::Color PellatioDefinitions::opponent(PellatioDefinitions::Color clr)
{
    if (clr == PellatioDefinitions::Black) {
        return PellatioDefinitions::Red;
    } else {
        return PellatioDefinitions::Black;
    }
}

PellatioDefinitions::Direction PellatioDefinitions::rotated(PellatioDefinitions::Direction d, PellatioDefinitions::Rotation r, quint8 count)
{
    count %= 8;
    const int f = ((r == ClockWise) ? 1 : ((r == CounterClockWise) ? -1 : 0));
    int ret = (d + f * count);
    while (ret < 0) ret += 8;
    return static_cast<Direction> (ret % 8);
}

PellatioDefinitions::Direction PellatioDefinitions::reversed(PellatioDefinitions::Direction d)
{
    return rotated(d, PellatioDefinitions::ClockWise, 4);
}



PellatioDefinitions::MoveOffset PellatioDefinitions::MoveOffset::fromDirection(PellatioDefinitions::Direction d, int len)
{
    MoveOffset ret;
    ret.len = len;
    ret.dir = d;
    switch (d) {
    case North:      ret.dy = -1; break;
    case NorthEast:  ret.dx = +1; ret.dy = -1; break;
    case East:       ret.dx = +1; break;
    case SouthEast:  ret.dx = +1; ret.dy = +1; break;
    case South:      ret.dy = +1; break;
    case SouthWest:  ret.dx = -1; ret.dy = +1; break;
    case West:       ret.dx = -1; break;
    case NorthWest:  ret.dx = -1; ret.dy = -1; break;
    }
    return ret;
}

PellatioDefinitions::Direction PellatioDefinitions::MoveOffset::toDirection() const
{
    Q_ASSERT(-1 <= dx && dx <= 1 && -1 <= dy && dy <= 1);

    if (dx + dy == -2) {
        return NorthWest;
    }
    if (dx + dy == 2) {
        return SouthEast;
    }
    if (dx + dy == 1) {
        if (dx == 0)
            return South;
        else
            return East;
    }
    if (dx + dy == -1) {
        if (dx == 0)
            return North;
        else
            return West;
    }
    if (dx == 1)
        return NorthEast;
    return SouthWest;
}

DEFINE_ENUM_SERIALIZER(PellatioDefinitions::PieceType)
DEFINE_ENUM_SERIALIZER(PellatioDefinitions::Color)
DEFINE_ENUM_SERIALIZER(PellatioDefinitions::Direction)
DEFINE_ENUM_SERIALIZER(PellatioDefinitions::Rotation)
DEFINE_ENUM_SERIALIZER(PellatioDefinitions::GameState)
