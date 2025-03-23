#ifndef BUS_H
#define BUS_H
#include <cstdint>

class Cartridge;
class CPU;

class Bus {
public:
    Bus(Cartridge *cart, CPU *cpu);

    uint8_t read(uint16_t addr) const;
    void write(uint16_t addr, uint8_t data) const;
private:
    Cartridge* m_cartridge;
    CPU* m_cpu;
};

#endif //BUS_H
