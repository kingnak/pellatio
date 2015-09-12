#ifndef PELLATIOQMLDEFINITIONS_H
#define PELLATIOQMLDEFINITIONS_H

#include <QObject>
#include <pellatiodefinitions.h>
#include <data/movedata.h>

class PellatioQMLDefinitions : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int boardSize READ boardSize NOTIFY boardSizeChanged_Dummy)
public:
    explicit PellatioQMLDefinitions(QObject *parent = 0) : QObject(parent) {}
    int boardSize() const { return PellatioDefinitions::BOARD_SIZE; }
signals:
    void boardSizeChanged_Dummy();
};

class PieceTypeType : public QObject
{
    Q_OBJECT
    Q_ENUMS(PieceType)
public:
    explicit PieceTypeType(QObject *parent = 0) : QObject(parent) {}

    enum PieceType {
        Aggressor = PellatioDefinitions::Aggressor,
        Phalangit = PellatioDefinitions::Phalangit,
        Kavalerist = PellatioDefinitions::Kavalerist,
        General = PellatioDefinitions::General
    };
};

class ColorType : public QObject
{
    Q_OBJECT
    Q_ENUMS(Color)
    Q_PROPERTY(Color color READ color)
public:
    explicit ColorType(QObject *parent = 0) : QObject(parent) {}

    enum Color {
        Red = PellatioDefinitions::Red,
        Black = PellatioDefinitions::Black
    };

    Color color() const { return m_color; }
private:
    Color m_color;
};

class RotationType : public QObject
{
    Q_OBJECT
    Q_ENUMS(Rotation)
    Q_PROPERTY(Rotation rotation READ rotation)
public:
    enum Rotation {
        None = PellatioDefinitions::None,
        ClockWise = PellatioDefinitions::ClockWise,
        CounterClockWise = PellatioDefinitions::CounterClockWise,
        Both = PellatioDefinitions::Both
    };

    Rotation rotation() const { return m_rot; }
private:
    Rotation m_rot;
};

class MoveType :  public QObject
{
    Q_OBJECT
    Q_ENUMS(Type)
    Q_PROPERTY(Type type READ type)
public:
    explicit MoveType(QObject *parent = 0) : QObject(parent) {}

    enum Type {
        Move = MoveData::MoveStep::Move,
        Rotate = MoveData::MoveStep::Rotate
    };

    Type type() const { return m_type; }
private:
    Type m_type;
};

#endif // PELLATIOQMLDEFINITIONS_H
