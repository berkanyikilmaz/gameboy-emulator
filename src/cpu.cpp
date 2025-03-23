#include "cpu.h"

#include <common.h>
#include <ostream>
#include <magic_enum/magic_enum.hpp>

#include "emulator.h"
#include "bus.h"
#include "instructions.h"
#include "utils/debug.h"

static constexpr std::array<void(CPU::*)(), static_cast<size_t>(IM_COUNT)> getInstructionHandlers() {
    std::array<void(CPU::*)(), static_cast<size_t>(IM_COUNT)> arr = {};

    arr.fill(&CPU::executeNONE);
    arr[IM_NOP] = &CPU::executeNOP;
    arr[IM_LD] = &CPU::executeLD;
    arr[IM_JP] = &CPU::executeJP;
    arr[IM_DI] = &CPU::executeDI;

    return arr;
};

CPU::CPU(Emulator *emulator)
    : m_registers(Registers()), m_fetchedData(0), m_memDest(0), m_destIsMem(false), m_currOpcode(0)
      , m_currInstruction(nullptr), m_instructionHandlers(getInstructionHandlers()), m_halted(false), m_IME(false), m_emulator(emulator)
      , m_bus(nullptr) {
    m_registers.PC = 0x100;
}

bool CPU::step() {
    if (!m_halted) {
        fetchInstruction();
        fetchData();
        executeInstruction();
    }

    return true;
}

void CPU::connectBus(Bus *bus) {
    m_bus = bus;
}

void CPU::fetchInstruction() {
    m_currOpcode = m_bus->read(m_registers.PC);
    m_currInstruction = getInstructionByOpcode(m_currOpcode);

    if (m_currInstruction->mnemonic == IM_NONE) {
        Debug::logErr("Unknown instruction", m_currOpcode);
        exit(-1);
    }

    printInstruction();
    m_registers.PC++;
}

/*
*I suppose you could make the switch/case a lot faster with threaded code.
Make a hash value for each op_code. e.g.
hash(AM_MR_R) => 29
Then make a lookup table (e.g. static void *labels[op_codes];) that takes these hashes and points directly to the execution code like this:

#define EXECUTE  goto *(labels[op_code])

this will make the code from O(n) to O(1) which I suppose is a good optimization, since the CPU instruction-lookup is the heart of the simulation, and you have more than 200 opcodes to check!
 *
 * NOTES FOR THE FUTURE!!!
 */
