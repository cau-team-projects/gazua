#ifndef COINMODEL_H
#define COINMODEL_H

#include <QAbstractTableModel>
#include <QString>
#include <QMap>
#include <QTimer>
#include "CoinInfo.h"

namespace Gazua {
    class CoinModel;
};

class CoinModel : public QAbstractTableModel {
    Q_OBJECT

private:
    QMap<QString, QMap<QString, Gazua::CoinInfo>>* coinInfosMap;

public:
    enum MapRoles {
        KeyRole = Qt::UserRole + 1,
        ValueRole
    };

    explicit CoinModel(QObject *parent = nullptr, QTimer timer);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    void timerHit();
    void append(QMap<QString, Gazua::CoinInfo> &newCoinInfo);
    void remove(QString index);
    void setMap(QMap<QString, QMap<QString, Gazua::CoinInfo>>* coinInfosMap) { this->coinInfosMap = coinInfosMap; }
};

#endif
