#include <QDebug>
#include <QVariant>
#include <QDateTime>
#include "Balance.h"
#include "UserInfo.h"
#include "Volume.h"

using namespace Gazua;

UserInfo::UserInfo(QObject* parent):
QAbstractItemModel{parent}
{
    m_rootItem = new QStandardItem{0, 2};
    m_rootItem->appendRow(new QStandardItem{"balances"});
    m_rootItem->appendRow(new QStandardItem{"total_volume"});
    m_rootItem->appendRow(new QStandardItem{"timestamp"});
    m_rootItem->appendRow(new QStandardItem{"volumes"});
    m_rootItem->child(static_cast<int>(Row::TOTAL_VOLUME))->appendRow(new QStandardItem{"empty"});
    m_rootItem->child(static_cast<int>(Row::TIMESTAMP))->appendRow(new QStandardItem{"empty"});
}

UserInfo::~UserInfo() {
    delete m_rootItem;
}

QModelIndex UserInfo::index(int row, int column, const QModelIndex &parent) const {
    auto parentItem = getItem(parent);
    auto childItem = parentItem->child(row, column);
    if(childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex{};
}

QModelIndex UserInfo::parent(const QModelIndex &index) const {
    if(!index.isValid())
        return QModelIndex{};
    auto childItem = getItem(index);
    auto parentItem = childItem->parent();
    if(parentItem == m_rootItem)
        return QModelIndex{};
    return createIndex(parentItem->row(), 0, parentItem);
}

int UserInfo::rowCount(const QModelIndex &parent) const {
    return getItem(parent)->rowCount();
}

int UserInfo::columnCount(const QModelIndex &parent) const {
    return getItem(parent)->columnCount();
}

QVariant UserInfo::data(const QModelIndex &index, int role) const {
    if(!index.isValid())
        return QVariant{};
    if(role != Qt::DisplayRole)
        return QVariant{};
    return getItem(index)->data(Qt::DisplayRole);
}

Qt::ItemFlags UserInfo::flags(const QModelIndex &index) const {
    if(!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

QVariant UserInfo::headerData(int section, Qt::Orientation orientation, int role) const {
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return QVariant{section};
    }
    return QVariant{};
}

QStandardItem* UserInfo::getItem(const QModelIndex& index) const {
    if(index.isValid()) {
        auto item = static_cast<QStandardItem*>(index.internalPointer());
        if(item)
            return item;
    }
    return m_rootItem;
}

quint64 UserInfo::total_volume() {
    return m_total_volume;
}

void UserInfo::total_volume(quint64 val) {
    m_total_volume = val;
    m_rootItem->child(static_cast<int>(Row::TOTAL_VOLUME))->child(0)->setText(std::move(QString::number(m_total_volume)));
    dataChanged(index(static_cast<int>(Row::TOTAL_VOLUME), 0), index(static_cast<int>(Row::TOTAL_VOLUME), 0));
}

quint64 UserInfo::timestamp() {
    return m_timestamp;
}

void UserInfo::timestamp(quint64 val) {
    m_timestamp = val; 
    m_rootItem->child(static_cast<int>(Row::TIMESTAMP))->child(0)->setText(std::move(QString::number(m_timestamp)));
    dataChanged(index(static_cast<int>(Row::TIMESTAMP), 0), index(static_cast<int>(Row::TIMESTAMP), 0));

}

void UserInfo::balances(QMap<QString, Balance>&& balances) {
    balances = std::move(balances);

    auto balancesRow = m_rootItem->child(static_cast<int>(Row::BALANCES));
    if(balancesRow->rowCount() == 0) {
        foreach(auto& key, balances.keys()) {
            auto balanceRow = new QStandardItem{};
            balanceRow->setText(key);
            balanceRow->appendRow({new QStandardItem{"available"}, new QStandardItem{QString::number(balances[key].available, 'f')}});
            balanceRow->appendRow({new QStandardItem{"trade_in_use"}, new QStandardItem{QString::number(balances[key].trade_in_use, 'f')}});
            balanceRow->appendRow({new QStandardItem{"withdrawal_in_use"}, new QStandardItem{QString::number(balances[key].withdrawal_in_use, 'f')}});
            balanceRow->appendRow({new QStandardItem{"avg_price"}, new QStandardItem{QString::number(balances[key].avg_price, 'f')}});
            balanceRow->appendRow({new QStandardItem{"avg_price_updated_at"}, new QStandardItem{QString::number(balances[key].avg_price_updated_at)}});
            balancesRow->appendRow(balanceRow);
        }
    } else {
        auto i = 0;
        foreach(auto &key, balances.keys()) {
            auto balanceRow = balancesRow->child(i);
            balanceRow->child(0, 1)->setText(QString::number(balances[key].available, 'f'));
            balanceRow->child(1, 1)->setText(QString::number(balances[key].trade_in_use, 'f'));
            balanceRow->child(2, 1)->setText(QString::number(balances[key].withdrawal_in_use, 'f'));
            balanceRow->child(3, 1)->setText(QString::number(balances[key].avg_price, 'f'));
            balanceRow->child(4, 1)->setText(QString::number(balances[key].avg_price_updated_at));
            ++i;
        }
    }
    m_balances = std::move(balances);
    dataChanged(index(static_cast<int>(Row::BALANCES), 0), index(static_cast<int>(Row::BALANCES), 0));
}

void UserInfo::volumes(QMap<QString, Volume>&& volumes) {
    auto volumesRow = m_rootItem->child(static_cast<int>(Row::VOLUMES));
    if(volumesRow->rowCount() == 0) {
        foreach(auto& key, volumes.keys()) {
            auto volumeRow = new QStandardItem{};
            volumeRow->setText(key);
            volumeRow->appendRow({new QStandardItem{"volume"}, new QStandardItem{QString::number(volumes[key].volume)}});
            volumeRow->appendRow({new QStandardItem{"maker_fee"}, new QStandardItem{QString::number(volumes[key].maker_fee, 'f')}});
            volumeRow->appendRow({new QStandardItem{"taker_fee"}, new QStandardItem{QString::number(volumes[key].taker_fee, 'f')}});
            volumesRow->appendRow(volumeRow);

        }
    } else {
        auto i = 0;
        foreach(auto &key, volumes.keys()) {
            auto volumeRow = volumesRow->child(i);
            volumeRow->child(0, 1)->setText(QString::number(volumes[key].volume));
            volumeRow->child(1, 1)->setText(QString::number(volumes[key].maker_fee, 'f'));
            volumeRow->child(2, 1)->setText(QString::number(volumes[key].taker_fee, 'f'));
            ++i;
        }
    }
    m_volumes = std::move(volumes);
    dataChanged(index(static_cast<int>(Row::VOLUMES), 0), index(static_cast<int>(Row::VOLUMES), 0));
}
