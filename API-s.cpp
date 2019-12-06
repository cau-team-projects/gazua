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

    QNetworkRequest detailRequest{QUrl{"https://api.korbit.co.kr/v1/ticker/detailed/all"}};
    QNetworkReply *detailReply = m_qnam.get(detailRequest);

    QModelIndex coinTreeRootIndex = coinInfoModel->index(0, 0, QModelIndex());
    CoinTreeItem *coinTreeRoot = coinInfoModel->getItem(coinTreeRootIndex);

    connect(detailReply, &QNetworkReply::finished, this, [this, detailReply, coinInfoModel, coinTreeRoot, coinTreeRootIndex] () {
        QJsonObject detailObject = QJsonDocument::fromJson(detailReply->readAll()).object();

        bool isInitializing = (coinTreeRoot->childCount() <= 0) ? true : false;
        int fieldNameIter = 0;

        int detail_coinNameIter = 0;
        for(const QString& coinName : detailObject.keys()) {
            if (isInitializing) coinTreeRoot->insertChildren(detail_coinNameIter, 1, 1);
            CoinTreeItem *coinType = coinTreeRoot->child(detail_coinNameIter);
            QModelIndex coinTypeIndex = coinInfoModel->index(detail_coinNameIter, 0, coinTreeRootIndex);
            if (isInitializing) coinInfoModel->setData(coinTypeIndex, coinName);

            fieldNameIter = 0;
            for(const QString& fieldName : detailObject[coinName].toObject().keys()) {
                if (isInitializing) coinType->insertChildren(fieldNameIter, 1, 2);
                if (isInitializing) coinInfoModel->setData(coinInfoModel->index(fieldNameIter, 0, coinTypeIndex), fieldName);
                coinInfoModel->setData(coinInfoModel->index(fieldNameIter, 1, coinTypeIndex), detailObject.value(coinName).toObject().value(fieldName).toVariant());

                fieldNameIter++;
            }
            detail_coinNameIter++;
        }
        detailReply->close();
        // detailReply->deleteLater(); not sure



        QNetworkRequest constraintRequest{QUrl{"https://api.korbit.co.kr/v1/constants"}};
        QNetworkReply *constraintReply = m_qnam.get(constraintRequest);

        connect(constraintReply, &QNetworkReply::finished, this, [constraintReply, isInitializing, coinInfoModel, coinTreeRoot, coinTreeRootIndex, fieldNameIter] () {
            QJsonObject constraintObject = QJsonDocument::fromJson(constraintReply->readAll()).object()["exchange"].toObject();

            int constraint_coinNameIter = 0;
            int constraint_fieldNameIter = fieldNameIter;

            for(const QString& coinName : constraintObject.keys()) {
                CoinTreeItem *coinType = coinTreeRoot->child(constraint_coinNameIter);
                QModelIndex coinTypeIndex = coinInfoModel->index(constraint_coinNameIter, 0, coinTreeRootIndex);

                constraint_fieldNameIter = fieldNameIter;
                for(const QString& fieldName : constraintObject[coinName].toObject().keys()) {
                    if (isInitializing) coinType->insertChildren(constraint_fieldNameIter, 1, 2);
                    if (isInitializing) coinInfoModel->setData(coinInfoModel->index(constraint_fieldNameIter, 0, coinTypeIndex), fieldName);
                    coinInfoModel->setData(coinInfoModel->index(constraint_fieldNameIter, 1, coinTypeIndex), constraintObject.value(coinName).toObject().value(fieldName).toVariant());

                    constraint_fieldNameIter++;
                }
                constraint_coinNameIter++;
            }

            constraintReply->close();
            // constraintReply->deleteLater(); not sure
        });

    });

    return true;
}

