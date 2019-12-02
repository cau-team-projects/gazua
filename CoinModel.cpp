#include "API.h"
#include "CoinModel.h"

CoinModel::CoinModel(QObject *parent) : QAbstractTableModel(parent) {
    coinInfosMap = nullptr;
}

int CoinModel::rowCount(const QModelIndex& parent) const
{
    if (coinInfosMap) return coinInfosMap->count();
    else return 0;
}

int CoinModel::columnCount(const QModelIndex & parent) const {
    return 2;
}

QVariant CoinModel::data(const QModelIndex& index, int role) const
{
    if      (!coinInfosMap)                                                                      return QVariant();
    else if (index.row() < 0 || index.row() >= coinInfosMap->count() || role != Qt::DisplayRole) return QVariant();

    else if (index.column() == 0) return (QString)coinInfosMap->keys().at(index.row());
    else if (index.column() == 1) return &(coinInfosMap->values().at(index.row()));

    else return QVariant();
}

void CoinModel::timerHit() {
    QModelIndex topLeft = createIndex(0,0);
    emit dataChanged(topLeft, topLeft, {Qt::DisplayRole});
}

void CoinModel::append(QMap<QString, Gazua::CoinInfo> &newCoinInfo) {
    coinInfosMap->insert(QTime::currentTime().toString(), newCoinInfo);
    return;
}

void CoinModel::remove(QString index) {
    coinInfosMap->remove(index);
    return;
}
