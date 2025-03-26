#ifndef RAM_H
#define RAM_H
#include <cstdint>

class RAM {
public:
    RAM();

    void writeWRAM(uint16_t addr, uint8_t data);
    void writeHRAM(uint16_t addr, uint8_t data);

    const uint8_t readWRAM(uint16_t addr);
    const uint8_t readHRAM(uint16_t addr);
private:
    uint8_t m_wram[0x2000];
    uint8_t m_hram[0x80];
};

#endif //RAM_H
