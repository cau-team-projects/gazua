#include <QDebug>
#include <QVariant>
#include <QDateTime>
#include "Ticker.h"
#include "CoinInfo.h"
#include "Constraint.h"

using namespace Gazua;

CoinInfo::CoinInfo(QObject* parent):
QAbstractItemModel{parent}
{
    m_rootItem = new QStandardItem{0, 2};
    m_rootItem->appendRow(new QStandardItem{"tickers"});
    m_rootItem->appendRow(new QStandardItem{"constraints"});
}

CoinInfo::~CoinInfo() {
    delete m_rootItem;
}

QModelIndex CoinInfo::index(int row, int column, const QModelIndex &parent) const {
    auto parentItem = getItem(parent);
    auto childItem = parentItem->child(row, column);
    if(childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex{};
}

QModelIndex CoinInfo::parent(const QModelIndex &index) const {
    if(!index.isValid())
        return QModelIndex{};
    auto childItem = getItem(index);
    auto parentItem = childItem->parent();
    if(parentItem == m_rootItem)
        return QModelIndex{};
    return createIndex(parentItem->row(), 0, parentItem);
}

int CoinInfo::rowCount(const QModelIndex &parent) const {
    return getItem(parent)->rowCount();
}

int CoinInfo::columnCount(const QModelIndex &parent) const {
    return getItem(parent)->columnCount();
}

QVariant CoinInfo::data(const QModelIndex &index, int role) const {
    if(!index.isValid())
        return QVariant{};
    if(role != Qt::DisplayRole)
        return QVariant{};
    return getItem(index)->data(Qt::DisplayRole);
}

Qt::ItemFlags CoinInfo::flags(const QModelIndex &index) const {
    if(!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

QVariant CoinInfo::headerData(int section, Qt::Orientation orientation, int role) const {
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return QVariant{section};
    }
    return QVariant{};
}

QStandardItem* CoinInfo::getItem(const QModelIndex& index) const {
    if(index.isValid()) {
        auto item = static_cast<QStandardItem*>(index.internalPointer());
        if(item)
            return item;
    }
    return m_rootItem;
}

void CoinInfo::tickers(QMap<QString, Ticker>&& tickers) {
    tickers = std::move(tickers);
    auto tickersRow = m_rootItem->child(static_cast<int>(Row::TICKERS));
    if(tickersRow->rowCount() == 0) {
        foreach(auto& key, tickers.keys()) {
            auto tickerRow = new QStandardItem{};
            tickerRow->setText(key);
            tickerRow->appendRow({new QStandardItem{"timestamp"}, new QStandardItem{QString::number(tickers[key].timestamp)}});
            tickerRow->appendRow({new QStandardItem{"last"}, new QStandardItem{QString::number(tickers[key].last)}});
            tickerRow->appendRow({new QStandardItem{"open"}, new QStandardItem{QString::number(tickers[key].open)}});
            tickerRow->appendRow({new QStandardItem{"bid"}, new QStandardItem{QString::number(tickers[key].bid)}});
            tickerRow->appendRow({new QStandardItem{"ask"}, new QStandardItem{QString::number(tickers[key].ask)}});
            tickerRow->appendRow({new QStandardItem{"low"}, new QStandardItem{QString::number(tickers[key].low)}});
            tickerRow->appendRow({new QStandardItem{"high"}, new QStandardItem{QString::number(tickers[key].high)}});
            tickerRow->appendRow({new QStandardItem{"volume"}, new QStandardItem{QString::number(tickers[key].volume)}});
            tickerRow->appendRow({new QStandardItem{"change"}, new QStandardItem{QString::number(tickers[key].change)}});
            tickerRow->appendRow({new QStandardItem{"changePercent"}, new QStandardItem{QString::number(tickers[key].changePercent)}});
            tickersRow->appendRow(tickerRow);
        }
    } else {
        auto i = 0;
        foreach(auto &key, tickers.keys()) {
            auto tickerRow = tickersRow->child(i);
            tickerRow->child(0, 1)->setText(QString::number(tickers[key].timestamp));
            tickerRow->child(1, 1)->setText(QString::number(tickers[key].last));
            tickerRow->child(2, 1)->setText(QString::number(tickers[key].open));
            tickerRow->child(3, 1)->setText(QString::number(tickers[key].bid));
            tickerRow->child(4, 1)->setText(QString::number(tickers[key].ask));
            tickerRow->child(5, 1)->setText(QString::number(tickers[key].low));
            tickerRow->child(6, 1)->setText(QString::number(tickers[key].high));
            tickerRow->child(7, 1)->setText(QString::number(tickers[key].volume));
            tickerRow->child(8, 1)->setText(QString::number(tickers[key].change));
            tickerRow->child(9, 1)->setText(QString::number(tickers[key].changePercent));
            ++i;
        }
    }
    m_tickers = std::move(tickers);
    dataChanged(index(static_cast<int>(Row::TICKERS), 0), index(static_cast<int>(Row::TICKERS), 0));
}

void CoinInfo::constraints(QMap<QString, Constraint>&& constraints) {
    auto constraintsRow = m_rootItem->child(static_cast<int>(Row::CONSTRAINTS));
    if(constraintsRow->rowCount() == 0) {
        foreach(auto& key, constraints.keys()) {
            auto constraintRow = new QStandardItem{};
            constraintRow->setText(key);
            constraintRow->appendRow({new QStandardItem{"tick_size"}, new QStandardItem{QString::number(constraints[key].tick_size)}});
            constraintRow->appendRow({new QStandardItem{"min_price"}, new QStandardItem{QString::number(constraints[key].min_price)}});
            constraintRow->appendRow({new QStandardItem{"max_price"}, new QStandardItem{QString::number(constraints[key].max_price)}});
            constraintRow->appendRow({new QStandardItem{"order_min_price"}, new QStandardItem{QString::number(constraints[key].order_min_price)}});
            constraintRow->appendRow({new QStandardItem{"order_max_price"}, new QStandardItem{QString::number(constraints[key].order_max_price)}});
            constraintsRow->appendRow(constraintRow);
        }
    } else {
        auto i = 0;
        foreach(auto &key, constraints.keys()) {
            auto constraintRow = constraintsRow->child(i);
            constraintRow->child(0, 1)->setText(QString::number(constraints[key].tick_size));
            constraintRow->child(1, 1)->setText(QString::number(constraints[key].min_price));
            constraintRow->child(2, 1)->setText(QString::number(constraints[key].max_price));
            constraintRow->child(3, 1)->setText(QString::number(constraints[key].order_min_price));
            constraintRow->child(4, 1)->setText(QString::number(constraints[key].order_max_price));
            ++i;
        }
    }
    m_constraints = std::move(constraints);
    dataChanged(index(static_cast<int>(Row::CONSTRAINTS), 0), index(static_cast<int>(Row::CONSTRAINTS), 0));
}
