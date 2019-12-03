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
