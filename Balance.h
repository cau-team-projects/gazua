#ifndef BALANCE_H
#define BALANCE_H

#include <QtGlobal>

namespace Gazua {
    struct Balance;
};

struct Gazua::Balance {
    qreal available; //현재 거래 가능한 화폐 수량
    qreal trade_in_use; //현재 거래중인 화폐 수량
    qreal withdrawal_in_use; //현재 출금이 진행중인 화폐 수량
    qreal avg_price; //코인의 경우 평균 매수 단가
    quint64 avg_price_updated_at; //평균 매수 단가가 계산된 시각
};

#endif
