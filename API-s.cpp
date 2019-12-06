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

    QModelIndex coinTreeRootIndex = coinInfoModel->index(0, 0, QModelIndex());
    CoinTreeItem *coinTreeRootItem = coinInfoModel->getRootItem();

    QNetworkRequest detailRequest{QUrl{"https://api.korbit.co.kr/v1/ticker/detailed/all"}};
    QNetworkReply *detailReply = m_qnam.get(detailRequest);

    QNetworkRequest constraintRequest{QUrl{"https://api.korbit.co.kr/v1/constants"}};
    QNetworkReply *constraintReply = m_qnam.get(constraintRequest);

    connect(detailReply, &QNetworkReply::finished, this, [this, detailReply, constraintReply, coinInfoModel, coinTreeRootItem, coinTreeRootIndex] () {
        QJsonObject detailObject = QJsonDocument::fromJson(detailReply->readAll()).object();

        coinTreeRootItem->insertChildren(coinTreeRootItem->childCount(), 1, 1);
        CoinTreeItem *timeItem = coinTreeRootItem->child(coinTreeRootItem->childCount() - 1);
        QModelIndex timeItemIndex = coinInfoModel->index(coinTreeRootItem->childCount() - 1, 0, coinTreeRootIndex);
        coinInfoModel->setData(timeItemIndex, QDateTime::currentSecsSinceEpoch());

        for(const QString& coinName : detailObject.keys()) {
            timeItem->insertChildren(timeItem->childCount(), 1, 1);
            CoinTreeItem *coinTypeItem = timeItem->child(timeItem->childCount() - 1);
            QModelIndex coinTypeItemIndex = coinInfoModel->index(timeItem->childCount() - 1, 0, timeItemIndex);
            coinInfoModel->setData(coinTypeItemIndex, coinName);

            for(const QString& fieldName : detailObject[coinName].toObject().keys()) {
                coinTypeItem->insertChildren(coinTypeItem->childCount(), 1, 2);
                QModelIndex coinFieldItemIndex = coinInfoModel->index(coinTypeItem->childCount() - 1, 0, coinTypeItemIndex);
                QModelIndex coinValueItemIndex = coinInfoModel->index(coinTypeItem->childCount() - 1, 1, coinTypeItemIndex);
                coinInfoModel->setData(coinFieldItemIndex, fieldName);
                coinInfoModel->setData(coinValueItemIndex, detailObject.value(coinName).toObject().value(fieldName).toVariant());
            }
        }
        detailReply->close();
        // detailReply->deleteLater(); not sure

        //qDebug() << coinTreeRootItem->child(coinTreeRootItem->childCount() - 1)->child(0)->child(0)->data(1) ;
        qDebug() << coinTreeRootItem->childCount();


        connect(constraintReply, &QNetworkReply::finished, this, [constraintReply, coinInfoModel, timeItem, timeItemIndex] () {
            QJsonObject constraintObject = QJsonDocument::fromJson(constraintReply->readAll()).object()["exchange"].toObject();

            int constraint_coinNameIter = 0;
            for(const QString& coinName : constraintObject.keys()) {
                CoinTreeItem *coinTypeItem = timeItem->child(constraint_coinNameIter);
                QModelIndex coinTypeItemIndex = coinInfoModel->index(constraint_coinNameIter, 0, timeItemIndex);

                for(const QString& fieldName : constraintObject[coinName].toObject().keys()) {
                    coinTypeItem->insertChildren(coinTypeItem->childCount(), 1, 2);
                    QModelIndex coinFieldItemIndex = coinInfoModel->index(coinTypeItem->childCount() - 1, 0, coinTypeItemIndex);
                    QModelIndex coinValueItemIndex = coinInfoModel->index(coinTypeItem->childCount() - 1, 1, coinTypeItemIndex);
                    coinInfoModel->setData(coinFieldItemIndex, fieldName);
                    coinInfoModel->setData(coinValueItemIndex, constraintObject.value(coinName).toObject().value(fieldName).toVariant());
                }
                constraint_coinNameIter++;
            }

            constraintReply->close();
            // constraintReply->deleteLater(); not sure
        });

    });

    return true;
}

