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
public:
    explicit UserInfo(QMap<QString, Balance>&&, QMap<QString, Volume>&&);
};

#endif
