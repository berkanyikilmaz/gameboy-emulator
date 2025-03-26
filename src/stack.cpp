#include "stack.h"

#include "cpu.h"
#include "bus.h"

Stack::Stack(Registers *cpuRegisters, Bus *bus) {
    m_cpuRegisters = cpuRegisters;
    m_bus = bus;
}

void Stack::push(const uint8_t data) const {
    m_cpuRegisters->SP--;
    m_bus->write(m_cpuRegisters->SP, data);
}

void Stack::push16(const uint16_t data) const {
    push((data >> 8) & 0xFF);
    push(data & 0xFF);
}

const uint8_t Stack::pop() const {
    return m_bus->read(m_cpuRegisters->SP++);
}

const uint16_t Stack::pop16() const {
    const uint16_t lo = pop();
    const uint16_t hi = pop();
    return (hi << 8) | lo;
}
