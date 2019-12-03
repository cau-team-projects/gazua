#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

#include <cstdint>

namespace Gazua {
    enum class TokenType : uint8_t {
        BEARER,
        UNKNOWN
    };
};

#endif
