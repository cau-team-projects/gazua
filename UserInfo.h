#ifndef USER_INFO_H
#define USER_INFO_H

#include <QAbstractItemModel>
#include <QStandardItem>
#include <QMap>
#include "Balance.h"
#include "Volume.h"

namespace Gazua {
    class UserInfo;
};

class Gazua::UserInfo : public QAbstractItemModel {
    Q_OBJECT
private:
    QMap<QString, Balance> m_balances;
    quint64 m_total_volume; // 모든 통화쌍 거래의 거래량 총합(KRW).
    quint64 m_timestamp; // 최종 거래량 및 거래 수수료 산정 시각(매시간에 한번씩 갱신).
    QMap<QString, Volume> m_volumes;
    QStandardItem* m_rootItem;
    enum class Row : int {
        BALANCES = 0,
        TOTAL_VOLUME,
        TIMESTAMP,
        VOLUMES
    };

    static constexpr int BALANCES = 0;
public:
    virtual ~UserInfo();
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    virtual QModelIndex parent(const QModelIndex &index) const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QStandardItem* getItem(const QModelIndex&) const;

    explicit UserInfo(QObject* parent = nullptr);
    quint64 total_volume();
    void total_volume(quint64);
    quint64 timestamp();
    void timestamp(quint64);
    void balances(QMap<QString, Balance>&& balances);
    void volumes(QMap<QString, Volume>&& volumes);
    void balance(const QString&, const Balance&);
    void volume(const QString&, const Volume&);
};

#endif
