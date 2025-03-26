#include "instructions.h"

Instruction instructions[0x100] = {
    [0x00] = {IM_NOP, AM_IMP},
    [0x01] = {IM_LD, AM_R_D16, RT_BC},
    [0x02] = {IM_LD, AM_MR_R, RT_BC, RT_A},

    [0x05] = {IM_DEC, AM_R, RT_B},
    [0x06] = {IM_LD, AM_R_D8, RT_B},

    [0x08] = {IM_LD, AM_A16_R, RT_NONE, RT_SP},

    [0x0A] = {IM_LD, AM_R_MR, RT_A, RT_BC},

    [0x0E] = {IM_LD, AM_R_D8, RT_C},

    //0x1X
    [0x11] = {IM_LD, AM_R_D16, RT_DE},
    [0x12] = {IM_LD, AM_MR_R, RT_DE, RT_A},
    [0x15] = {IM_DEC, AM_R, RT_D},
    [0x16] = {IM_LD, AM_R_D8, RT_D},
    [0x18] = {IM_JR, AM_D8},
    [0x1A] = {IM_LD, AM_R_MR, RT_A, RT_DE},
    [0x1E] = {IM_LD, AM_R_D8, RT_E},

    //0x2X
    [0x20] = {IM_JR, AM_D8, RT_NONE, RT_NONE, CT_NZ},
    [0x21] = {IM_LD, AM_R_D16, RT_HL},
    [0x22] = {IM_LD, AM_HLI_R, RT_HL, RT_A},
    [0x25] = {IM_DEC, AM_R, RT_H},
    [0x26] = {IM_LD, AM_R_D8, RT_H},
    [0x28] = {IM_JR, AM_D8, RT_NONE, RT_NONE, CT_Z},
    [0x2A] = {IM_LD, AM_R_HLI, RT_A, RT_HL},
    [0x2E] = {IM_LD, AM_R_D8, RT_L},

    //0x3X
    [0x30] = {IM_JR, AM_D8, RT_NONE, RT_NONE, CT_NC},
    [0x31] = {IM_LD, AM_R_D16, RT_SP},
    [0x32] = {IM_LD, AM_HLD_R, RT_HL, RT_A},
    [0x35] = {IM_DEC, AM_R, RT_HL},
    [0x36] = {IM_LD, AM_MR_D8, RT_HL},
    [0x38] = {IM_JR, AM_D8, RT_NONE, RT_NONE, CT_C},
    [0x3A] = {IM_LD, AM_R_HLD, RT_A, RT_HL},
    [0x3E] = {IM_LD, AM_R_D8, RT_A},

    //0x4X
    [0x40] = {IM_LD, AM_R_R, RT_B, RT_B},
    [0x41] = {IM_LD, AM_R_R, RT_B, RT_C},
    [0x42] = {IM_LD, AM_R_R, RT_B, RT_D},
    [0x43] = {IM_LD, AM_R_R, RT_B, RT_E},
    [0x44] = {IM_LD, AM_R_R, RT_B, RT_H},
    [0x45] = {IM_LD, AM_R_R, RT_B, RT_L},
    [0x46] = {IM_LD, AM_R_MR, RT_B, RT_HL},
    [0x47] = {IM_LD, AM_R_R, RT_B, RT_A},
    [0x48] = {IM_LD, AM_R_R, RT_C, RT_B},
    [0x49] = {IM_LD, AM_R_R, RT_C, RT_C},
    [0x4A] = {IM_LD, AM_R_R, RT_C, RT_D},
    [0x4B] = {IM_LD, AM_R_R, RT_C, RT_E},
    [0x4C] = {IM_LD, AM_R_R, RT_C, RT_H},
    [0x4D] = {IM_LD, AM_R_R, RT_C, RT_L},
    [0x4E] = {IM_LD, AM_R_MR, RT_C, RT_HL},
    [0x4F] = {IM_LD, AM_R_R, RT_C, RT_A},

    //0x5X
    [0x50] = {IM_LD, AM_R_R,  RT_D, RT_B},
    [0x51] = {IM_LD, AM_R_R,  RT_D, RT_C},
    [0x52] = {IM_LD, AM_R_R,  RT_D, RT_D},
    [0x53] = {IM_LD, AM_R_R,  RT_D, RT_E},
    [0x54] = {IM_LD, AM_R_R,  RT_D, RT_H},
    [0x55] = {IM_LD, AM_R_R,  RT_D, RT_L},
    [0x56] = {IM_LD, AM_R_MR, RT_D, RT_HL},
    [0x57] = {IM_LD, AM_R_R,  RT_D, RT_A},
    [0x58] = {IM_LD, AM_R_R,  RT_E, RT_B},
    [0x59] = {IM_LD, AM_R_R,  RT_E, RT_C},
    [0x5A] = {IM_LD, AM_R_R,  RT_E, RT_D},
    [0x5B] = {IM_LD, AM_R_R,  RT_E, RT_E},
    [0x5C] = {IM_LD, AM_R_R,  RT_E, RT_H},
    [0x5D] = {IM_LD, AM_R_R,  RT_E, RT_L},
    [0x5E] = {IM_LD, AM_R_MR, RT_E, RT_HL},
    [0x5F] = {IM_LD, AM_R_R,  RT_E, RT_A},

    //0x6X
    [0x60] = {IM_LD, AM_R_R,  RT_H, RT_B},
    [0x61] = {IM_LD, AM_R_R,  RT_H, RT_C},
    [0x62] = {IM_LD, AM_R_R,  RT_H, RT_D},
    [0x63] = {IM_LD, AM_R_R,  RT_H, RT_E},
    [0x64] = {IM_LD, AM_R_R,  RT_H, RT_H},
    [0x65] = {IM_LD, AM_R_R,  RT_H, RT_L},
    [0x66] = {IM_LD, AM_R_MR, RT_H, RT_HL},
    [0x67] = {IM_LD, AM_R_R,  RT_H, RT_A},
    [0x68] = {IM_LD, AM_R_R,  RT_L, RT_B},
    [0x69] = {IM_LD, AM_R_R,  RT_L, RT_C},
    [0x6A] = {IM_LD, AM_R_R,  RT_L, RT_D},
    [0x6B] = {IM_LD, AM_R_R,  RT_L, RT_E},
    [0x6C] = {IM_LD, AM_R_R,  RT_L, RT_H},
    [0x6D] = {IM_LD, AM_R_R,  RT_L, RT_L},
    [0x6E] = {IM_LD, AM_R_MR, RT_L, RT_HL},
    [0x6F] = {IM_LD, AM_R_R,  RT_L, RT_A},

    //0x7X
    [0x70] = {IM_LD, AM_MR_R,  RT_HL, RT_B},
    [0x71] = {IM_LD, AM_MR_R,  RT_HL, RT_C},
    [0x72] = {IM_LD, AM_MR_R,  RT_HL, RT_D},
    [0x73] = {IM_LD, AM_MR_R,  RT_HL, RT_E},
    [0x74] = {IM_LD, AM_MR_R,  RT_HL, RT_H},
    [0x75] = {IM_LD, AM_MR_R,  RT_HL, RT_L},
    [0x76] = {IM_HALT},
    [0x77] = {IM_LD, AM_MR_R,  RT_HL, RT_A},
    [0x78] = {IM_LD, AM_R_R,  RT_A, RT_B},
    [0x79] = {IM_LD, AM_R_R,  RT_A, RT_C},
    [0x7A] = {IM_LD, AM_R_R,  RT_A, RT_D},
    [0x7B] = {IM_LD, AM_R_R,  RT_A, RT_E},
    [0x7C] = {IM_LD, AM_R_R,  RT_A, RT_H},
    [0x7D] = {IM_LD, AM_R_R,  RT_A, RT_L},
    [0x7E] = {IM_LD, AM_R_MR, RT_A, RT_HL},
    [0x7F] = {IM_LD, AM_R_R,  RT_A, RT_A},

    [0xAF] = {IM_XOR, AM_R, RT_A},

    [0xC0] = {IM_RET, AM_IMP, RT_NONE, RT_NONE, CT_NZ},
    [0xC1] = {IM_POP, AM_IMP, RT_BC},
    [0xC2] = {IM_JP, AM_D16, RT_NONE, RT_NONE, CT_NZ},
    [0xC3] = {IM_JP, AM_D16},
    [0xC4] = {IM_CALL, AM_D16, RT_NONE, RT_NONE, CT_NZ},
    [0xC5] = {IM_PUSH, AM_IMP, RT_BC},
    [0xC7] = {IM_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00},
    [0xC8] = {IM_RET, AM_IMP, RT_NONE, RT_NONE, CT_Z},
    [0xC9] = {IM_RET, AM_IMP},
    [0xCA] = {IM_JP, AM_D16, RT_NONE, RT_NONE, CT_Z},
    [0xCC] = {IM_CALL, AM_D16, RT_NONE, RT_NONE, CT_Z},
    [0xCD] = {IM_CALL, AM_D16},
    [0xCF] = {IM_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x08},

    [0xD0] = {IM_RET, AM_IMP, RT_NONE, RT_NONE, CT_NC},
    [0xD1] = {IM_POP, AM_IMP, RT_DE},
    [0xD2] = {IM_JP, AM_D16, RT_NONE, RT_NONE, CT_NC},
    [0xD4] = {IM_CALL, AM_D16, RT_NONE, RT_NONE, CT_NC},
    [0xD5] = {IM_PUSH, AM_IMP, RT_DE},
    [0xD7] = {IM_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x10},
    [0xD8] = {IM_RET, AM_IMP, RT_NONE, RT_NONE, CT_C},
    [0xD9] = {IM_RETI, AM_IMP},
    [0xDA] = {IM_JP, AM_D16, RT_NONE, RT_NONE, CT_C},
    [0xDC] = {IM_CALL, AM_D16, RT_NONE, RT_NONE, CT_C},
    [0xDF] = {IM_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x18},

    //0xEX
    [0xE0] = {IM_LDH, AM_A8_R, RT_NONE, RT_A},
    [0xE1] = {IM_POP, AM_IMP, RT_HL},
    [0xE2] = {IM_LD, AM_MR_R, RT_C, RT_A}, //CHANGE IT TO LDH
    [0xE5] = {IM_PUSH, AM_IMP, RT_HL},
    [0xE7] = {IM_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x20},
    [0xE9] = {IM_JP, AM_MR, RT_HL},
    [0xEA] = {IM_LD, AM_A16_R, RT_NONE, RT_A},
    [0xEF] = {IM_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x28},

    //0xFX
    [0XF0] = {IM_LDH, AM_R_A8, RT_A},
    [0xF1] = {IM_POP, AM_IMP, RT_AF},
    [0xF2] = {IM_LD, AM_R_MR, RT_A, RT_C}, //CHANGE IT TO LDH
    [0xF3] = {IM_DI},
    [0xF5] = {IM_PUSH, AM_IMP, RT_AF},
    [0xF7] = {IM_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x30},
    [0xFA] = {IM_LD, AM_R_A16, RT_A},
    [0xFF] = {IM_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x38},
};

Instruction* getInstructionByOpcode(uint8_t opcode) {
    return &instructions[opcode];
}
