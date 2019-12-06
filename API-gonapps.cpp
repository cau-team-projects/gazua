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
    QNetworkRequest req{QUrl{"https://api.korbit.co.kr/v1/oauth2/access_token"}};
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    auto reply = m_qnam.post(req, query.query().toUtf8());
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
        //reply->deleteLater();
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
    QNetworkRequest req{QUrl{"https://api.korbit.co.kr/v1/oauth2/access_token"}};
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    auto reply = m_qnam.post(req, query.query().toUtf8());
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
        //reply->deleteLater();
    });
    return true;
}

// GET https://api.korbit.co.kr/v1/user/balances
// GET https://api.korbit.co.kr/v1/user/volume
bool Gazua::API::refreshUserInfo(std::shared_ptr<UserInfo> userInfo) {
    if(!m_token.has_value() || !m_token.value().accessToken().has_value())
        return false;
    const auto accessToken = m_token.value().accessToken().value();
    QNetworkRequest balancesReq{std::move(QUrl{"https://api.korbit.co.kr/v1/user/balances"})};
    balancesReq.setRawHeader(QString{"Authorization"}.toUtf8(), QString{"Bearer %1"}.arg(accessToken).toUtf8());
    auto balancesReply = m_qnam.get(balancesReq);
    connect(balancesReply, &QNetworkReply::finished, this, [balancesReply, userInfo] () {
        const auto root = QJsonDocument::fromJson(balancesReply->readAll()).object();
        QMap<QString, Balance> balances;
        for(const auto& coinName : root.keys()) {
             balances[coinName] = (struct Balance) {
                 .available = root[coinName]["available"].toString().toDouble(),
                 .trade_in_use = root[coinName]["trade_in_use"].toString().toDouble(),
                 .withdrawal_in_use = root[coinName]["withdrawal_in_use"].toString().toDouble(),
                 .avg_price = root[coinName]["avg_price"].toString().toDouble(),
                 .avg_price_updated_at = static_cast<quint64>(root[coinName]["avg_price_updated_at"].toDouble())
             };
/*
             qDebug() << coinName << ">>>>>>>>>>>>>>>>";
             qDebug() << "available: " << balance.available;
             qDebug() << "trade_in_use: " << balance.trade_in_use;
             qDebug() << "withdrawal_in_use: " << balance.withdrawal_in_use;
             qDebug() << "avg_price: " << balance.avg_price;
             qDebug() << "avg_price_updated_at: " << balance.avg_price_updated_at;
*/
        }
        userInfo->balances(std::move(balances));
    });
    QNetworkRequest volumesReq{std::move(QUrl{"https://api.korbit.co.kr/v1/user/volume"})};
    volumesReq.setRawHeader(QString{"Authorization"}.toUtf8(), QString{"Bearer %1"}.arg(accessToken).toUtf8());
    auto volumesReply = m_qnam.get(volumesReq);
    connect(volumesReply, &QNetworkReply::finished, this, [volumesReply, userInfo] () {
        auto data = volumesReply->readAll();
        const auto root = QJsonDocument::fromJson(std::move(data)).object();
        userInfo->total_volume(static_cast<quint64>(root["total_volume"].toDouble()));
        userInfo->timestamp(static_cast<quint64>(root["timestamp"].toDouble()));
/*
        qDebug() << "total_volume: " << userInfo->total_volume();
        qDebug() << "timestamp: " << userInfo->timestamp();
*/

        for(const auto& coinName : root.keys()) {
            userInfo->volume(
                coinName,
                (struct Volume) {
                    .volume = static_cast<quint64>(root[coinName]["volume"].toString().toULongLong()),
                    .maker_fee = root[coinName]["maker_fee"].toString().toDouble(),
                    .taker_fee = root[coinName]["taker_fee"].toString().toDouble()
                }
            );
/*
            qDebug() << coinName << ">>>>>>>>>>>>>>>>";
            qDebug() << "volume: " << volume.volume;
            qDebug() << "maker_fee: " << volume.maker_fee;
            qDebug() << "taker_fee: " << volume.taker_fee;
*/

        }
    });
    return true;
}
