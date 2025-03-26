#ifndef BUS_H
#define BUS_H
#include <cstdint>

class Cartridge;
class CPU;
class RAM;

class Bus {
public:
    Bus(Cartridge *cart, CPU *cpu, RAM *ram);

    uint8_t read(uint16_t addr) const;
    uint16_t read16(uint16_t addr) const;
    void write(uint16_t addr, uint8_t data) const;
    void write16(uint16_t addr, uint16_t data) const;
private:
    Cartridge* m_cartridge;
    CPU* m_cpu;
    RAM* m_ram;
};

#endif //BUS_H
