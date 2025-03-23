#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include <cstdint>

enum AddrMode{
    AM_IMP,
    AM_R_D16,
    AM_R_R,
    AM_MR_R,
    AM_R,
    AM_R_D8,
    AM_R_MR,
    AM_R_HLI,
    AM_R_HLD,
    AM_HLI_R,
    AM_HLD_R,
    AM_R_A8,
    AM_A8_R,
    AM_HL_SPR,
    AM_D16,
    AM_D8,
    AM_D16_R,
    AM_MR_D8,
    AM_MR,
    AM_A16_R,
    AM_R_A16
};

enum  RegisterType {
    RT_NONE,
    RT_A,
    RT_F,
    RT_B,
    RT_C,
    RT_D,
    RT_E,
    RT_H,
    RT_L,
    RT_AF,
    RT_BC,
    RT_DE,
    RT_HL,
    RT_SP,
    RT_PC
};

enum InstructionMnemonic {
    IM_NONE,
    IM_NOP,
    IM_LD,
    IM_INC,
    IM_DEC,
    IM_RLCA,
    IM_ADD,
    IM_RRCA,
    IM_STOP,
    IM_RLA,
    IM_JR,
    IM_RRA,
    IM_DAA,
    IM_CPL,
    IM_SCF,
    IM_CCF,
    IM_HALT,
    IM_ADC,
    IM_SUB,
    IM_SBC,
    IM_AND,
    IM_XOR,
    IM_OR,
    IM_CP,
    IM_POP,
    IM_JP,
    IM_PUSH,
    IM_RET,
    IM_CB,
    IM_CALL,
    IM_RETI,
    IM_LDH,
    IM_JPHL,
    IM_DI,
    IM_EI,
    IM_RST,
    IM_ERR,
    //CB instructions...
    IM_RLC,
    IM_RRC,
    IM_RL,
    IM_RR,
    IM_SLA,
    IM_SRA,
    IM_SWAP,
    IM_SRL,
    IM_BIT,
    IM_RES,
    IM_SET,
    IM_COUNT
};

enum CondType {
    CT_NONE, CT_NZ, CT_Z, CT_NC, CT_C
} ;

struct Instruction {
    InstructionMnemonic mnemonic;
    AddrMode addrMode;
    RegisterType reg1;
    RegisterType reg2;
    CondType cond;
    uint8_t parameters;
};

Instruction* getInstructionByOpcode(uint8_t opcode);

#endif //INSTRUCTIONS_H