void CPU::fetchData() {
    m_memDest = 0;
    m_destIsMem = false;

    uint8_t lo, hi;
    uint16_t addr;

    switch (m_currInstruction->addrMode) {
        case AM_IMP:
            return;
        case AM_R:
            m_fetchedData = readReg(m_currInstruction->reg1);
            return;
        case AM_R_R:
            m_fetchedData = readReg(m_currInstruction->reg2);
            return;
        case AM_R_D8:
        case AM_R_A8:
        case AM_HL_SPR:
        case AM_D8:
            m_fetchedData = m_bus->read(m_registers.PC);
            m_emulator->cycle(1);
            m_registers.PC++;
            return;
        case AM_D16:
        case AM_R_D16:
            lo = m_bus->read(m_registers.PC);
            m_emulator->cycle(1);
            m_registers.PC++;

            hi = m_bus->read(m_registers.PC);
            m_emulator->cycle(1);
            m_registers.PC++;

            m_fetchedData = (hi << 8) | lo;
            return;
        case AM_MR_R:
            m_fetchedData = readReg(m_currInstruction->reg2);
            m_memDest = readReg(m_currInstruction->reg1);
            if (m_currInstruction->reg1 == RT_C) {
                m_memDest |= 0xFF00;
                }
            m_destIsMem = true;
            return;
        case AM_R_MR:
            addr = readReg(m_currInstruction->reg2);
            if (m_currInstruction->reg2 == RT_C) {
                addr |= 0xFF00;
            }
            m_fetchedData = m_bus->read(addr);
            m_emulator->cycle(1);
            return;
        case AM_R_HLI:
            m_fetchedData = m_bus->read(readReg(RT_HL));
            m_emulator->cycle(1);
            writeReg(RT_HL, readReg(RT_HL) + 1);
            return;
        case AM_R_HLD:
            m_fetchedData = m_bus->read(readReg(RT_HL));
            m_emulator->cycle(1);
            writeReg(RT_HL, readReg(RT_HL) - 1);
            return;
        case AM_HLI_R:
            m_fetchedData = readReg(m_currInstruction->reg2);
            m_memDest = readReg(RT_HL);
            m_destIsMem = true;
            writeReg(RT_HL, readReg(RT_HL) + 1);
            return;
        case AM_HLD_R:
            m_fetchedData = readReg(m_currInstruction->reg2);
            m_memDest = readReg(RT_HL);
            m_destIsMem = true;
            writeReg(RT_HL, readReg(RT_HL) - 1);
            return;
        case AM_A8_R:
            m_fetchedData = readReg(m_currInstruction->reg2);
            m_memDest = m_bus->read(m_registers.PC) | 0xFF00;
            m_destIsMem = true;
            m_emulator->cycle(1);
            m_registers.PC++;
            return;
        case AM_A16_R:
        case AM_D16_R:
            lo = m_bus->read(m_registers.PC);
            m_emulator->cycle(1);
            m_registers.PC++;

            hi = m_bus->read(m_registers.PC);
            m_emulator->cycle(1);
            m_registers.PC++;

            m_memDest = (hi << 8) | lo;
            m_destIsMem = true;
            m_fetchedData = readReg(m_currInstruction->reg2);
        case AM_MR_D8:
            m_fetchedData = m_bus->read(m_registers.PC);
            m_emulator->cycle(1);
            m_registers.PC++;

            m_memDest = readReg(m_currInstruction->reg1);
            m_destIsMem = true;
            return;
        case AM_MR:
            m_memDest = readReg(m_currInstruction->reg1);
            m_destIsMem = true;
            m_fetchedData = m_bus->read(readReg(m_currInstruction->reg1));
            m_emulator->cycle(1);
            return;
        case AM_R_A16:
            lo = m_bus->read(m_registers.PC);
            m_emulator->cycle(1);
            m_registers.PC++;

            hi = m_bus->read(m_registers.PC);
            m_emulator->cycle(1);
            m_registers.PC++;

            addr = (hi << 8) | lo;
            m_fetchedData = m_bus->read(addr);
            m_emulator->cycle(1);
    }
}

void CPU::executeInstruction() {
    (this->*m_instructionHandlers[static_cast<size_t>(m_currInstruction->mnemonic)])();
}

void CPU::executeNONE() {
    Debug::log("\tInvalid instruction");
    exit(-1);
}

void CPU::executeNOP() {
    Debug::log("\tNOP");
}

void CPU::executeLD() {
    if (m_destIsMem) {
        if (m_currInstruction->reg2 >= RT_AF) {
            m_bus->write16(m_memDest, m_fetchedData);
            m_emulator->cycle(1);
        }
        else {
            m_bus->write(m_memDest, m_fetchedData);
        }

        return;
    }

    if (m_currInstruction->addrMode == AM_HL_SPR) {
        writeReg(m_currInstruction->reg1,
            readReg(m_currInstruction->reg2) + static_cast<uint8_t>(m_fetchedData));

        const bool h = (readReg(m_currInstruction->reg2) & 0xF) + (m_fetchedData & 0xF) >= 0x10;
        const bool c = (readReg(m_currInstruction->reg2) & 0xFF) + (m_fetchedData & 0xFF) >= 0x100;
        setFlags(0, 0, h, c);
        return;
    }

    writeReg(m_currInstruction->reg1, m_fetchedData);
}

void CPU::executeJP() {
    Debug::log("\tJP");
    if (checkCond()) {
        m_registers.PC = m_fetchedData;
        m_emulator->cycle(1);
        Debug::log("\tCondition met, jumped to address", m_fetchedData);
        return;
    }
    Debug::log("\tCondition not met");
}

void CPU::executeDI() {
    m_IME = false;
    Debug::log("\tDI");
}

