#include "bus.h"

#include "common.h"

Bus::Bus(Cartridge *cart) : m_cartridge(cart) {}

const uint8_t Bus::read(uint16_t addr) {
    if (addr < 0x8000) {
        return m_cartridge->read(addr);
    }

    NO_IMPL;
}

void Bus::write(uint16_t addr, uint8_t data) {
    if (addr < 0x8000) {
        m_cartridge->write(addr, data);
    }

    NO_IMPL
}
