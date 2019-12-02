#ifndef ORDER_H
#define ORDER_H
#include "API.h"

namespace Gazua {
    class Order;
};

class Gazua::Order {
public:
    QString currency_pair,		// 해당 통화쌍
                side;				// 매수/매도 구분 (매수: bid, 매도: ask)
    uint64_t    avg_price,			// 체결 가격의 가중 평균치
                price;				// 주문 시에 설정한 지정가, 기본값은 0 
    long double order_amount,		// 주문 시에 지정한 코인의 수량
                filled_amount;		// 현재까지 체결된 코인의 수량
    uint64_t    order_total,		// 주문 금액
                filled_total,		// 체결 금액
                created_at,			// 거래를 주문한 시각 Unix timestamp(milliseconds)
                last_filled_at;		// 거래가 부분 체결된 최종 시각 Unix timestamp(milliseconds)
    QString status;				// 현재 주문의 상태 ('unfilled', 'partially_filled', 'filled')
    long double fee;				// 거래 수수료
    // id(주문의 ID 식별번호)는 map 자료형에서 key값으로 사용 예정

    Order(QString _currency_pair, QString _side, uint64_t _avg_price, uint64_t _price, long double _order_amount,
          long double _filled_amount, uint64_t _order_total, uint64_t _filled_total, uint64_t _created_at,
          uint64_t _last_filled_at, QString _status, long double _fee);
};

#endif
