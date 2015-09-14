#ifndef FLANKMODEL_H
#define FLANKMODEL_H

#include <QAbstractListModel>
#include <data/movedata.h>

class FlankModel : public QAbstractListModel
{
    Q_OBJECT

    enum {
        fieldRole = Qt::UserRole + 1,
        directionRole
    };
public:
    explicit FlankModel(QObject *parent = 0);

    int rowCount(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role) const;

    void updateData(QList<MoveData::MoveStep> flanks);

signals:

public slots:

private:
    QList<MoveData::MoveStep> m_data;
};

#endif // FLANKMODEL_H
