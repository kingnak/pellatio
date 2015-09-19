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
    void endRemis();
    void terminate();
    void generalMessage(QString msg);

    void confirm(QString msg, QString btn, QObject *recevier = NULL, const char *act = NULL);

    void ask(QString msg, QString op1, QString op2, QObject *receiver, const char *act1, const char *act2);

signals:
    void won();
    void lost();
    void remis();
    void terminated();
    void message(QString msg);

    void dialog(QString msg, QString btn);
    void question(QString msg, QString op1, QString op2);

    void show();
    void hide();

public slots:
    void chooseOption1();
    void chooseOption2();
    void confirmDialog();

private:
    QByteArray m_func1;
    QByteArray m_func2;
    QObject *m_recv;

};

#endif // MESSAGEMODEL_H
