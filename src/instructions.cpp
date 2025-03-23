#include "instructions.h"

Instruction instructions[0x100] = {
    [0x00] = {IM_NOP, AM_IMP},

    [0x05] = {IM_DEC, AM_R, RT_B},

    [0x0E] = {IM_LD, AM_R_D8, RT_C},

    [0xAF] = {IM_XOR, AM_R, RT_A},

    [0xC3] = {IM_JP, AM_D16},

    [0xF3] = {IM_DI}
};

Instruction* getInstructionByOpcode(uint8_t opcode) {
    return &instructions[opcode];
}
