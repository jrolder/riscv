#pragma once

#include <exception>
#include <string>

// From Stackoverflow: 
// https://stackoverflow.com/questions/5814072/sign-extend-a-nine-bit-number-in-c
#define SIGNEX(v, sb) ((v) | (((v) & (1 << (sb))) ? ~((1 << (sb))-1) : 0))


#define OPCODE(x) (x & 127)
#define RD(x) ((x >> 7) & 31)
#define FUNCT3(x) ((x >> 12) & 7)
#define RS1(x) ((x >> 15) & 31) 
#define UIMM(x) (int64_t)(int32_t)(x & 0xfffff000)
#define IIMM(x) SIGNEX(uint64_t((x >> 20) & 0xfffff), 19)


class InvalidInstruction : public std::exception {
    private:
        std::string text;
    public:
        InvalidInstruction(std::string s) {
            text = s;
        }
        const char * what () const throw () {
          return text.c_str();
        }
};