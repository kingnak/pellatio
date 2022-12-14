#ifndef MOVEDATA_H
#define MOVEDATA_H

#include "pellatiodefinitions.h"
#include <QList>

class PieceData;

class PELLATIO_COMMONSHARED_EXPORT MoveData
{
public:
    MoveData();

    struct PELLATIO_COMMONSHARED_EXPORT MoveStep {
        MoveStep() : type(None) {}

        enum Type {
            None, Move, Rotate, MoveCapture, MoveSelfCapture, FlankedCapture
        } type;
        PellatioDefinitions::FieldIndex field;

        QString activePieceId;
        QString passivePieceId;

        PellatioDefinitions::Rotation rotation;
        PellatioDefinitions::Direction direction;
        int moveLength;
        PellatioDefinitions::FieldIndex moveField;

        static MoveStep rotate(const PieceData &d, PellatioDefinitions::Rotation dir);
        static MoveStep move(const PieceData &d, PellatioDefinitions::Direction dir, int len, PellatioDefinitions::FieldIndex dest);
        static MoveStep flank(const PieceData &act, const PieceData &pass, PellatioDefinitions::Direction dir);

    };

    QList<MoveStep> steps() const { return m_steps; }
    void addStep(MoveStep s) { m_steps.append(s); }
    void clear() { m_steps.clear(); }

    quint8 getMoveLength() const;

protected:
    QList<MoveStep> m_steps;

    DECLARE_SERIALIZABLE_EXPORT(PELLATIO_COMMONSHARED_EXPORT, MoveData);
    DECLARE_SERIALIZABLE_EXPORT(PELLATIO_COMMONSHARED_EXPORT, MoveData::MoveStep);
};

DECLARE_ENUM_SERIALIZER_EXPORT(PELLATIO_COMMONSHARED_EXPORT, MoveData::MoveStep::Type);

//Q_DECLARE_METATYPE(MoveData::MoveStep::Type)

#endif // MOVEDATA_H
