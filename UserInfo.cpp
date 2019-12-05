#include <QDebug>
#include <QModelIndex>
#include <QVariant>
#include "Balance.h"
#include "UserInfo.h"
#include "Volume.h"

using namespace Gazua;

UserInfo::UserInfo(QObject* parent):
QAbstractItemModel{parent}
{
    m_rootItem = new QStandardItem{};
    m_rootItem->appendRow(new QStandardItem{"balances"});
    m_rootItem->appendRow(new QStandardItem{"total_volume"});

    m_rootItem->child(1)->appendRow(new QStandardItem{"value"});
    m_rootItem->child(1)->appendRow(new QStandardItem{"value"});
    m_rootItem->child(1)->appendRow(new QStandardItem{"value"});

    m_rootItem->appendRow(new QStandardItem{"timestamp"});
    m_rootItem->child(2)->appendRow(new QStandardItem{"value"});
    m_rootItem->appendRow(new QStandardItem{"volumes"});
}

QModelIndex UserInfo::index(int row, int column, const QModelIndex &parent) const {
/*
    qDebug() << "index" << row << column;
    if(!hasIndex(row, column, parent))
        return QModelIndex{};
    return createIndex(row, column, nullptr);
*/
    if(parent.isValid() && parent.column() != 0)
        return QModelIndex{};
    auto parentItem = getItem(parent);
    auto childItem = parentItem->child(row, 0);
    if(childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
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
    qDebug() << "rowCount" << getItem(parent)->rowCount();
    return getItem(parent)->rowCount();
/*
    if(parent.isValid()) {
        qDebug() << "rowCount" << 0;
        return 0;
    }
    qDebug() << "rowCount" << 10;
    return m_balances.size();
*/
}

int UserInfo::columnCount(const QModelIndex &parent) const {
    return getItem(parent)->columnCount();
}

QVariant UserInfo::data(const QModelIndex &index, int role) const {
    if(!index.isValid())
        return QVariant{};
    if(role != Qt::DisplayRole)
        return QVariant{};
    auto item = getItem(index);
    return item->data(index.column());
/*
    if(!index.isValid()) {
        qDebug() << "data" << index.row() << index.column() << QVariant{};

        return QVariant{};
    }

    if(role != Qt::DisplayRole)
        return QVariant{};

    qDebug() << "data" << index.row() << index.column() << m_balances[m_balances.keys().at(index.row())].avg_price_updated_at;

    return m_balances[m_balances.keys().at(index.row())].avg_price_updated_at;
*/
}

Qt::ItemFlags UserInfo::flags(const QModelIndex &index) const {
    if(!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

QVariant UserInfo::headerData(int section, Qt::Orientation orientation, int role) const {
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        if(section == 0)
            return QVariant{"header"};
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
}

quint64 UserInfo::timestamp() {
    return m_timestamp;
}

void UserInfo::timestamp(quint64 val) {
    m_timestamp = val; 
}

void UserInfo::balance(const QString& coinName, const Balance& balance) {
    m_balances[coinName] = balance;
}

void UserInfo::volume(const QString& coinName, const Volume& volume) {
    m_volumes[coinName] = volume;
}
