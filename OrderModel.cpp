#include "OrderModel.h"



OrderModel::OrderModel(QObject *parent)
    : QAbstractTableModel(parent) {
}

int OrderModel::rowCount(const QModelIndex &parent) const {
    return orderList.size();
}

int OrderModel::columnCount(const QModelIndex &parent) const {
    return 13;
}

QVariant OrderModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
        return orderList[index.row()][index.column()];
    else
        return QVariant();
}

bool OrderModel::append(const QModelIndex &parent, std::shared_ptr<QMap<uint64_t, Gazua::Order>> orders) {
    int cols = columnCount();

    beginInsertRows(parent, 0, orders->size());

    for(auto row = orders->begin(); row != orders->end(); row++) {
       QStringList tmp;
       tmp.append(QString::number(row.key()));
       tmp.append(row->currency_pair);
       tmp.append(row->side);
       tmp.append(QString::number(row->avg_price));
       tmp.append(QString::number(row->price));
       tmp.append(QString::number((double)row->order_amount));
       tmp.append(QString::number((double)row->filled_amount));
       tmp.append(QString::number(row->order_total));
       tmp.append(QString::number(row->filled_total));
       tmp.append(QString::number(row->created_at));
       tmp.append(QString::number(row->last_filled_at));
       tmp.append(row->status);
       tmp.append(QString::number((double)row->fee));

       orderList.push_back(tmp);
    }
    endInsertRows();
    return true;
}

bool OrderModel::remove(const QModelIndex &parent) {
    orderList.clear();
    return true;
}


