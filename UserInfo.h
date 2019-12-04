#ifndef USER_INFO_H
#define USER_INFO_H

#include <QMap>
#include "Balance.h"
#include "Volume.h"

namespace Gazua {
    class UserInfo;
};

class Gazua::UserInfo {
private:
    QMap<QString, Balance> m_balances;
    quint64 m_total_volume; // 모든 통화쌍 거래의 거래량 총합(KRW).
    quint64 m_timestamp; // 최종 거래량 및 거래 수수료 산정 시각(매시간에 한번씩 갱신).
    QMap<QString, Volume> m_volumes;
public:
    explicit UserInfo();
    quint64 total_volume();
    void total_volume(quint64);
    quint64 timestamp();
    void timestamp(quint64);
    const QMap<QString, Balance>& balances() const;
    QMap<QString, Balance>& balances();
    const QMap<QString, Volume>& volumes() const;
    QMap<QString, Volume>& volumes();
};

#endif
