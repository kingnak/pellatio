#ifndef PREVIEWMODEL_H
#define PREVIEWMODEL_H

#include <QAbstractListModel>
#include <data/movedata.h>

class PreviewModel : public QAbstractListModel
{
    Q_OBJECT
    enum {
        typeRole = Qt::UserRole + 1,
        fieldRole,
        directionRole,
        lengthRole,
        rotationRole,
    };
public:
    explicit PreviewModel(QObject *parent = 0);

    int rowCount(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role) const;

    void updateData(MoveData data);

    QHash<int, QByteArray> roleNames() const;

private:
    MoveData m_data;

};

#endif // PREVIEWMODEL_H
