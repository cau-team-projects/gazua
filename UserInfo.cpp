#include "Balance.h"
#include "UserInfo.h"
#include "Volume.h"

using namespace Gazua;

UserInfo::UserInfo() {}

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
