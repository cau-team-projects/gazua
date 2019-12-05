#ifndef ORDERMODEL_H
#define ORDERMODEL_H

#include <QAbstractListModel>

namespace Gazua {
    class OrderModel;
};

class Gazua::OrderModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum MapRoles {
        NameRole = Qt::UserRole + 1,
        FieldRole
    };

    explicit OrderModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int count() const;

    const QVariantMap& getOrders() const;

    QVariantMap orders;

public slots:
    void append(QString id, QVariantMap orderField);
    void remove(QString id);
    void setMap(QVariantMap orders) { this->orders = orders; }
    QHash<int, QByteArray> roleNames() const;
signals:
    void countChanged(int count);
};

#endif
