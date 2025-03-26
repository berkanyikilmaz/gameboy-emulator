#include "bus.h"

#include <cpu.h>
#include <iostream>
#include <ostream>
#include <utils/debug.h>

#include "common.h"
#include "cartridge.h"
#include "ram.h"

Bus::Bus(Cartridge *cart, CPU *cpu, RAM *ram) : m_cartridge(cart), m_cpu(cpu), m_ram(ram) {}

uint8_t Bus::read(const uint16_t addr) const {
    if (addr < 0x8000) {
        return m_cartridge->read(addr);
    } else if (addr < 0xA000) {

    } else if (addr < 0xC000) {
        return m_cartridge->read(addr);
    } else if (addr < 0xE000) {
        return m_ram->readWRAM(addr);
    } else if (addr < 0xFE00) {
        Debug::logErr("Prohibited address op", addr);
        exit(1);
    } else if (addr < 0xFEA0) {

    } else if (addr < 0xFF00) {
        Debug::logErr("Prohibited address op", addr);
        exit(1);
    } else if (addr < 0xFF80) {

    } else if (addr < 0xFFFF) {
        return m_ram->readHRAM(addr);
    } else if (addr == 0xFFFF) {
        return m_cpu->readIE();
    }

    Debug::logErr("Unimplemented address op", addr);

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
    } else if (addr < 0xA000) {
        NO_IMPL
    } else if (addr < 0xC000) {
        m_cartridge->write(addr, data);
    } else if (addr < 0xE000) {
        m_ram->writeWRAM(addr, data);
    } else if (addr < 0xFE00) {
        Debug::logErr("Prohibited address op", addr);
        exit(1);
    } else if (addr < 0xFEA0) {

    } else if (addr < 0xFF00) {
        Debug::logErr("Prohibited address op", addr);
        exit(1);
    } else if (addr < 0xFF80) {

    } else if (addr < 0xFFFF) {
        m_ram->writeHRAM(addr, data);
    } else if (addr == 0xFFFF) {
        m_cpu->writeIE(data);
    }
}

void Bus::write16(uint16_t addr, uint16_t data) const {
    write(addr, data & 0xFF);
    write(addr + 1, (data >> 8) & 0xFF);
}
