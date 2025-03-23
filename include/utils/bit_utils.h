#ifndef BIT_UTILS_H
#define BIT_UTILS_H

#include <cstdint>
#include <stdexcept>

namespace BitUtils {
    template <typename T>
    constexpr bool getBit(T data, uint8_t bit) {
        static_assert(std::is_integral_v<T> && std::is_unsigned_v<T>, "T must be an unsigned integral type");

        if (bit >= sizeof(T) * 8) {
            throw std::out_of_range("Bit index out of range");
        }

        return (data >> bit) & 1;
    }

    inline void setBit(uint8_t *data, const uint8_t bit, bool value) {
        *data = value ? *data | (1 << bit) : *data & ~(1 << bit);
    }
};


#endif //BIT_UTILS_H
