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
        const auto root = QJsonDocument::fromJson(reply->readAll()).object();
        const auto tokenType = root["token_type"].toString() == "Bearer" ? TokenType::BEARER : TokenType::UNKNOWN;
        const auto scopeStringList = root["scope"].toString().split(',', QString::SkipEmptyParts);
        uint32_t scope = 0;
        for(const auto& scopeString : scopeStringList) {
            if(scopeString == "VIEW")
                scope = scope | Token::VIEW;
            else if(scopeString == "TRADE")
                scope = scope | Token::TRADE;
            else if(scopeString == "WITHDRAWAL")
                scope = scope | Token::WITHDRAWAL;
        }
        if(root["access_token"].isUndefined()) {
            m_token = std::nullopt;
            qDebug() << "Failed to fetch token";
        } else {
            const auto expiration = root["expires_in"].toInt();
            const auto accessToken = root["access_token"].toString();
            const auto refreshToken = root["refresh_token"].toString();
            m_token.emplace(Token{tokenType, scope, static_cast<uint32_t>(expiration), accessToken, refreshToken});
            qDebug() << m_token.value();
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
        const auto root = QJsonDocument::fromJson(reply->readAll()).object();
        const auto tokenType = root["token_type"].toString() == "Bearer" ? TokenType::BEARER : TokenType::UNKNOWN;
        const auto scopeStringList = root["scope"].toString().split(',', QString::SkipEmptyParts);
        uint32_t scope = 0;
        if(root["access_token"].isUndefined()) {
            m_token = std::nullopt;
            qDebug() << "Failed to fetch token";
        } else {
            const auto expiration = root["expires_in"].toInt();
            const auto accessToken = root["access_token"].toString();
            const auto refreshToken = root["refresh_token"].toString();
            m_token.emplace(Token{tokenType, scope, static_cast<uint32_t>(expiration), accessToken, refreshToken});
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
        const auto root = QJsonDocument::fromJson(reply->readAll()).object();
        for(const auto& coinName : root.keys()) {

             auto& balances = userInfo->balances();

             auto& balance = balances[coinName];
             balance.available = root[coinName]["available"].toString().toDouble();
             balance.trade_in_use = root[coinName]["trade_in_use"].toString().toDouble();
             balance.withdrawal_in_use = root[coinName]["withdrawal_in_use"].toString().toDouble(); 
             balance.avg_price = root[coinName]["avg_price"].toString().toDouble();
             balance.avg_price_updated_at = root[coinName]["avg_price_updated_at"].toDouble();

             qDebug() << coinName << ">>>>>>>>>>>>>>>>";
             qDebug() << "available: " << balance.available;
             qDebug() << "trade_in_use: " << balance.trade_in_use;
             qDebug() << "withdrawal_in_use: " << balance.withdrawal_in_use;
             qDebug() << "avg_price: " << balance.avg_price;
             qDebug() << "avg_price_updated_at: " << balance.avg_price_updated_at;
        }
    });
    return true;
}
