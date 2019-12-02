#ifndef COINMODEL_H
#define COINMODEL_H

#include <QAbstractTableModel>
#include <QMap>
#include "CoinInfo.h"

namespace Gazua {
    class CoinModel;
};

class CoinModel : public QAbstractTableModel {
    Q_OBJECT

private:
    QMap<std::time_t, QMap<std::string, Gazua::CoinInfo>>* coinInfosMap;

public:
    enum MapRoles {
        KeyRole = Qt::UserRole + 1,
        ValueRole
    };

    explicit CoinModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    void append(QPair<std::time_t, QMap<std::string, Gazua::CoinInfo>>* newCoinInfo);
    void remove(qint64 index);
    void setMap(QMap<std::time_t, QMap<std::string, Gazua::CoinInfo>>* coinInfosMap) { this->coinInfosMap = coinInfosMap; }
};

#endif
