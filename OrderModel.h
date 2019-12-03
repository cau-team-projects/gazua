#ifndef ORDERMODEL_H
#define ORDERMODEL_H

#include <QAbstractListModel>
#include "API.h"

namespace Gazua {
    class OrderModel;
}

class OrderModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    OrderModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    //QVariant data(const QModelIndex &index, int role) const;
    bool append(const QModelIndex &index,std::shared_ptr<QMap<uint64_t, Gazua::Order>> orders);
    bool remove(const QModelIndex &parent = QModelIndex());

private:
    struct order {
        QString id;
        QString currency_pair;
        QString side;
        QString avg_price;
        QString price;
        QString order_amount;
        QString filled_amount;
        QString order_total;
        QString filled_total;
        QString created_at;
        QString last_filled_at;
        QString status;
        QString fee;
    };

    QList<order> orderList;
};

#endif
