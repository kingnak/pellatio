#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include <QObject>
#include <pellatiodefinitions.h>
#include <QList>
#include <data/fielddata.h>
#include <data/piecedata.h>
#include <data/movedata.h>

class FieldModel;
class PieceModel;
class RotationModel;
class ConfirmModel;
class InfoModel;
class PreviewModel;
class AnimationModel;
class PlayerProxy;
class MessageModel;

class GameInterface : public QObject
{
    Q_OBJECT
public:
    explicit GameInterface(PlayerProxy *thisPlayer, QObject *parent = 0);

    virtual void setMessageModel(MessageModel *msg);

    virtual void confirmMove();
    virtual void resetMove();
    virtual void select(PellatioDefinitions::FieldIndex idx);
    virtual void rotateSelected(PellatioDefinitions::Rotation rot);

    virtual PellatioDefinitions::Color thisPlayer();

    virtual void thisPlayerChanged();

    FieldModel *fieldModel() { return m_fields; }
    PieceModel * pieceModel() { return m_pieces; }
    RotationModel *rotationModel() { return m_rotation; }
    ConfirmModel *confirmModel() { return m_confim; }
    InfoModel *infoModel() { return m_info; }
    PreviewModel *previewModel() { return m_preview; }
    AnimationModel *animationModel() { return m_anim; }
    //MessageModel *messageModel() { return m_msg; }

    virtual void animateMove(MoveData move);
    virtual void notifyWinner(PellatioDefinitions::Color winner);

protected:
    FieldModel *m_fields;
    PieceModel * m_pieces;
    RotationModel *m_rotation;
    ConfirmModel *m_confim;
    InfoModel *m_info;
    PreviewModel *m_preview;
    AnimationModel *m_anim;
    MessageModel *m_msg;

    PlayerProxy *m_thisPlayer;
};

#endif // GAMEINTERFACE_H
