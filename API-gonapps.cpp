#include <QObject>
#include <QtNetwork>
#include <QString>
#include <QUrl>
#include <QJsonDocument>
#include "API.h"
#include "Token.h"

Gazua::API::API(QString&& key, QString&& secret): m_key{std::move(key)}, m_secret{std::move(secret)}, m_token{}
{}

bool Gazua::API::access() {
    QUrlQuery query;
    query.addQueryItem("client_id", m_key);
    query.addQueryItem("client_secret", m_secret);
    query.addQueryItem("grant_type", "client_credentials");
    QNetworkRequest request{QUrl{"https://api.korbit.co.kr/v1/oauth2/access_token"}};
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    auto reply = m_qnam.post(request, query.query().toUtf8());
    connect(reply, &QNetworkReply::finished, this, [this, reply] () {
        const auto jsonObj = QJsonDocument::fromJson(reply->readAll()).object();
        const auto tokenType = jsonObj["token_type"].toString() == "Bearer" ? TokenType::BEARER : TokenType::UNKNOWN;
        const auto scopeStringList = jsonObj["scope"].toString().split(',', QString::SkipEmptyParts);
        uint32_t scope = 0;
        for(const auto& scopeString : scopeStringList) {
            if(scopeString == "VIEW")
                scope = scope | Token::VIEW;
            else if(scopeString == "TRADE")
                scope = scope | Token::TRADE;
            else if(scopeString == "WITHDRAWL")
                scope = scope | Token::WITHDRAWL;
        }
        if(jsonObj["access_token"].isUndefined()) {
            m_token = std::nullopt;
            qDebug() << "Failed to fetch token";
        } else {
            const auto expiration = jsonObj["expires_in"].toInt();
            const auto accessToken = jsonObj["access_token"].toString();
            const auto refreshToken = jsonObj["refresh_token"].toString();
            m_token.emplace(Token{tokenType, scope, static_cast<uint32_t>(expiration), accessToken, refreshToken});
        }
        reply->close();
        // reply->deleteLater(); not sure
    });

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    return true;
}

bool Gazua::API::refresh() {
    if(!m_token.has_value() || !m_token.value().refreshToken().has_value())
        return false;
    QUrlQuery query;
    query.addQueryItem("client_id", m_key);
    query.addQueryItem("client_secret", m_secret);
    query.addQueryItem("grant_type", "refresh_token");
    query.addQueryItem("refresh_token", m_token.value().refreshToken().value());
    QNetworkRequest request{QUrl{"https://api.korbit.co.kr/v1/oauth2/access_token"}};
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    auto reply = m_qnam.post(request, query.query().toUtf8());
    connect(reply, &QNetworkReply::finished, this, [this, reply] () {
        const auto jsonObj = QJsonDocument::fromJson(reply->readAll()).object();
        const auto tokenType = jsonObj["token_type"].toString() == "Bearer" ? TokenType::BEARER : TokenType::UNKNOWN;
        const auto scopeStringList = jsonObj["scope"].toString().split(',', QString::SkipEmptyParts);
        uint32_t scope = 0;
        if(jsonObj["access_token"].isUndefined()) {
            m_token = std::nullopt;
            qDebug() << "Failed to fetch token";
        } else {
            const auto expiration = jsonObj["expires_in"].toInt();
            const auto accessToken = jsonObj["access_token"].toString();
            const auto refreshToken = jsonObj["refresh_token"].toString();
            m_token = Token{tokenType, scope, static_cast<uint32_t>(expiration), accessToken, refreshToken};
            qDebug() << m_token.value();
        }
        reply->close();
        // reply->deleteLater(); not sure
    });
    return true;
}

// GET https://api.korbit.co.kr/v1/user/balances
// GET https://api.korbit.co.kr/v1/user/volume
bool Gazua::API::refreshUserInfo(std::shared_ptr<UserInfo> userInfo) {
    if(!m_token.has_value() || !m_token.value().accessToken().has_value())
        return false;
    const auto accessToken = m_token.value().accessToken().value();
    QNetworkRequest request{QUrl{"https://api.korbit.co.kr/v1/user/balances"}};
    request.setRawHeader(QString{"Authorization"}.toUtf8(), QString{"Bearer %1"}.arg(accessToken).toUtf8());
    auto reply = m_qnam.get(request);
    connect(reply, &QNetworkReply::finished, this, [reply, userInfo] () {
        qDebug() << reply->readAll();
    });
    return true;
}
