#ifndef CONFIRMMODEL_H
#define CONFIRMMODEL_H

#include <QObject>
#include <data/interactionoptionsdata.h>

class GameInterface;

class ConfirmModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool canReset READ canReset NOTIFY canResetChanged)
    Q_PROPERTY(bool canConfirm READ canConfirm NOTIFY canConfirmChanged)
    Q_PROPERTY(bool autoConfirm READ autoConfirm WRITE setAutoConfirm NOTIFY autoConfirmChanged)

public:
    explicit ConfirmModel(GameInterface *ctrl, QObject *parent = 0);

    bool canReset() const { return m_data.canResetMove(); }
    bool canConfirm() const { return m_data.canConfirmMove(); }
    bool autoConfirm() const { return m_autoConfirm; }

    void setAutoConfirm(bool ac);

    void updateData(InteractionOptionsData data);

signals:
    void canResetChanged();
    void canConfirmChanged();
    void autoConfirmChanged();

public slots:
    void confirm();
    void reset();

private:
    GameInterface *m_ctrl;
    InteractionOptionsData m_data;
    bool m_autoConfirm;
};

#endif // CONFIRMMODEL_H
