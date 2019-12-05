#include "API.h"
#include "CoinInfoModel.h"

CoinInfoModel::CoinInfoModel(QObject *parent) : QAbstractTableModel(parent) {
    coinInfoModel = nullptr;
}

int CoinInfoModel::rowCount(const QModelIndex& parent) const {
    if (coinInfoModel) return coinInfoModel->count();
    else return 0;
}

int CoinInfoModel::columnCount(const QModelIndex & parent) const {
    return 2;
}

QVariant CoinInfoModel::data(const QModelIndex& index, int role) const {
    if      (!coinInfoModel)                                                                      return QVariant();
    else if (index.row() < 0 || index.row() >= coinInfoModel->count() || role != Qt::DisplayRole) return QVariant();

    else if (index.column() == 0) return coinInfoModel->keys().at(index.row());
    else if (index.column() == 1) return coinInfoModel->values().at(index.row());

    else return QVariant();
}

void CoinInfoModel::append(QString newCoinName, QVariantMap newCoinFields) {
    coinInfoModel->insert(newCoinName, newCoinFields);
    return;
}

void CoinInfoModel::remove(QString coinName) {
    coinInfoModel->remove(coinName);
    return;
}

QHash<int, QByteArray> CoinInfoModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[KeyRole] = "key";
    roles[ValueRole] = "value";
    return roles;
}

Q_PROPERTY(int count READ count NOTIFY countChanged)
