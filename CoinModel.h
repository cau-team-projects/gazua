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
    QMap<QString, QVariant>* coinInfosMap;

public:
    enum MapRoles {
        KeyRole = Qt::UserRole + 1,
        ValueRole
    };

    explicit CoinModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    int count() const;

public slots:
    void append(std::shared_ptr<QMap<QString, Gazua::CoinInfo>> newCoinInfo);
    void remove(QString index);
    void setMap(QMap<QString, QVariant> *coinInfosMap) { this->coinInfosMap = coinInfosMap; }

signals:
    void countChanged(int count);

};

#endif
