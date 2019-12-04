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
    QMap<QString, Volume> m_volumes;
public:
    explicit UserInfo();
    const QMap<QString, Balance>& balances() const;
    QMap<QString, Balance>& balances();
    const QMap<QString, Volume>& volumes() const;
    QMap<QString, Volume>& volumes();
};

#endif
