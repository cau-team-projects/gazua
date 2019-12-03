#ifndef COINTREEITEM_H
#define COINTREEITEM_H

#include <QVector>
#include <QVariant>

namespace Gazua {
    class CoinTreeItem;
};

class CoinTreeItem
{
private:
    QVector<CoinTreeItem*> childItems;
    QVector<QVariant> itemData;
    CoinTreeItem *parentItem;

public:
    explicit CoinTreeItem(const QVector<QVariant> &data, CoinTreeItem *parent = nullptr);
    ~CoinTreeItem();

    CoinTreeItem *child(int number);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    bool insertChildren(int position, int count, int columns);
    bool insertColumns(int position, int columns);
    CoinTreeItem *parent();
    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);
    int childNumber() const;
    bool setData(int column, const QVariant &value);
};

#endif
