#ifndef WALLET_H
#define WALLET_H

#include <ctime>
#include <memory>

namespace Gazua {
    class Wallet;
};

class Gazua::Wallet {
public:
    long double available,        //현재 거래 가능한 화폐 수량
            trade_in_use,         //현재 거래중인 화폐 수량
            withdrawal_in_use,    //현재 출금이 진행중인 화폐 수량
            avg_price;            //코인의 경우 평균 매수 단가
    std::time_t avg_price_updated_at; //평균 매수 단가가 계산된 시각

    // GET https://api.korbit.co.kr/v1/user/volume
    long double month_volume;     //30일간의 거래량
};

#endif
