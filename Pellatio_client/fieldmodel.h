#ifndef FIELDMODEL_H
#define FIELDMODEL_H

#include <QObject>
#include <data/fielddata.h>
#include <QAbstractListModel>

class GameInterface;

class FieldModel : public QAbstractListModel
{
    Q_OBJECT
    enum {
        movableRole = Qt::UserRole + 1,
        selectableRole,
        selectedRole,
        paradeRole,
        stateStringRole
    };

public:
    explicit FieldModel(GameInterface *ctrl, QObject *parent = NULL);

    int rowCount(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role) const;

    void updateData(QList<FieldData> fields);

    QHash<int, QByteArray> roleNames() const;

public slots:
    void select(int idx);

private:
    static QString stateStringFromFlags(FieldData f);

    GameInterface *m_ctrl;
    QList<FieldData> m_fields;
};

/*
class FieldModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int index READ index)
    Q_PROPERTY(bool isMovableTo READ isMovableTo)// NOTIFY movableToChanged)
    Q_PROPERTY(bool isSelectable READ isSelectable)// NOTIFY selectableChanged)
    Q_PROPERTY(bool isSelected READ isSelected)// NOTIFY selectedChanged)
    Q_PROPERTY(bool isParade READ isParade)// NOTIFY paradeChanged)
    Q_PROPERTY(QString stateStringFromFlags READ stateStringFromFlags NOTIFY stateStringFromFlagsChanged)
public:
    explicit FieldModel(GameInterface *ctrl, QObject *parent = 0);

    int index() const { return m_data.index(); }

    bool isMovableTo() const { return m_data.isMovable(); }
    bool isSelectable() const { return m_data.isSelectable(); }
    bool isSelected() const { return m_data.isSelected(); }
    bool isParade() const { return m_data.isParade(); }

    QString stateStringFromFlags() const;

    void updateData(FieldData data);

signals:
    void stateStringFromFlagsChanged();

public slots:
    void select();

private:
    GameInterface *m_ctrl;
    FieldData m_data;
};
*/

#endif // FIELDMODEL_H
