#ifndef BUS_H
#define BUS_H
#include <cartridge.h>
#include <cstdint>


class Bus {
public:
    Bus(Cartridge *cart);

    const uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t data);
private:
    Cartridge* m_cartridge;
};



#endif //BUS_H
