#include <optional>
#include "Token.h"
#include "TokenType.h"

Gazua::Token::Token(TokenType tokenType, uint32_t scope, uint32_t expiration, const QString& accessToken, const QString& refreshToken) {
    m_scope = scope;
    m_expiration = expiration;
    m_accessToken = accessToken;
    m_refreshToken = refreshToken;
}

std::optional<QString> Gazua::Token::accessToken() {
    if(true)
        return std::nullopt;
    return std::optional<QString>{m_accessToken};
}
