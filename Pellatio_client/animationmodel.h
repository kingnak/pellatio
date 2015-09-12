#ifndef ANIMATIONMODEL_H
#define ANIMATIONMODEL_H

#include <QObject>
#include <data/movedata.h>

class GameInterface;
class QEventLoop;

class AnimationModel : public QObject
{
    Q_OBJECT
public:
    explicit AnimationModel(GameInterface *inter, QObject *parent = 0);

    void animate(MoveData move);

signals:

public slots:
    void animationStarted();
    void animationFinished();

protected:
    void doAnimate();
protected slots:
    void doAnimateStep();

private:
    GameInterface *m_inter;
    QEventLoop *m_loop;

    QList<MoveData::MoveStep> m_anims;
    int m_animCt;
};

#endif // ANIMATIONMODEL_H
