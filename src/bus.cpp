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

void Bus::write(const uint16_t addr, const uint8_t data) const {
    if (addr < 0x8000) {
        m_cartridge->write(addr, data);
    }

    NO_IMPL
}
