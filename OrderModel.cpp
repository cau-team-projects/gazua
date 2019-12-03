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

bool OrderModel::append(const QModelIndex &parent, std::shared_ptr<QMap<uint64_t, Gazua::Order>> orders) {
    int cols = columnCount();

    beginInsertRows(parent, 0, orders->size());

    for(auto row = orders->begin(); row != orders->end(); row++) {
       order tmp;
       for(int col = 0; col < cols; col++) {
           tmp.id = QString::number(row.key());
           tmp.currency_pair = row->currency_pair;
           tmp.side = row->side;
           tmp.avg_price = QString::number(row->avg_price);
           tmp.price = QString::number(row->price);
           tmp.order_amount = QString::number((double)row->order_amount);
           tmp.filled_amount = QString::number((double)row->filled_amount);
           tmp.order_total = QString::number(row->order_total);
           tmp.filled_total = QString::number(row->filled_total);
           tmp.created_at = QString::number(row->created_at);
           tmp.last_filled_at = QString::number(row->last_filled_at);
           tmp.status = row->status;
           tmp.fee = QString::number((double)row->fee);
       }
       orderList.push_back(tmp);
    }
    endInsertRows();
    return true;
}

bool OrderModel::remove(const QModelIndex &parent) {
    orderList.clear();
    return true;
}


