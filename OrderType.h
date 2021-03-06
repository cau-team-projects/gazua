#ifndef ORDER_TYPE_H
#define ORDER_TYPE_H

#include <cstdint>

namespace Gazua {

    enum class OrderType : uint8_t {
        LIMIT,
        MARKET
    };

};

#endif
