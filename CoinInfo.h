#ifndef COIN_INFO_H
#define COIN_INFO_H

#include <ctime>
#include <memory>

namespace Gazua {
    class CoinInfo;
};

class Gazua::CoinInfo {
public:
    //ticker
    std::time_t timestamp; //최종 체결 시각
    double last,      //최종 체결 가격
            open,          //최근 24시간 시작 가격
            bid,           //매수호가
            ask,           //매도호가
            low,           //최근 24시간 체결 가격 중 최저가
            high,          //최근 24시간 체결 가격 중 최고가
            volume,        //거래량
            change,        //시작 가격 대비 현재가 차이
            changePercent; //시작 가격 대비 현재가 차이 변화 비율

    //constraint
    double tick_size,  //호가 단위
            min_price,      //최소 주문가
            max_price,      //최대 주문가
            order_min_size, //매수/매도 수량 최소 입력값
            order_max_size; //매수/매도 수량 최대 입력값    

    CoinInfo();
    CoinInfo(double _timestamp, double _last, double _open, double _bid, double _ask, double _low, double _high, double _volume, double _change, double _changePercent, double _tick_size, double _min_price, double _max_price, double _order_min_size, double _order_max_size);

};



#endif
