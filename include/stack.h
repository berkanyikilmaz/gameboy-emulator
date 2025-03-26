#ifndef STACK_H
#define STACK_H
#include <cstdint>

struct Registers;
class Bus;

class Stack {
public:
    explicit Stack(Registers *cpuRegisters, Bus *bus);

    void push(uint8_t data) const;
    void push16(uint16_t data) const;

    const uint8_t pop() const;
    const uint16_t pop16() const;
private:
    Registers *m_cpuRegisters;
    Bus *m_bus;
};

#endif //STACK_H
