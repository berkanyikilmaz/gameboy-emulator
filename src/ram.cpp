#include "ram.h"

RAM::RAM(): m_wram{}, m_hram{} {
}

void RAM::writeWRAM(const uint16_t addr, const uint8_t data) {
    uint16_t wramAddr = addr - 0xC000;
    m_wram[wramAddr] = data;
}

void RAM::writeHRAM(const uint16_t addr, const uint8_t data) {
    uint16_t hramAddr = addr - 0xFF80;
    m_hram[hramAddr] = data;
}

const uint8_t RAM::readWRAM(const uint16_t addr) {
    uint16_t wramAddr = addr - 0xC000;
    return m_wram[wramAddr];
}

const uint8_t RAM::readHRAM(const uint16_t addr) {
    uint16_t hramAddr = addr - 0xFF80;
    return m_hram[hramAddr];
}