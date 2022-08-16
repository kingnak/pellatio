#ifndef PIECEMODEL_H
#define PIECEMODEL_H

#include <QAbstractListModel>
#include <pellatiodefinitions.h>
#include <data/piecedata.h>

class PieceModel : public QAbstractListModel
{
    Q_OBJECT
    enum {
        typeRole = Qt::UserRole + 1,
        colorRole,
        directionRole,
        fieldRole,
        captureRole
    };

public:

    explicit PieceModel(QObject *parent = 0);

    int rowCount(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role) const;

    void updateSinglePieceField(QString id, PellatioDefinitions::FieldIndex field);
    void updateSinglePieceDirection(QString id, PellatioDefinitions::Direction dir);
    void updateSinglePieceDirection(QString id, PellatioDefinitions::Rotation dir);
    void updateSinglePieceCapture(QString id, bool captured);

    void updateData(QList<PieceData> data);

    struct CapturePieceData : PieceData {
        CapturePieceData(PieceData p) : PieceData(p), m_isCaptured(false) {}
        bool isCaptured() const { return m_isCaptured; }
        void setCaptured(bool captured) { m_isCaptured = captured; }
    private:
        bool m_isCaptured;
    };

    QHash<int, QByteArray> roleNames() const;

private:
    int findPiece(QString id);

private:
    QList<CapturePieceData> m_data;
};

#endif // PIECEMODEL_H
