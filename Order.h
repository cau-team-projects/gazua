#ifndef ORDER_H
#define ORDER_H

#include <QtGlobal>
#include "API.h"

namespace Gazua {
    class Order;
};

struct Gazua::Order {
    QString currency_pair; // 해당 통화쌍
    QString side; // 매수/매도 구분 (매수: bid, 매도: ask)
    quint64 avg_price; // 체결 가격의 가중 평균치
    quint64 price; // 주문 시에 설정한 지정가, 기본값은 0
    qreal order_amount; // 주문 시에 지정한 코인의 수량
    qreal filled_amount; // 현재까지 체결된 코인의 수량
    quint64 order_total; // 주문 금액
    quint64 filled_total; // 체결 금액
    quint64 created_at; // 거래를 주문한 시각 Unix timestamp(milliseconds)
    quint64 last_filled_at; // 거래가 부분 체결된 최종 시각 Unix timestamp(milliseconds)
    QString status; // 현재 주문의 상태 ('unfilled', 'partially_filled', 'filled')
    qreal fee; // 거래 수수료
};

#endif
