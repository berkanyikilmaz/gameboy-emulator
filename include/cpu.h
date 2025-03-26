#ifndef CPU_H
#define CPU_H
#include <array>
#include <bus.h>
#include <cstdint>

#include "instructions.h"
#include "utils/bit_utils.h"

class Emulator;
class Bus;

struct Registers {
    uint8_t A;
    uint8_t F;
    uint8_t B;
    uint8_t C;
    uint8_t D;
    uint8_t E;
    uint8_t H;
    uint8_t L;
    uint16_t PC;
    uint16_t SP;
};

class CPU {
public:
    explicit CPU(Emulator *emulator);

    bool step();

    void connectBus(Bus *bus);

    void fetchInstruction();
    void fetchData();
    void executeInstruction();

    const uint8_t readReg(RegisterType regType) const;
    void writeReg(RegisterType regType, uint16_t data);
    const bool getFlagZ() const { return BitUtils::getBit(m_registers.F, 7); }
    const bool getFlagC() const { return BitUtils::getBit(m_registers.F, 4); }

    void writeIE(const uint8_t data) { m_IE = data; };
    const uint8_t readIE() const { return m_IE; };

    // Instruction Exec
    void executeNONE();
    void executeNOP();
    void executeLD();
    void executeLDH();
    void executeJP();
    void executeDI();
    void executeXOR();

    void setFlags(char z, char n, char h, char c);
    bool checkCond();

    const uint8_t fetchData8Bit(uint16_t addr);
    const uint16_t fetchData16Bit(uint16_t addr);

    void printInstruction();
private:
    Registers m_registers;

    uint16_t m_fetchedData;
    uint16_t m_memDest;
    bool m_destIsMem;
    uint8_t m_currOpcode;
    Instruction *m_currInstruction;

    std::array<void(CPU::*)(), static_cast<size_t>(IM_COUNT)> m_instructionHandlers;

    bool m_halted;
    bool m_IME; //Interrupt Master Enable Flag
    uint8_t m_IE; //Interrupt Enable Register

    Emulator *m_emulator;
    Bus *m_bus;
};

#endif //CPU_H
