#include "bus.h"

#include <iostream>
#include <ostream>
#include <__format/format_functions.h>

#include "cartridge.h"
#include "common.h"

Bus::Bus(Cartridge *cart, CPU *cpu) : m_cartridge(cart), m_cpu(cpu) {}

uint8_t Bus::read(const uint16_t addr) const {
    if (addr < 0x8000) {
        return m_cartridge->read(addr);
    }

    NO_IMPL;
}

uint16_t Bus::read16(uint16_t addr) const {
    const auto lo = read(addr);
    const auto hi = read(addr + 1);
    return (hi << 8) | lo;
}

void Bus::write(const uint16_t addr, const uint8_t data) const {
    if (addr < 0x8000) {
        m_cartridge->write(addr, data);
    }

    NO_IMPL
}

void Bus::write16(uint16_t addr, uint16_t data) const {
    write(addr, data & 0xFF);
    write(addr + 1, (data >> 8) & 0xFF);
}
