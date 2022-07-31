#include "emu.h"

#include "memory.h"
#include "registers.h"

#include <boost/format.hpp>

inline void setx(int rd, uint64_t v) {
    if (rd == 0)
        return;
    x[rd] = v;
}

void lui(uint32_t ins) {
    uint32_t rd = RD(ins);
    uint32_t imm = UIMM(ins);

    setx(rd, (int64_t)(int32_t)imm);
}

void opimm(uint32_t ins) {
    int64_t imm = IIMM(ins);
    uint32_t f = FUNCT3(ins);
    uint32_t rd = RD(ins);
    uint32_t rs1 = RS1(ins);

    switch (f) {
        case 0: // ADDI
            setx(rd, x[rs1] + imm);
            break;
        case 2: // SLTI
            setx(rd, (int64_t(x[rs1]) < imm) ? 1 : 0);
            break;
        case 3: // SLTIU
            setx(rd, (x[rs1] < (uint64_t)imm) ? 1 : 0);
            break;
        case 4: // XORI
            setx(rd, x[rs1] ^ imm);
            break;
        case 6: // ORI
            setx(rd, x[rs1] | imm);
            break;
        case 7: // XORI
            setx(rd, x[rs1] & imm);
            break;
        default:
            throw InvalidInstruction((boost::format("Unhandled funct3 %x in %x") % f % ins).str());

    }
}

void execute() 
{
    uint32_t ins = *(uint32_t *)(mem+pc);
    uint8_t op = ins & 127;

    switch (op) {
        case 0b0010011:
            opimm(ins);
            break;
        case 0b0110111:
            lui(ins);
            break;
        default:
            throw InvalidInstruction((boost::format("Unhandled op %x in %x") % op % ins).str());
    }
}