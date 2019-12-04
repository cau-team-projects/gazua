#include "Balance.h"
#include "UserInfo.h"
#include "Volume.h"

using namespace Gazua;

UserInfo::UserInfo() {}

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
