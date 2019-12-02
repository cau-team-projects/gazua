#ifndef TOKEN_H
#define TOKEN_H

#include "TokenType.h"

namespace Gazua {
    class Token;
};

class Gazua::Token {
private:
    constexpr static uint32_t VIEW = 1 << 0;
    constexpr static uint32_t TRADE = 1 << 1;
    constexpr static uint32_t WITHDRAWL = 1 << 2;
//    TokenType tokenType;
    uint32_t scope;
    uint32_t expiration;
    std::string accessToken;
    std::string refreshToken;
};

#endif
