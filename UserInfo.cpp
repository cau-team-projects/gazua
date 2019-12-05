#include <QDebug>
#include <QModelIndex>
#include <QVariant>
#include "Balance.h"
#include "UserInfo.h"
#include "Volume.h"

using namespace Gazua;

UserInfo::UserInfo(QObject* parent):
QAbstractItemModel{parent}
{}

QModelIndex UserInfo::index(int row, int column, const QModelIndex &parent) const {
    qDebug() << "index" << row << column;
    if(!hasIndex(row, column, parent))
        return QModelIndex{};
    return createIndex(row, column, nullptr);
}

QModelIndex UserInfo::parent(const QModelIndex &index) const {
    return QModelIndex{};
}

int UserInfo::rowCount(const QModelIndex &parent) const {
    if(parent.isValid()) {
        qDebug() << "rowCount" << 0;
        return 0;
    }
    qDebug() << "rowCount" << 10;
    return m_balances.size();
}

int UserInfo::columnCount(const QModelIndex &parent) const {
    if(parent.isValid()) {
        qDebug() << "columnCount" << 0;
        return 0;
    }
    qDebug() << "columnCount" << 1;
    return 1;
}

QVariant UserInfo::data(const QModelIndex &index, int role) const {
    if(!index.isValid()) {
        qDebug() << "data" << index.row() << index.column() << QVariant{};

        return QVariant{};
    }

    if(role != Qt::DisplayRole)
        return QVariant{};

    qDebug() << "data" << index.row() << index.column() << m_balances[m_balances.keys().at(index.row())].avg_price_updated_at;

    return m_balances[m_balances.keys().at(index.row())].avg_price_updated_at;
}

Qt::ItemFlags UserInfo::flags(const QModelIndex &index) const {
    if(!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

QVariant UserInfo::headerData(int section, Qt::Orientation orientation, int role) const {
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return QVariant{"header"};
    return QVariant{};
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

const QMap<QString, Balance>& UserInfo::balances() const {
    return m_balances;
}

QMap<QString, Balance>& UserInfo::balances() {
    return m_balances;
}

const QMap<QString, Volume>& UserInfo::volumes() const {
    return m_volumes;
}

QMap<QString, Volume>& UserInfo::volumes() {
    return m_volumes;
}
