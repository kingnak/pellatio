#ifndef OPTIONMODEL_H
#define OPTIONMODEL_H

#include <QObject>

class GameInterface;

class OptionModel : public QObject
{
    Q_OBJECT
public:
    explicit OptionModel(GameInterface *ctrl, QObject *parent = 0);

public slots:
    void offerRemis();
    void giveUp();

    void confirmOfferRemis();
    void dontOfferRemis() {}

    void confirmGiveUp();
    void dontGiveUp() {}

    void remisAccepted();
    void remisDeclined();

    void remisOffered();

    void acceptRemis();
    void declineRemis();

private:
    GameInterface *m_inter;
};

#endif // OPTIONMODEL_H
