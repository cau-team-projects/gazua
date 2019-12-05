#ifndef COININFOMODEL_H
#define COININFOMODEL_H

#include <QAbstractTableModel>
#include <QString>
#include <QMap>
#include <QTimer>
#include "CoinInfo.h"

namespace Gazua {
    class CoinInfoModel;
};

class CoinInfoModel : public QAbstractTableModel {
    Q_OBJECT

private:
    QVariantMap *coinInfoModel;

public:
    enum MapRoles {
        KeyRole = Qt::UserRole + 1,
        ValueRole
    };

    explicit CoinInfoModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    int count() const;

public slots:
    void append(QString newCoinName, QVariantMap newCoinFields);
    void remove(QString index);
    void setMap(QVariantMap *coinInfoModel) { this->coinInfoModel = coinInfoModel; }
    QHash<int, QByteArray> roleNames() const;
signals:
    void countChanged(int count);

};

#endif
