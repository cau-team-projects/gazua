#include <QDebug>
#include <QVariant>
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

    m_rootItem->child(static_cast<int>(Row::BALANCES))->appendRow(new QStandardItem{"empty"});
    m_rootItem->child(static_cast<int>(Row::TOTAL_VOLUME))->appendRow(new QStandardItem{"empty"});
    m_rootItem->child(static_cast<int>(Row::TIMESTAMP))->appendRow(new QStandardItem{"empty"});
    m_rootItem->child(static_cast<int>(Row::VOLUMES))->appendRow(new QStandardItem{"empty"});
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
}

quint64 UserInfo::timestamp() {
    return m_timestamp;
}

void UserInfo::timestamp(quint64 val) {
    m_timestamp = val; 
    m_rootItem->child(static_cast<int>(Row::TIMESTAMP))->child(0)->setText(std::move(QString::number(m_timestamp)));
}

void UserInfo::balances(QMap<QString, Balance>&& balances) {
    beginResetModel();
    m_balances = std::move(balances);
    auto balancesRow = m_rootItem->child(static_cast<int>(Row::BALANCES));
    balancesRow->removeRows(0, balancesRow->rowCount());
    foreach(auto& key, m_balances.keys()) {
        auto balanceRow = new QStandardItem{};
        balanceRow->setText(key);
        balanceRow->appendRow({new QStandardItem{"available"}, new QStandardItem{QString::number(m_balances[key].available)}});
        balanceRow->appendRow({new QStandardItem{"trade_in_use"}, new QStandardItem{QString::number(m_balances[key].trade_in_use)}});
        balanceRow->appendRow({new QStandardItem{"withdrawal_in_use"}, new QStandardItem{QString::number(m_balances[key].withdrawal_in_use)}});
        balanceRow->appendRow({new QStandardItem{"avg_price"}, new QStandardItem{QString::number(m_balances[key].avg_price)}});
        balanceRow->appendRow({new QStandardItem{"avg_price_updated_at"}, new QStandardItem{QString::number(m_balances[key].avg_price_updated_at)}});
        balancesRow->appendRow(balanceRow);
    }
    endResetModel();
}
void UserInfo::volumes(QMap<QString, Volume>&& volumes) {
    m_volumes = std::move(volumes);
}

void UserInfo::balance(const QString& coinName, const Balance& balance) {
    m_balances[coinName] = balance;
}

void UserInfo::volume(const QString& coinName, const Volume& volume) {
    m_volumes[coinName] = volume;
}
