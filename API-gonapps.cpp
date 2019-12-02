#include <QObject>
#include <QtNetwork>
#include <QString>
#include <QUrl>
#include "API.h"

Gazua::API::API(): m_token{}
{}
/*
bool Gazua::API::access(const QString& key, const QString& secret) {

    connect(m_accessReply, &QNetworkReply::finished, this, &Gazua::API::accessFinished);
    const QString url_qs = "https://api.korbit.co.kr/v1/oauth2/access_token";
    QUrl url = url_qs;

    QUrlQuery query;
    query.addQueryItem("client_id", QString::fromStdString(key));
    query.addQueryItem("client_secret", QString::fromStdString(secret));
    query.addQueryItem("grant_type", "client_credentials");

    QString data_qs = query.query(QUrl::FullyEncoded) ;
    data_qs.replace("+", "%2B");
    QByteArray data = data_qs.toUtf8();

    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    req.setHeader(QNetworkRequest::ContentLengthHeader, data.count());

    m_accessReply = m_qnam.post(req, data);

    QString accessData = (QString) m_accessReply->readAll();
    QJsonDocument accessDoc = QJsonDocument::fromJson(accessData.toUtf8());
    QJsonObject accessObj = accessDoc.object();

    QJsonValue token_type = accessObj.value("token_type");
    QJsonValue access_token = accessObj.value("access_token");
    QJsonValue expires_in = accessObj.value("expires_in");
    QJsonValue scope = accessObj.value("scope");
    QJsonValue refresh_token = accessObj.value("refresh_token");

    return true;
}
*/
bool Gazua::API::access(const QString& key, const QString& secret) {
    m_accessReply = m_qnam.get(QNetworkRequest{QUrl{"https://api.korbit.co.kr/v1/ticker/detailed/all"}});
    connect(m_accessReply, &QNetworkReply::finished, this, [this]() {
        qDebug() << QString::fromUtf8(m_accessReply->readAll());
        m_accessReply->close();
    });
    return true;
}

bool Gazua::API::refresh() {
    return true;
}
