#ifndef USER_INFO_H
#define USER_INFO_H

#include <unordered_map>
#include "Balance.h"

namespace Gazua {
    class UserInfo;
};

class Gazua::UserInfo {
public:
    //각 통화쌍 balance에 volume(30일간 거래량)을 포함시킴
    std::unordered_map<std::string, Balance> balances;
    explicit UserInfo();
};

#endif
