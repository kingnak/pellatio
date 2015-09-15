#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include <QObject>

class MessageModel : public QObject
{
    Q_OBJECT
public:
    explicit MessageModel(QObject *parent = 0);

    void win();
    void lose();
    void terminate();
    void generalMessage(QString msg);

signals:
    void won();
    void lost();
    void terminated();
    void message(QString msg);

public slots:

};

#endif // MESSAGEMODEL_H
