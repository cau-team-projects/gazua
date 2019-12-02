#ifndef TOKEN_H
#define TOKEN_H

#include <optional>
#include <QString>
#include "TokenType.h"

namespace Gazua {
    class Token;
};

class Gazua::Token {
private:
    TokenType m_tokenType;
    uint32_t m_scope;
    uint32_t m_expiration;
    QString m_accessToken;
    QString m_refreshToken;
public:
    constexpr static uint32_t VIEW = 1 << 0;
    constexpr static uint32_t TRADE = 1 << 1;
    constexpr static uint32_t WITHDRAWL = 1 << 2;
    explicit Token(TokenType tokenType, uint32_t scope, uint32_t expiration, const QString& accessToken, const QString& refreshToken);
    std::optional<QString> accessToken();
};

#endif
