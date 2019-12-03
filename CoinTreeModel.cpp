#include <QModelIndex>
#include <QDateTime>
#include "CoinTreeModel.h"

CoinTreeModel::CoinTreeModel(const QStringList &headers, const QString &data, QObject *parent) : QAbstractItemModel(parent) {
    QVector<QVariant> rootData;
    for (const QString &header : headers)
        rootData << header;
    rootItem = new CoinTreeItem(rootData);
}
CoinTreeModel::~CoinTreeModel() { delete rootItem; }

CoinTreeItem *CoinTreeModel::getItem(const QModelIndex &index) const {
    if (index.isValid()) {
        CoinTreeItem *item = static_cast<CoinTreeItem*>(index.internalPointer());
        if (item) return item;
    }
    return rootItem;
}

QVariant CoinTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    CoinTreeItem *item = static_cast<CoinTreeItem*>(index.internalPointer());

    return item->data(index.column());
}

QVariant CoinTreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex CoinTreeModel::index(int row, int column, const QModelIndex &parent) const {
    if (parent.isValid() && parent.column() != 0) return QModelIndex();
    CoinTreeItem *parentItem = getItem(parent);
    if (!parentItem) return QModelIndex();

    CoinTreeItem *childItem = parentItem->child(row);

    if (childItem) return createIndex(row, column, childItem);
    else return QModelIndex();
}

QModelIndex CoinTreeModel::parent(const QModelIndex &index) const {
    if (!index.isValid()) return QModelIndex();
    CoinTreeItem *childItem = getItem(index);
    CoinTreeItem *parentItem = childItem ? childItem->parent() : nullptr;

    if (parentItem == rootItem || !parentItem) return QModelIndex();
    else return createIndex(parentItem->childNumber(), 0, parentItem);
}

int CoinTreeModel::rowCount(const QModelIndex &parent) const {
    const CoinTreeItem *parentItem = getItem(parent);
    return parentItem ? parentItem->childCount() : 0;
}

int CoinTreeModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return rootItem->columnCount();
}

Qt::ItemFlags CoinTreeModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) return Qt::NoItemFlags;
    else return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

//bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
//bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;
//bool insertColumns(int position, int columns, const QModelIndex &parent = QModelIndex()) override;
//bool removeColumns(int position, int columns, const QModelIndex &parent = QModelIndex()) override;
//bool insertRows(int position, int rows,  const QModelIndex &parent = QModelIndex()) override;
//bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;

bool CoinTreeModel::appendCoinInfos(std::shared_ptr<QMap<QString, Gazua::CoinInfo>> coinInfos) {

    /*
    ** rootItem
    ** └┬ item(QDateTime time)
    **  └┬ item(QString coinName)
    **   └─ item(Gazua::CoinInfo coinField)
    */

    rootItem->insertChildren(0, 1, 1);
    CoinTreeItem *newCoinInfosItem = rootItem->child(rootItem->childCount() - 1);
    newCoinInfosItem->setData(0, QDateTime::currentDateTime());

    newCoinInfosItem->insertChildren(0, coinInfos->size(), 1);
    for(int i = 0; i < newCoinInfosItem->childCount(); ++i) {
        CoinTreeItem *newCoinItem = newCoinInfosItem->child(i);
        newCoinItem->setData(0, coinInfos->keys().at(i));

        newCoinItem->insertChildren(0, 1, 1);
        CoinTreeItem *newCoinFields = newCoinItem->child(0);
        newCoinFields->setData(0, QVariant::fromValue<Gazua::CoinInfo>(coinInfos->values().at(i)));
    }

    return true;
}
