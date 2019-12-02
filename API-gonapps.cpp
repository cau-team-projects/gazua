#include <QObject>
#include <QtNetwork>
#include <QString>
#include <QUrl>
#include <QJsonDocument>
#include "API.h"

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
    connect(reply, &QNetworkReply::finished, this, [reply]() {
        auto jsonObj = QJsonDocument::fromJson(QString::fromUtf8(reply->readAll()).object();
        auto tokenType = jsonObj["token_type"];
        auto accessToken = jsonObj["access_token"].toString();
        auto scope = jsonObj["scope"].toString().split(',', QString::SkipEmptyParts);
        auto refreshToken = jsonObj["refresh_token"].toString();
        reply->close();
        // reply->deleteLater(); not sure
    });
    return true;
}

bool Gazua::API::refresh() {
    return true;
}
