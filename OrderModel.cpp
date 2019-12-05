#include "OrderModel.h"

using namespace Gazua;

OrderModel::OrderModel(QObject *parent)
    : QAbstractTableModel(parent) {
}

int OrderModel::rowCount(const QModelIndex &parent) const {
    return orders.count();
}

int OrderModel::columnCount(const QModelIndex &parent) const {
    return 13;
}

QVariant OrderModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
        ;//return orderList[index.row()][index.column()];
    else
        return QVariant();
}

const QVariantMap& OrderModel::getOrders() const{
    return orders;
}

void OrderModel::append(QString id, QVariantMap orderField) {
    orders.insert(id, orderField);
}

void OrderModel::remove(QString id) {
    orders.remove(id);
}

QHash<int, QByteArray> OrderModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[FieldRole] = "field";
    return roles;
}

Q_PROPERTY(int count READ count NOTIFY countChanged)