void CPU::executeXOR() {
    m_registers.A = m_registers.A ^ m_fetchedData;
    setFlags(m_registers.A, false, false, false);
    Debug::log("\tXOR");
}

void CPU::setFlags(const char z, const char n, const char h, const char c) {
    if (z != -1) {
        BitUtils::setBit(&m_registers.F, 7, z);
    }
    if (n != -1) {
        BitUtils::setBit(&m_registers.F, 6, n);
    }
    if (h != -1) {
        BitUtils::setBit(&m_registers.F, 5, h);
    }
    if (c != -1) {
        BitUtils::setBit(&m_registers.F, 4, c);
    }
}

bool CPU::checkCond() {
    const bool z = getFlagZ();
    const bool c = getFlagC();

    switch (m_currInstruction->cond) {
        case CT_NONE: return true;
        case CT_NZ: return !z;
        case CT_Z: return z;
        case CT_NC: return !c;
        case CT_C: return c;
    }

    return false;
}

const uint8_t CPU::readReg(RegisterType regType) const {
    switch (regType) {
        case RT_A:
            return m_registers.A;
        case RT_F:
            return m_registers.F;
        case RT_B:
            return m_registers.B;
        case RT_C:
            return m_registers.C;
        case RT_D:
            return m_registers.D;
        case RT_E:
            return m_registers.E;
        case RT_H:
            return m_registers.H;
        case RT_L:
            return m_registers.L;
        case RT_AF:
            return (m_registers.A << 8) | m_registers.F;
        case RT_BC:
            return (m_registers.B << 8) | m_registers.C;
        case RT_DE:
            return (m_registers.D << 8) | m_registers.E;
        case RT_HL:
            return (m_registers.H << 8) | m_registers.L;
        case RT_SP:
            return m_registers.SP;
        case RT_PC:
            return m_registers.PC;
        default:
            Debug::logErr("Unknown register type", static_cast<uint8_t>(regType));
        return 0;
    }
}

void CPU::writeReg(const RegisterType regType, const uint16_t data) {
    switch (regType) {
        case RT_A:
            m_registers.A = data & 0xFF;
            return;
        case RT_F:
            m_registers.F = data & 0xFF;
            return;
        case RT_B:
            m_registers.B = data & 0xFF;
            return;
        case RT_C:
            m_registers.C = data & 0xFF;
            return;
        case RT_D:
            m_registers.D = data & 0xFF;
            return;
        case RT_E:
            m_registers.E = data & 0xFF;
            return;
        case RT_H:
            m_registers.H = data & 0xFF;
            return;
        case RT_L:
            m_registers.L = data & 0xFF;
            return;
        case RT_AF:
            m_registers.A = (data >> 8) & 0xFF;
            m_registers.F = data & 0xFF;
            return;
        case RT_BC:
            m_registers.B = (data >> 8) & 0xFF;
            m_registers.C = data & 0xFF;
            return;
        case RT_DE:
            m_registers.D = (data >> 8) & 0xFF;
            m_registers.E = data & 0xFF;
            return;
        case RT_HL:
            m_registers.H = (data >> 8) & 0xFF;
            m_registers.L = data & 0xFF;
            return;
        case RT_SP:
            m_registers.SP = data;
            return;
        case RT_PC:
            m_registers.PC = data;
            return;
        default:
            Debug::logErr("Unknown register type", static_cast<uint8_t>(regType));
    }
}

const uint8_t CPU::fetchData8Bit(uint16_t addr) {
    NO_IMPL
}

const uint16_t CPU::fetchData16Bit(uint16_t addr) {
    NO_IMPL
}

void CPU::printInstruction() {
    const auto fmt = std::format(
        "${:04X}: {:<7} ({:02X} {:02X} {:02X}) A: {:02X} B: {:02X} C: {:02X}",
        m_registers.PC,
        magic_enum::enum_name(m_currInstruction->mnemonic),
        m_currOpcode,
        m_bus->read(m_registers.PC + 1),
        m_bus->read(m_registers.PC + 2),
        m_registers.A,
        m_registers.B,
        m_registers.C
    );
    Debug::log(fmt);
}