#include <QObject>
#include <QtNetwork>
#include <QString>
#include <QUrl>
#include "API.h"

Gazua::API::API(): m_token{}
{}

bool Gazua::API::access(const std::string& key, const std::string& secret) {
    m_accessReply = m_qnam.get(QNetworkRequest{QUrl{"https://api.korbit.co.kr/v1/ticker/detailed/all"}});
    connect(m_accessReply, &QNetworkReply::finished, this, &Gazua::API::accessFinished);
    return true;
}

bool Gazua::API::refresh() {
    return true;
}

void Gazua::API::accessFinished() {
    qDebug() << "accessFinished()";
    qDebug() << QString::fromUtf8(m_accessReply->readAll());
}
