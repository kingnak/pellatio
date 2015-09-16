#ifndef PELLATIODEFINITIONS_H
#define PELLATIODEFINITIONS_H

#include "pellatio_common_global.h"
#include "serializer.hpp"

class PELLATIO_COMMONSHARED_EXPORT PellatioDefinitions
{
public:
    static const int BOARD_SIZE = 9;
    //static const int ANIMATION_LENGTH = 500;

    typedef qint8 FieldIndex;

    enum PieceType {
        Aggressor,
        Phalangit,
        Kavalerist,
        General
    };

    enum Color {
        Red,
        Black
    };

    static PellatioDefinitions::Color opponent(PellatioDefinitions::Color clr);

    enum Rotation {
        None = 0,
        ClockWise = 1,
        CounterClockWise = 2,
        Both = ClockWise | CounterClockWise
    };

    enum Direction {
        North, NorthEast, East,
        SouthEast, South, SouthWest,
        West, NorthWest
    };

    enum GameState {
        NotStarted,
        Running,
        Terminated,
        Winner,
        Remis
    };

    static Direction rotated(Direction d, Rotation r, quint8 count = 1);
    static Direction reversed(Direction d);

    struct PELLATIO_COMMONSHARED_EXPORT MoveOffset {
        int dx, dy, len; Direction dir;
        MoveOffset() : dx(0), dy(0), len(0), dir(North) {}
        static MoveOffset fromDirection(Direction d, int len = 1);
        Direction toDirection() const;
    private:
        MoveOffset(int dx, int dy, Direction dir, int len = 1) : dx(dx), dy(dy), len(len), dir(dir) {}
    };

private:
    PellatioDefinitions() {}
};

DECLARE_ENUM_SERIALIZER_EXPORT(PELLATIO_COMMONSHARED_EXPORT, PellatioDefinitions::PieceType);
DECLARE_ENUM_SERIALIZER_EXPORT(PELLATIO_COMMONSHARED_EXPORT, PellatioDefinitions::Color);
DECLARE_ENUM_SERIALIZER_EXPORT(PELLATIO_COMMONSHARED_EXPORT, PellatioDefinitions::Rotation);
DECLARE_ENUM_SERIALIZER_EXPORT(PELLATIO_COMMONSHARED_EXPORT, PellatioDefinitions::Direction);
DECLARE_ENUM_SERIALIZER_EXPORT(PELLATIO_COMMONSHARED_EXPORT, PellatioDefinitions::GameState);

Q_DECLARE_METATYPE(PellatioDefinitions::FieldIndex)
Q_DECLARE_METATYPE(PellatioDefinitions::PieceType)
Q_DECLARE_METATYPE(PellatioDefinitions::Color)
Q_DECLARE_METATYPE(PellatioDefinitions::Rotation)
Q_DECLARE_METATYPE(PellatioDefinitions::Direction)
Q_DECLARE_METATYPE(PellatioDefinitions::GameState)

#endif // PELLATIODEFINITIONS_H
