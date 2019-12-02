#include <QObject>
#include <QtNetwork>
#include <QString>
#include <QUrl>
#include <QJsonDocument>
#include "API.h"
#include "Token.h"

Gazua::API::API(): m_token{}
{}

bool Gazua::API::access(const QString& key, const QString& secret) {
    QUrlQuery query;
    query.addQueryItem("client_id", key);
    query.addQueryItem("client_secret", secret);
    query.addQueryItem("grant_type", "client_credentials");
    QNetworkRequest request{QUrl{"https://api.korbit.co.kr/v1/oauth2/access_token"}};
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    auto reply = m_qnam.post(request, query.query().toUtf8());
    connect(reply, &QNetworkReply::finished, this, [this, reply] () {
        auto jsonObj = QJsonDocument::fromJson(reply->readAll()).object();
        auto tokenType = jsonObj["token_type"].toString() == "Bearer" ? TokenType::BEARER : TokenType::UNKNOWN;
        auto scopeList = jsonObj["scope"].toString().split(',', QString::SkipEmptyParts);
        auto expiration = jsonObj["expires_in"].toInt();
        auto accessToken = jsonObj["access_token"].toString();
        auto refreshToken = jsonObj["refresh_token"].toString();
        m_token = Token(tokenType, 1, expiration, accessToken, refreshToken);
        reply->close();
        // reply->deleteLater(); not sure
    });
    return true;
}

bool Gazua::API::refresh() {
    return true;
}
