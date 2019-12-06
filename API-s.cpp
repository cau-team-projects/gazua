#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QMap>
#include <QNetworkRequest>
#include <QDebug>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include "API.h"
#include "CoinTreeModel.h"
#include "CoinTreeItem.h"

bool Gazua::API::refreshCoinInfo(std::shared_ptr<CoinTreeModel> coinInfoModel) {

    QJsonObject detailObject;
    QJsonObject constraintObject;

    QNetworkRequest detailRequest{QUrl{"https://api.korbit.co.kr/v1/ticker/detailed/all"}};
    QNetworkReply *detailReply = m_qnam.get(detailRequest);
    connect(detailReply, &QNetworkReply::finished, this, [this, detailReply, coinInfoModel] () {
        QJsonObject detailObject = QJsonDocument::fromJson(detailReply->readAll()).object();
        CoinTreeItem *coinTreeRoot = coinInfoModel->getItem(coinInfoModel->index(0, 0, QModelIndex()));
        coinTreeRoot->removeChildren(0, coinTreeRoot->childCount()); // removeAll except root
        for(const QString& coinName : detailObject.keys()) {
            coinTreeRoot->insertChildren(coinTreeRoot->childCount(), 1, 1);

            CoinTreeItem *coinType = coinTreeRoot->child(coinTreeRoot->childCount() - 1);
            coinType->setData(0, coinName);

            for(const QString& fieldName : detailObject[coinName].toObject().keys()) {
                coinType->insertChildren(coinType->childCount(), 1, 2);
                coinType->child(coinType->childCount() - 1)->setData(0, fieldName);
                coinType->child(coinType->childCount() - 1)->setData(1, detailObject.value(coinName).toObject().value(fieldName).toVariant());
            }
        }
        detailReply->close();
        // detailReply->deleteLater(); not sure


        QNetworkRequest constraintRequest{QUrl{"https://api.korbit.co.kr/v1/constants"}};
        QNetworkReply *constraintReply = m_qnam.get(constraintRequest);
        connect(constraintReply, &QNetworkReply::finished, this, [this, constraintReply, coinTreeRoot] () {
            QJsonObject constraintObject = QJsonDocument::fromJson(constraintReply->readAll()).object()["exchange"].toObject();

            //CoinTreeItem *coinTreeRoot = coinInfoModel->getItem(coinInfoModel->index(0, 0, QModelIndex()));

            int i = 0;
            for(const QString& coinName : constraintObject.keys()) {
                CoinTreeItem *coinType = coinTreeRoot->child(i);
                qDebug() << coinTreeRoot->childCount();
                qDebug() << coinType->childCount();
                for(const QString& fieldName : constraintObject[coinName].toObject().keys()) {
                    qDebug() << coinName << fieldName << coinType->childCount();
                    coinType->insertChildren(coinType->childCount(), 1, 2);
                    coinType->child(coinType->childCount() - 1)->setData(0, fieldName);
                    coinType->child(coinType->childCount() - 1)->setData(1, constraintObject.value(coinName).toObject().value(fieldName).toVariant());
                }
                i++;
            }

            constraintReply->close();
            // constraintReply->deleteLater(); not sure
        });






    });

    /*
    QNetworkRequest constraintRequest{QUrl{"https://api.korbit.co.kr/v1/constants"}};
    QNetworkReply *constraintReply = m_qnam.get(constraintRequest);
    connect(constraintReply, &QNetworkReply::finished, this, [this, constraintReply, coinInfoModel] () {
        QJsonObject constraintObject = QJsonDocument::fromJson(constraintReply->readAll()).object()["exchange"].toObject();

        CoinTreeItem *coinTreeRoot = coinInfoModel->getItem(coinInfoModel->index(0, 0, QModelIndex()));

        int i = 0;
        for(const QString& coinName : constraintObject.keys()) {
            CoinTreeItem *coinType = coinTreeRoot->child(i);
            for(const QString& fieldName : constraintObject[coinName].toObject().keys()) {
                    qDebug() << coinName << fieldName << coinType->childCount();
                coinType->insertChildren(coinType->childCount(), 1, 2);
                coinType->child(coinType->childCount() - 1)->setData(0, fieldName);
                coinType->child(coinType->childCount() - 1)->setData(1, constraintObject.value(coinName).toObject().value(fieldName).toVariant());
            }
            i++;
        }

        constraintReply->close();
        // constraintReply->deleteLater(); not sure
    });
*/

    return true;
}

