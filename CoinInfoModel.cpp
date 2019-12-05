#include "CoinInfoModel.h"

using namespace Gazua;

CoinInfoModel::CoinInfoModel(QObject* parent) : QAbstractTableModel{parent} {}

int CoinInfoModel::rowCount(const QModelIndex& parent) const {
    return coinInfo.count();
}

int CoinInfoModel::columnCount(const QModelIndex & parent) const {
    return 2;
}

QVariant CoinInfoModel::data(const QModelIndex& index, int role) const {

    if (role == Qt::DisplayRole) {
       return QString(coinInfo.keys().at(index.row()) + ", " + qvariant_cast<QVariantMap>(coinInfo.values().at(index.row())).value("test").toString()) //  + "Row%1, Column%2"
                   .arg(index.row() + 1)
                   .arg(index.column() +1);
    }
    else return QVariant();
}

const QVariantMap& CoinInfoModel::getCoinInfo() const {
    return coinInfo;
}

bool CoinInfoModel::contains(QString coinName) const {
    return coinInfo.contains(coinName);
}

QVariantMap::iterator CoinInfoModel::findCoinField(QString coinName) {
    return coinInfo.find(coinName);
}

void CoinInfoModel::append(QString coinName, QVariantMap coinFields) {
    coinInfo.insert(coinName, coinFields);
    return;
}

void CoinInfoModel::remove(QString coinName) {
    coinInfo.remove(coinName);
    return;
}

QHash<int, QByteArray> CoinInfoModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[FieldRole] = "field";
    return roles;
}

Q_PROPERTY(int count READ count NOTIFY countChanged)
