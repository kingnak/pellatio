#include "movedata.h"
#include "piecedata.h"

MoveData::MoveData()
{
}

quint8 MoveData::getMoveLength() const
{
    quint8 ct = 0;
    foreach (MoveStep s, m_steps) {
        if (s.type == MoveData::MoveStep::Rotate) ct++;
        if (s.type == MoveData::MoveStep::Move) ct += s.moveLength;
    }
    return ct;
}


MoveData::MoveStep MoveData::MoveStep::rotate(const PieceData &d, PellatioDefinitions::Rotation dir)
{
    MoveStep ret;
    ret.type = Rotate;
    ret.activePieceId = d.id();
    ret.field = d.field();
    ret.rotation = dir;
    return ret;
}

MoveData::MoveStep MoveData::MoveStep::move(const PieceData &d, PellatioDefinitions::Direction dir, int len, PellatioDefinitions::FieldIndex dest)
{
    MoveStep ret;
    ret.type = Move;
    ret.activePieceId = d.id();
    ret.field = d.field();
    ret.direction = dir;
    ret.moveLength = len;
    ret.moveField = dest;
    return ret;
}

MoveData::MoveStep MoveData::MoveStep::flank(const PieceData &act, const PieceData &pass, PellatioDefinitions::Direction dir)
{
    MoveStep ret;
    ret.type = FlankedCapture;
    ret.activePieceId = act.id();
    ret.passivePieceId = pass.id();
    ret.field = pass.field();
    ret.direction = dir;
    return ret;
}
