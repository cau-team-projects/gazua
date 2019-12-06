#ifndef COIN_INFO_H
#define COIN_INFO_H

#include <QAbstractItemModel>
#include <QStandardItem>
#include <QMap>
#include "Ticker.h"
#include "Constraint.h"

namespace Gazua {
    class CoinInfo;
};

class Gazua::CoinInfo : public QAbstractItemModel {
    Q_OBJECT
private:
    QMap<QString, Ticker> m_tickers;
    QMap<QString, Constraint> m_constraints;
    QStandardItem* m_rootItem;
    enum class Row : int {
        TICKERS = 0,
        CONSTRAINTS
    };
public:
    virtual ~CoinInfo();
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    virtual QModelIndex parent(const QModelIndex &index) const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QStandardItem* getItem(const QModelIndex&) const;

    explicit CoinInfo(QObject* parent = nullptr);
    quint64 total_constraint();
    void total_constraint(quint64);
    quint64 timestamp();
    void timestamp(quint64);
    void tickers(QMap<QString, Ticker>&& tickers);
    void constraints(QMap<QString, Constraint>&& constraints);
};

#endif
