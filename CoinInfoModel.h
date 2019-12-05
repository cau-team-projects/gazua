#ifndef COIN_INFO_MODEL_H
#define COIN_INFO_MODEL_H

#include <QAbstractTableModel>
#include <QMap>

namespace Gazua {
    class CoinInfoModel;
};

class Gazua::CoinInfoModel : public QAbstractTableModel {
    Q_OBJECT

private:
    QVariantMap coinInfo;

public:
    enum MapRoles {
        KeyRole = Qt::UserRole + 1,
        ValueRole
    };

    explicit CoinInfoModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    const QVariantMap& getCoinInfo() const;
    bool contains(QString coinName) const;
    QVariantMap::iterator findCoinField(QString coinName);
    int count() const;

public slots:
    void append(QString coinName, QVariantMap coinFields);
    void remove(QString coinName);
    void setMap(QVariantMap coinInfo) { this->coinInfo = coinInfo; }
    QHash<int, QByteArray> roleNames() const;
signals:
    void countChanged(int count);

};

#endif
