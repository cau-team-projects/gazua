#include "API.h"
#include "CoinTreeItem.h"

CoinTreeItem::CoinTreeItem(const QVector<QVariant> &data, CoinTreeItem *parent) : itemData(data), parentItem(parent) {}

CoinTreeItem::~CoinTreeItem() { qDeleteAll(childItems); }

CoinTreeItem *CoinTreeItem::parent() { return parentItem; }

CoinTreeItem *CoinTreeItem::child(int number) {
    if (number < 0 || number >= childItems.size()) return nullptr;
    else return childItems.at(number);
}

int CoinTreeItem::childCount() const { return childItems.count(); }

int CoinTreeItem::childNumber() const {
    if (parentItem) return parentItem->childItems.indexOf(const_cast<CoinTreeItem*>(this));
    else return 0;
}

int CoinTreeItem::columnCount() const { return itemData.count(); }

QVariant CoinTreeItem::data(int column) const {
    if (column < 0 || column >= itemData.size()) return QVariant();
    else return itemData.at(column);
}

bool CoinTreeItem::setData(int column, const QVariant &value) {
    if (column < 0 || column >= itemData.size()) return false;
    itemData[column] = value;
    return true;
}

bool CoinTreeItem::insertChildren(int position, int count, int columns) {
    if (position < 0 || position > childItems.size()) return false;

    for (int row = 0; row < count; ++row) {
        QVector<QVariant> data(columns);
        CoinTreeItem *item = new CoinTreeItem(data, this);
        childItems.insert(position, item);
    }
    return true;
}

bool CoinTreeItem::removeChildren(int position, int count) {
    if (position < 0 || position + count > childItems.size()) return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);
    return true;
}

bool CoinTreeItem::insertColumns(int position, int columns) {
    if (position < 0 || position > itemData.size()) return false;

    for (int column = 0; column < columns; ++column)
        itemData.insert(position, QVariant());
    for (CoinTreeItem *child : qAsConst(childItems))
        child->insertColumns(position, columns);
    return true;
}

