#include <optional>
#include <QDateTime>
#include <QDebug>
#include "Token.h"
#include "TokenType.h"

Gazua::Token::Token(TokenType tokenType, uint32_t scope, uint32_t expiration, const QString& accessToken, const QString& refreshToken) {
    m_tokenType = tokenType;
    m_scope = scope;
    m_currentTime = QDateTime::currentMSecsSinceEpoch();
    m_expiration = expiration;
    m_accessToken = accessToken;
    m_refreshToken = refreshToken;
}

std::optional<QString> Gazua::Token::accessToken() {
    if(m_currentTime + m_expiration >= QDateTime::currentMSecsSinceEpoch())
        return std::nullopt;
    return std::optional<QString>{m_accessToken};
}

QDebug Gazua::operator<<(QDebug debug, const Gazua::Token& token) {
    switch(token.m_tokenType) {
    case TokenType::UNKNOWN:
        debug.nospace() << "tokenType: Unknown" << "\n";
        break;
    case TokenType::BEARER:
        debug.nospace() << "tokenType: Bearer" << "\n";
        break;
    }
    debug.nospace() << "scope: ";
    if(token.m_scope & Token::VIEW)
        debug << "VIEW";
    if(token.m_scope & Token::TRADE)
        debug << "TRADE";
    if(token.m_scope & Token::WITHDRAWL)
        debug << "WITHDRAWL";
    debug.nospace() << "\n";
    debug.nospace() << "currentTime: " << token.m_currentTime << "\n";
    debug.nospace() << "expiration: " << token.m_expiration << "\n";
    debug.nospace() << "accessToken: " << token.m_accessToken << "\n";
    debug.nospace() << "refreshToken: " << token.m_refreshToken << "\n";
    return debug;
}
