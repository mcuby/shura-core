/*
   SSSSSSSSSSSSSSS hhhhhhh                                                                         CCCCCCCCCCCCC
 SS:::::::::::::::Sh:::::h                                                                      CCC::::::::::::C
S:::::SSSSSS::::::Sh:::::h                                                                    CC:::::::::::::::C
S:::::S     SSSSSSSh:::::h                                                                   C:::::CCCCCCCC::::C
S:::::S             h::::h hhhhh       uuuuuu    uuuuuu rrrrr   rrrrrrrrr   aaaaaaaaaaaaa   C:::::C       CCCCCC   ooooooooooo   rrrrr   rrrrrrrrr       eeeeeeeeeeee
S:::::S             h::::hh:::::hhh    u::::u    u::::u r::::rrr:::::::::r  a::::::::::::a C:::::C               oo:::::::::::oo r::::rrr:::::::::r    ee::::::::::::ee
 S::::SSSS          h::::::::::::::hh  u::::u    u::::u r:::::::::::::::::r aaaaaaaaa:::::aC:::::C              o:::::::::::::::or:::::::::::::::::r  e::::::eeeee:::::ee
  SS::::::SSSSS     h:::::::hhh::::::h u::::u    u::::u rr::::::rrrrr::::::r         a::::aC:::::C              o:::::ooooo:::::orr::::::rrrrr::::::re::::::e     e:::::e
    SSS::::::::SS   h::::::h   h::::::hu::::u    u::::u  r:::::r     r:::::r  aaaaaaa:::::aC:::::C              o::::o     o::::o r:::::r     r:::::re:::::::eeeee::::::e
       SSSSSS::::S  h:::::h     h:::::hu::::u    u::::u  r:::::r     rrrrrrraa::::::::::::aC:::::C              o::::o     o::::o r:::::r     rrrrrrre:::::::::::::::::e
            S:::::S h:::::h     h:::::hu::::u    u::::u  r:::::r           a::::aaaa::::::aC:::::C              o::::o     o::::o r:::::r            e::::::eeeeeeeeeee
            S:::::S h:::::h     h:::::hu:::::uuuu:::::u  r:::::r          a::::a    a:::::a C:::::C       CCCCCCo::::o     o::::o r:::::r            e:::::::e
SSSSSSS     S:::::S h:::::h     h:::::hu:::::::::::::::uur:::::r          a::::a    a:::::a  C:::::CCCCCCCC::::Co:::::ooooo:::::o r:::::r            e::::::::e
S::::::SSSSSS:::::S h:::::h     h:::::h u:::::::::::::::ur:::::r          a:::::aaaa::::::a   CC:::::::::::::::Co:::::::::::::::o r:::::r             e::::::::eeeeeeee
S:::::::::::::::SS  h:::::h     h:::::h  uu::::::::uu:::ur:::::r           a::::::::::aa:::a    CCC::::::::::::C oo:::::::::::oo  r:::::r              ee:::::::::::::e
 SSSSSSSSSSSSSSS    hhhhhhh     hhhhhhh    uuuuuuuu  uuuurrrrrrr            aaaaaaaaaa  aaaa       CCCCCCCCCCCCC   ooooooooooo    rrrrrrr                eeeeeeeeeeeeee
*/

#include "instruction_decode.h"
#include "register_file.h"
#include <iostream>
#include <cstdint>
#include <cstring>


//            AluControlBits obj;

//            obj.reg0      = dataForAlu & 0x07000000 >> 24;
//            obj.reg1      = dataForAlu & 0x38000000 >> 27;
//            obj.extencion = dataForAlu & 0xC0000000 >> 30;

//            unsigned - 00, signed - 01, flaot - 10, double - 11 (data type)

Decode commonDecodeObj;

/**
 * @brief Decode::decodeInputDataForAlu
 * @param dataForAlu
 */
void Decode::decodeInputDataForAlu(uint64_t dataForAlu)
{
    switch (dataForAlu & 0x3F) {
    case ADD:
        if (dataForAlu & 0x10000) {
            switch ((dataForAlu & 0xC0000000) >> 30) {
            case 0x00:
                commonRegsObj.w[(dataForAlu & 0x07000000) >> 24] =
                    commonlAluObj._add<uint64_t>(commonRegsObj.w[(dataForAlu & 0x38000000) >> 27], commonRegsObj.w[(dataForAlu & 0x700000000) >> 32]);
                break;
            case 0x01:
                commonRegsObj.w[(dataForAlu & 0x07000000) >> 24] =
                    static_cast<uint64_t>(commonlAluObj._add<int64_t>(static_cast<int64_t>(commonRegsObj.w[(dataForAlu & 0x38000000) >> 27]), static_cast<int64_t>(commonRegsObj.w[(dataForAlu & 0x700000000) >> 32])));
                break;
            case 0x10:
                commonRegsObj.w[(dataForAlu & 0x07000000) >> 24] =
                    static_cast<uint64_t>(commonlAluObj._add<float>(static_cast<float>(commonRegsObj.w[(dataForAlu & 0x38000000) >> 27]), static_cast<float>(commonRegsObj.w[(dataForAlu & 0x700000000) >> 32])));
                break;
            case 0x11:
                commonRegsObj.w[(dataForAlu & 0x07000000) >> 24] =
                    static_cast<uint64_t>(commonlAluObj._add<double>(static_cast<double>(commonRegsObj.w[(dataForAlu & 0x38000000) >> 27]), static_cast<double>(commonRegsObj.w[(dataForAlu & 0x700000000) >> 32])));
                break;
            }
        } else {
            switch ((dataForAlu & 0xC0000000) >> 30) {
            case 0x00:
                commonRegsObj.w[(dataForAlu & 0x07000000) >> 24] =
                    commonlAluObj._add<uint64_t>(commonRegsObj.w[(dataForAlu & 0x38000000) >> 27], (dataForAlu & 0xFFFFFFFF00000000) >> 32);
                break;
            case 0x01:
                commonRegsObj.w[(dataForAlu & 0x07000000) >> 24] =
                    static_cast<uint64_t>(commonlAluObj._add<int64_t>(static_cast<int64_t>(commonRegsObj.w[(dataForAlu & 0x38000000) >> 27]), (dataForAlu & 0xFFFFFFFF00000000) >> 32));
                break;
            case 0x10:
                commonRegsObj.w[(dataForAlu & 0x07000000) >> 24] =
                    static_cast<uint64_t>(commonlAluObj._add<float>(static_cast<float>(commonRegsObj.w[(dataForAlu & 0x38000000) >> 27]), (dataForAlu & 0xFFFFFFFF00000000) >> 32));
                break;
            case 0x11:
                commonRegsObj.w[(dataForAlu & 0x07000000) >> 24] =
                    static_cast<uint64_t>(commonlAluObj._add<double>(static_cast<double>(commonRegsObj.w[(dataForAlu & 0x38000000) >> 27]), (dataForAlu & 0xFFFFFFFF00000000) >> 32));
                break;
            }
        }
        break;
    case SUB:
        break;

    case MUL:
        break;

    case DIV :
        break;

    case MOD :
        break;

    case XOR :
        break;

    case AND :
        break;

    case OR  :
        break;

    case NOT :
        break;

    case LSHIFT :
        break;

    case RSHIFT :
        break;

    case EQUAL :
        break;

    case NEQUAL :
        break;

    case GREATER :
        break;

    case LESS :
        break;

    case GEQUAL:
        break;

    case LEQUAL :
        break;
    }
}

/**
 * @brief Decode::decodeInputData
 * @param data
 */
void Decode::decodeInputData(uint64_t data)
{

    if ((data & 0x3F) <= 0x3F) {
        decodeInputDataForAlu(data);
    }

    if (data & 0x40) {
        Svd obj;

        //for furture
        obj.var0 = (data & 0xFF);
        obj.var1 = (data & 0xFF00)   >> 8;
        obj.var2 = (data & 0xFF0000) >> 16;

        obj.extension = (data & 0x1000000)  >> 24;
        obj.registerNumber = (data & 0xE000000) >> 25;
        obj.reserve = (data & 0xF0000000) >> 28;

        uint32_t dataForReg = (data & 0xffffffff00000000) >> 32;
        commonRegsObj.wd(obj, dataForReg);
    }

}

/**
 * @brief testForDecodeForWd
 */
void testForDecodeForWd()
{
    uint64_t arrayDataForTest[24] = {

        0x8888888800000040, //register 0, -> wd r0, 0, 0x88888888
        0x9999999900000040, //register 0, -> wd r0, 0, 0x99999999
        0xAAAAAAAA01000040, //register 0, register with padding up to 64 bits, -> wd r0, 1, 0xAAAAAAAA

        0x8888888802000040, //register 1, -> wd r1, 0, 0x88888888
        0x9999999902000040, //register 1, -> wd r1, 0, 0x99999999
        0xAAAAAAAA03000040, //register 1, register with padding up to 64 bits, -> wd r1, 1, 0xAAAAAAAA

        0x8888888804000040, //register 2, -> wd r2, 0, 0x88888888
        0x9999999904000040, //register 2, -> wd r2, 0, 0x99999999
        0xAAAAAAAA05000040, //register 2, register with padding up to 64 bits, -> wd r2, 1, 0xAAAAAAAA

        0x8888888806000040, //register 3, -> wd r3, 0, 0x88888888
        0x9999999906000040, //register 3, -> wd r3, 0, 0x99999999
        0xAAAAAAAA07000040, //register 3, register with padding up to 64 bits, -> wd r3, 1, 0xAAAAAAAA

        0x8888888808000040, //register 4, -> wd r4, 0, 0x88888888
        0x9999999908000040, //register 4, -> wd r4, 0, 0x99999999
        0xAAAAAAAA09000040, //register 4, register with padding up to 64 bits, -> wd r4, 1, 0xAAAAAAAA

        0x888888880A000040, //register 5, -> wd r5, 0, 0x88888888
        0x999999990A000040, //register 5, -> wd r5, 0, 0x99999999
        0xAAAAAAAA0B000040, //register 5, register with padding up to 64 bits, -> wd r5, 1, 0xAAAAAAAA

        0x888888880C000040, //register 6, -> wd r6, 0, 0x88888888
        0x999999990C000040, //register 6, -> wd r6, 0, 0x99999999
        0xAAAAAAAA0D000040, //register 6, register with padding up to 64 bits, -> wd r6, 1, 0xAAAAAAAA

        0x888888880E000040, //register 7, -> wd r7, 0, 0x88888888
        0x999999990E000040, //register 7, -> wd r7, 0, 0x99999999
        0xAAAAAAAA0F000040, //register 7, register with padding up to 64 bits, -> wd r7, 1, 0xAAAAAAAA
    };

    for (uint64_t number : arrayDataForTest) {
        commonDecodeObj.decodeInputData(number);

        std::cout << "---------------------------------" <<  "\n";

        std::cout << "w0 = " << std::hex << commonRegsObj.w[0] <<  "\n"
                  << "w1 = " << std::hex << commonRegsObj.w[1] <<  "\n"
                  << "w2 = " << std::hex << commonRegsObj.w[2] <<  "\n"
                  << "w3 = " << std::hex << commonRegsObj.w[3] <<  "\n"
                  << "w4 = " << std::hex << commonRegsObj.w[4] <<  "\n"
                  << "w5 = " << std::hex << commonRegsObj.w[5] <<  "\n"
                  << "w6 = " << std::hex << commonRegsObj.w[6] <<  "\n"
                  << "w7 = " << std::hex << commonRegsObj.w[7] <<  "\n";

        std::cout << "---------------------------------" <<  "\n";
    }
}

void makeForRegisters(uint32_t numberOfRegister, bool pad, uint64_t data)
{
    if (pad) {
        uint64_t t0 = commonlAluObj._lshift<uint64_t>(data, 32);
        commonRegsObj.w[numberOfRegister] = commonlAluObj._or<uint64_t>(commonRegsObj.w[numberOfRegister], t0);;
    } else {
        commonRegsObj.w[numberOfRegister] = data;
    }
}


void testAluAddUint32(void)
{
    uint32_t r0_u32 = 0;
    uint32_t r1_u32 = 1;
    uint32_t r2_u32 = 2;
    uint32_t r3_u32 = 3;
    uint32_t r4_u32 = 4;
    uint32_t r5_u32 = 5;
    uint32_t r6_u32 = 6;
    uint32_t r7_u32 = 7;

    makeForRegisters(r0_u32, 0, r0_u32);
    std::cout << "w0 = " << std::hex << commonRegsObj.w[r0_u32] <<  "\n";

    makeForRegisters(r1_u32, 0, r1_u32);
    std::cout << "w1 = " << std::hex << commonRegsObj.w[r1_u32] <<  "\n";

    makeForRegisters(r2_u32, 0, r2_u32);
    std::cout << "w2 = " << std::hex << commonRegsObj.w[r2_u32] <<  "\n";

    makeForRegisters(r3_u32, 0, r3_u32);
    std::cout << "w3 = " << std::hex << commonRegsObj.w[r3_u32] <<  "\n";

    makeForRegisters(r4_u32, 0, r4_u32);
    std::cout << "w4 = " << std::hex << commonRegsObj.w[r4_u32] <<  "\n";

    makeForRegisters(r5_u32, 0, r5_u32);
    std::cout << "w5 = " << std::hex << commonRegsObj.w[r5_u32] <<  "\n";

    makeForRegisters(r6_u32, 0, r6_u32);
    std::cout << "w6 = " << std::hex << commonRegsObj.w[r6_u32] <<  "\n";

    makeForRegisters(r7_u32, 0, r7_u32);
    std::cout << "w7 = " << std::hex << commonRegsObj.w[r7_u32] <<  "\n";

    //r0/r0
    uint64_t add_array_r0[8] = {
        0x0000000100000000,
        0x0000000100000000,
        0x0000000100000000,
        0x0000000100000000,
        0x0000000100000000,
        0x0000000100000000,
        0x0000000100000000,
        0x0000000100000000
    };

    //r1/r1
    uint64_t add_array_r1[8] = {
        0x0000000109000000,
        0x0000000109000000,
        0x0000000109000000,
        0x0000000109000000,
        0x0000000109000000,
        0x0000000109000000,
        0x0000000109000000,
        0x0000000109000000
    };

    //r2/r2
    uint64_t add_array_r2[8] = {
        0x0000000112000000,
        0x0000000112000000,
        0x0000000112000000,
        0x0000000112000000,
        0x0000000112000000,
        0x0000000112000000,
        0x0000000112000000,
        0x0000000112000000
    };

    //r3/r3
    uint64_t add_array_r3[8] = {
        0x000000011B000000,
        0x000000011B000000,
        0x000000011B000000,
        0x000000011B000000,
        0x000000011B000000,
        0x000000011B000000,
        0x000000011B000000,
        0x000000011B000000
    };

    //r4/r4
    uint64_t add_array_r4[8] = {
        0x000000024000000,
        0x000000024000000,
        0x000000024000000,
        0x000000024000000,
        0x000000024000000,
        0x000000024000000,
        0x000000024000000,
        0x000000024000000
    };

    //r5/r5
    uint64_t add_array_r5[8] = {
        0x000000012D000000,

        0x000000012D000000,
        0x000000012D000000,
        0x000000012D000000,
        0x000000012D000000,
        0x000000012D000000,
        0x000000012D000000,
        0x000000012D000000
    };

    //r6/r6
    uint64_t add_array_r6[8] = {
        0x0000000136000000,
        0x0000000136000000,
        0x0000000136000000,
        0x0000000136000000,
        0x0000000136000000,
        0x0000000136000000,
        0x0000000136000000,
        0x0000000136000000
    };

    //r7/r7
    uint64_t add_array_r7[8] = {
        0x000000013F000000,
        0x000000013F000000,
        0x000000013F000000,
        0x000000013F000000,
        0x000000013F000000,
        0x000000013F000000,
        0x000000013F000000,
        0x000000013F000000
    };

    for (uint64_t number : add_array_r0) {
        commonDecodeObj.decodeInputData(number);

        std::cout << "---------------------------------"       <<  "\n";

        std::cout << "w0 = " << std::hex << commonRegsObj.w[0] <<  "\n"
                  << "w1 = " << std::hex << commonRegsObj.w[1] <<  "\n"
                  << "w2 = " << std::hex << commonRegsObj.w[2] <<  "\n"
                  << "w3 = " << std::hex << commonRegsObj.w[3] <<  "\n"
                  << "w4 = " << std::hex << commonRegsObj.w[4] <<  "\n"
                  << "w5 = " << std::hex << commonRegsObj.w[5] <<  "\n"
                  << "w6 = " << std::hex << commonRegsObj.w[6] <<  "\n"
                  << "w7 = " << std::hex << commonRegsObj.w[7] <<  "\n";

        std::cout << "---------------------------------"       <<  "\n";
    }

    for (uint64_t number : add_array_r1) {
        commonDecodeObj.decodeInputData(number);

        std::cout << "---------------------------------"       <<  "\n";

        std::cout << "w0 = " << std::hex << commonRegsObj.w[0] <<  "\n"
                  << "w1 = " << std::hex << commonRegsObj.w[1] <<  "\n"
                  << "w2 = " << std::hex << commonRegsObj.w[2] <<  "\n"
                  << "w3 = " << std::hex << commonRegsObj.w[3] <<  "\n"
                  << "w4 = " << std::hex << commonRegsObj.w[4] <<  "\n"
                  << "w5 = " << std::hex << commonRegsObj.w[5] <<  "\n"
                  << "w6 = " << std::hex << commonRegsObj.w[6] <<  "\n"
                  << "w7 = " << std::hex << commonRegsObj.w[7] <<  "\n";

        std::cout << "---------------------------------"       <<  "\n";
    }

    for (uint64_t number : add_array_r2) {
        commonDecodeObj.decodeInputData(number);

        std::cout << "---------------------------------"       <<  "\n";

        std::cout << "w0 = " << std::hex << commonRegsObj.w[0] <<  "\n"
                  << "w1 = " << std::hex << commonRegsObj.w[1] <<  "\n"
                  << "w2 = " << std::hex << commonRegsObj.w[2] <<  "\n"
                  << "w3 = " << std::hex << commonRegsObj.w[3] <<  "\n"
                  << "w4 = " << std::hex << commonRegsObj.w[4] <<  "\n"
                  << "w5 = " << std::hex << commonRegsObj.w[5] <<  "\n"
                  << "w6 = " << std::hex << commonRegsObj.w[6] <<  "\n"
                  << "w7 = " << std::hex << commonRegsObj.w[7] <<  "\n";

        std::cout << "---------------------------------"       <<  "\n";
    }

    for (uint64_t number : add_array_r3) {
        commonDecodeObj.decodeInputData(number);

        std::cout << "---------------------------------"       <<  "\n";

        std::cout << "w0 = " << std::hex << commonRegsObj.w[0] <<  "\n"
                  << "w1 = " << std::hex << commonRegsObj.w[1] <<  "\n"
                  << "w2 = " << std::hex << commonRegsObj.w[2] <<  "\n"
                  << "w3 = " << std::hex << commonRegsObj.w[3] <<  "\n"
                  << "w4 = " << std::hex << commonRegsObj.w[4] <<  "\n"
                  << "w5 = " << std::hex << commonRegsObj.w[5] <<  "\n"
                  << "w6 = " << std::hex << commonRegsObj.w[6] <<  "\n"
                  << "w7 = " << std::hex << commonRegsObj.w[7] <<  "\n";

        std::cout << "---------------------------------"       <<  "\n";
    }

    for (uint64_t number : add_array_r4) {
        commonDecodeObj.decodeInputData(number);

        std::cout << "---------------------------------"       <<  "\n";

        std::cout << "w0 = " << std::hex << commonRegsObj.w[0] <<  "\n"
                  << "w1 = " << std::hex << commonRegsObj.w[1] <<  "\n"
                  << "w2 = " << std::hex << commonRegsObj.w[2] <<  "\n"
                  << "w3 = " << std::hex << commonRegsObj.w[3] <<  "\n"
                  << "w4 = " << std::hex << commonRegsObj.w[4] <<  "\n"
                  << "w5 = " << std::hex << commonRegsObj.w[5] <<  "\n"
                  << "w6 = " << std::hex << commonRegsObj.w[6] <<  "\n"
                  << "w7 = " << std::hex << commonRegsObj.w[7] <<  "\n";

        std::cout << "---------------------------------"       <<  "\n";
    }


    for (uint64_t number : add_array_r5) {
        commonDecodeObj.decodeInputData(number);

        std::cout << "---------------------------------"       <<  "\n";

        std::cout << "w0 = " << std::hex << commonRegsObj.w[0] <<  "\n"
                  << "w1 = " << std::hex << commonRegsObj.w[1] <<  "\n"
                  << "w2 = " << std::hex << commonRegsObj.w[2] <<  "\n"
                  << "w3 = " << std::hex << commonRegsObj.w[3] <<  "\n"
                  << "w4 = " << std::hex << commonRegsObj.w[4] <<  "\n"
                  << "w5 = " << std::hex << commonRegsObj.w[5] <<  "\n"
                  << "w6 = " << std::hex << commonRegsObj.w[6] <<  "\n"
                  << "w7 = " << std::hex << commonRegsObj.w[7] <<  "\n";

        std::cout << "---------------------------------"       <<  "\n";
    }

    for (uint64_t number : add_array_r6) {
        commonDecodeObj.decodeInputData(number);

        std::cout << "---------------------------------"       <<  "\n";

        std::cout << "w0 = " << std::hex << commonRegsObj.w[0] <<  "\n"
                  << "w1 = " << std::hex << commonRegsObj.w[1] <<  "\n"
                  << "w2 = " << std::hex << commonRegsObj.w[2] <<  "\n"
                  << "w3 = " << std::hex << commonRegsObj.w[3] <<  "\n"
                  << "w4 = " << std::hex << commonRegsObj.w[4] <<  "\n"
                  << "w5 = " << std::hex << commonRegsObj.w[5] <<  "\n"
                  << "w6 = " << std::hex << commonRegsObj.w[6] <<  "\n"
                  << "w7 = " << std::hex << commonRegsObj.w[7] <<  "\n";

        std::cout << "---------------------------------"       <<  "\n";
    }

    for (uint64_t number : add_array_r7) {
        commonDecodeObj.decodeInputData(number);

        std::cout << "---------------------------------"       <<  "\n";

        std::cout << "w0 = " << std::hex << commonRegsObj.w[0] <<  "\n"
                  << "w1 = " << std::hex << commonRegsObj.w[1] <<  "\n"
                  << "w2 = " << std::hex << commonRegsObj.w[2] <<  "\n"
                  << "w3 = " << std::hex << commonRegsObj.w[3] <<  "\n"
                  << "w4 = " << std::hex << commonRegsObj.w[4] <<  "\n"
                  << "w5 = " << std::hex << commonRegsObj.w[5] <<  "\n"
                  << "w6 = " << std::hex << commonRegsObj.w[6] <<  "\n"
                  << "w7 = " << std::hex << commonRegsObj.w[7] <<  "\n";

        std::cout << "---------------------------------"       <<  "\n";
    }
}


void testAluAddInt32(void)
{
    int64_t r0_i64 = -10;
    int64_t r1_i64 = -11;
    int64_t r2_i64 = -12;
    int64_t r3_i64 = -13;
    int64_t r4_i64 = -14;
    int64_t r5_i64 = -15;
    int64_t r6_i64 = -16;
    int64_t r7_i64 = -17;

    int64_t t_r0 = 0;
    int64_t t_r1 = 0;
    int64_t t_r2 = 0;
    int64_t t_r3 = 0;
    int64_t t_r4 = 0;
    int64_t t_r5 = 0;
    int64_t t_r6 = 0;
    int64_t t_r7 = 0;


    uint64_t r0_u64 = 0;
    uint64_t r1_u64 = 0;
    uint64_t r2_u64 = 0;
    uint64_t r3_u64 = 0;
    uint64_t r4_u64 = 0;
    uint64_t r5_u64 = 0;
    uint64_t r6_u64 = 0;
    uint64_t r7_u64 = 0;

    std::memcpy(&r0_u64, &r0_i64, sizeof(uint64_t));
    std::memcpy(&r1_u64, &r1_i64, sizeof(uint64_t));
    std::memcpy(&r2_u64, &r2_i64, sizeof(uint64_t));
    std::memcpy(&r3_u64, &r3_i64, sizeof(uint64_t));
    std::memcpy(&r4_u64, &r4_i64, sizeof(uint64_t));
    std::memcpy(&r5_u64, &r5_i64, sizeof(uint64_t));
    std::memcpy(&r6_u64, &r6_i64, sizeof(uint64_t));
    std::memcpy(&r7_u64, &r7_i64, sizeof(uint64_t));

    makeForRegisters(0, 0, r0_u64);
    std::cout << "w0 = " << std::hex << commonRegsObj.w[0] <<  "\n";

    makeForRegisters(1, 0, r1_u64);
    std::cout << "w1 = " << std::hex << commonRegsObj.w[1] <<  "\n";

    makeForRegisters(2, 0, r2_u64);
    std::cout << "w2 = " << std::hex << commonRegsObj.w[2] <<  "\n";

    makeForRegisters(3, 0, r3_u64);
    std::cout << "w3 = " << std::hex << commonRegsObj.w[3] <<  "\n";

    makeForRegisters(4, 0, r4_u64);
    std::cout << "w4 = " << std::hex << commonRegsObj.w[4] <<  "\n";

    makeForRegisters(5, 0, r5_u64);
    std::cout << "w5 = " << std::hex << commonRegsObj.w[5] <<  "\n";

    makeForRegisters(6, 0, r6_u64);
    std::cout << "w6 = " << std::hex << commonRegsObj.w[6] <<  "\n";

    makeForRegisters(7, 0, r7_u64);
    std::cout << "w7 = " << std::hex << commonRegsObj.w[7] <<  "\n";

    //r0/r0
    uint64_t add_array_r0[8] = {
        0x0000000140000000,
        0x0000000140000000,
        0x0000000140000000,
        0x0000000140000000,
        0x0000000140000000,
        0x0000000140000000,
        0x0000000140000000,
        0x0000000140000000
    };

    //r1/r1
    uint64_t add_array_r1[8] = {
        0x0000000109000000,
        0x0000000109000000,
        0x0000000109000000,
        0x0000000109000000,
        0x0000000109000000,
        0x0000000109000000,
        0x0000000109000000,
        0x0000000109000000
    };

    //r2/r2
    uint64_t add_array_r2[8] = {
        0x0000000112000000,
        0x0000000112000000,
        0x0000000112000000,
        0x0000000112000000,
        0x0000000112000000,
        0x0000000112000000,
        0x0000000112000000,
        0x0000000112000000
    };

    //r3/r3
    uint64_t add_array_r3[8] = {
        0x000000011B000000,
        0x000000011B000000,
        0x000000011B000000,
        0x000000011B000000,
        0x000000011B000000,
        0x000000011B000000,
        0x000000011B000000,
        0x000000011B000000
    };

    //r4/r4
    uint64_t add_array_r4[8] = {
        0x000000024000000,
        0x000000024000000,
        0x000000024000000,
        0x000000024000000,
        0x000000024000000,
        0x000000024000000,
        0x000000024000000,
        0x000000024000000
    };

    //r5/r5
    uint64_t add_array_r5[8] = {
        0x000000012D000000,
        0x000000012D000000,
        0x000000012D000000,
        0x000000012D000000,
        0x000000012D000000,
        0x000000012D000000,
        0x000000012D000000,
        0x000000012D000000
    };

    //r6/r6
    uint64_t add_array_r6[8] = {
        0x0000000136000000,
        0x0000000136000000,
        0x0000000136000000,
        0x0000000136000000,
        0x0000000136000000,
        0x0000000136000000,
        0x0000000136000000,
        0x0000000136000000
    };

    //r7/r7
    uint64_t add_array_r7[8] = {
        0x000000013F000000,
        0x000000013F000000,
        0x000000013F000000,
        0x000000013F000000,
        0x000000013F000000,
        0x000000013F000000,
        0x000000013F000000,
        0x000000013F000000
    };

    for (uint64_t number : add_array_r0) {
        commonDecodeObj.decodeInputData(number);

        std::cout << "---------------------------------"       <<  "\n";

        std::cout << "w0 = " << std::hex << commonRegsObj.w[0] <<  "\n"
                  << "w1 = " << std::hex << commonRegsObj.w[1] <<  "\n"
                  << "w2 = " << std::hex << commonRegsObj.w[2] <<  "\n"
                  << "w3 = " << std::hex << commonRegsObj.w[3] <<  "\n"
                  << "w4 = " << std::hex << commonRegsObj.w[4] <<  "\n"
                  << "w5 = " << std::hex << commonRegsObj.w[5] <<  "\n"
                  << "w6 = " << std::hex << commonRegsObj.w[6] <<  "\n"
                  << "w7 = " << std::hex << commonRegsObj.w[7] <<  "\n";

        std::cout << "---------------------------------"       <<  "\n";
    }

    std::memcpy(&t_r0, &commonRegsObj.w[0], sizeof(uint64_t));
    std::cout << "w0 = " << std::dec << t_r0 <<  "\n";

    for (uint64_t number : add_array_r1) {
        commonDecodeObj.decodeInputData(number);

        std::cout << "---------------------------------"       <<  "\n";

        std::cout << "w0 = " << std::hex << commonRegsObj.w[0] <<  "\n"
                  << "w1 = " << std::hex << commonRegsObj.w[1] <<  "\n"
                  << "w2 = " << std::hex << commonRegsObj.w[2] <<  "\n"
                  << "w3 = " << std::hex << commonRegsObj.w[3] <<  "\n"
                  << "w4 = " << std::hex << commonRegsObj.w[4] <<  "\n"
                  << "w5 = " << std::hex << commonRegsObj.w[5] <<  "\n"
                  << "w6 = " << std::hex << commonRegsObj.w[6] <<  "\n"
                  << "w7 = " << std::hex << commonRegsObj.w[7] <<  "\n";

        std::cout << "---------------------------------"       <<  "\n";
    }

    std::memcpy(&t_r1, &commonRegsObj.w[1], sizeof(uint64_t));
    std::cout << "w1 = " << std::dec << t_r1 <<  "\n";

    for (uint64_t number : add_array_r2) {
        commonDecodeObj.decodeInputData(number);

        std::cout << "---------------------------------"       <<  "\n";

        std::cout << "w0 = " << std::hex << commonRegsObj.w[0] <<  "\n"
                  << "w1 = " << std::hex << commonRegsObj.w[1] <<  "\n"
                  << "w2 = " << std::hex << commonRegsObj.w[2] <<  "\n"
                  << "w3 = " << std::hex << commonRegsObj.w[3] <<  "\n"
                  << "w4 = " << std::hex << commonRegsObj.w[4] <<  "\n"
                  << "w5 = " << std::hex << commonRegsObj.w[5] <<  "\n"
                  << "w6 = " << std::hex << commonRegsObj.w[6] <<  "\n"
                  << "w7 = " << std::hex << commonRegsObj.w[7] <<  "\n";

        std::cout << "---------------------------------"       <<  "\n";
    }

    std::memcpy(&t_r2, &commonRegsObj.w[2], sizeof(uint64_t));
    std::cout << "w2 = " << std::dec << t_r2 <<  "\n";

    for (uint64_t number : add_array_r3) {
        commonDecodeObj.decodeInputData(number);

        std::cout << "---------------------------------"       <<  "\n";

        std::cout << "w0 = " << std::hex << commonRegsObj.w[0] <<  "\n"
                  << "w1 = " << std::hex << commonRegsObj.w[1] <<  "\n"
                  << "w2 = " << std::hex << commonRegsObj.w[2] <<  "\n"
                  << "w3 = " << std::hex << commonRegsObj.w[3] <<  "\n"
                  << "w4 = " << std::hex << commonRegsObj.w[4] <<  "\n"
                  << "w5 = " << std::hex << commonRegsObj.w[5] <<  "\n"
                  << "w6 = " << std::hex << commonRegsObj.w[6] <<  "\n"
                  << "w7 = " << std::hex << commonRegsObj.w[7] <<  "\n";

        std::cout << "---------------------------------"       <<  "\n";
    }

    std::memcpy(&t_r3, &commonRegsObj.w[3], sizeof(uint64_t));
    std::cout << "w3 = " << std::dec << t_r3 <<  "\n";

    for (uint64_t number : add_array_r4) {
        commonDecodeObj.decodeInputData(number);

        std::cout << "---------------------------------"       <<  "\n";

        std::cout << "w0 = " << std::hex << commonRegsObj.w[0] <<  "\n"
                  << "w1 = " << std::hex << commonRegsObj.w[1] <<  "\n"
                  << "w2 = " << std::hex << commonRegsObj.w[2] <<  "\n"
                  << "w3 = " << std::hex << commonRegsObj.w[3] <<  "\n"
                  << "w4 = " << std::hex << commonRegsObj.w[4] <<  "\n"
                  << "w5 = " << std::hex << commonRegsObj.w[5] <<  "\n"
                  << "w6 = " << std::hex << commonRegsObj.w[6] <<  "\n"
                  << "w7 = " << std::hex << commonRegsObj.w[7] <<  "\n";

        std::cout << "---------------------------------"       <<  "\n";
    }

    std::memcpy(&t_r4, &commonRegsObj.w[4], sizeof(uint64_t));
    std::cout << "w4 = " << std::dec << t_r4 <<  "\n";

    for (uint64_t number : add_array_r5) {
        commonDecodeObj.decodeInputData(number);

        std::cout << "---------------------------------"       <<  "\n";

        std::cout << "w0 = " << std::hex << commonRegsObj.w[0] <<  "\n"
                  << "w1 = " << std::hex << commonRegsObj.w[1] <<  "\n"
                  << "w2 = " << std::hex << commonRegsObj.w[2] <<  "\n"
                  << "w3 = " << std::hex << commonRegsObj.w[3] <<  "\n"
                  << "w4 = " << std::hex << commonRegsObj.w[4] <<  "\n"
                  << "w5 = " << std::hex << commonRegsObj.w[5] <<  "\n"
                  << "w6 = " << std::hex << commonRegsObj.w[6] <<  "\n"
                  << "w7 = " << std::hex << commonRegsObj.w[7] <<  "\n";

        std::cout << "---------------------------------"       <<  "\n";
    }

    std::memcpy(&t_r5, &commonRegsObj.w[5], sizeof(uint64_t));
    std::cout << "w5 = " << std::dec << t_r5 <<  "\n";

    for (uint64_t number : add_array_r6) {
        commonDecodeObj.decodeInputData(number);

        std::cout << "---------------------------------"       <<  "\n";

        std::cout << "w0 = " << std::hex << commonRegsObj.w[0] <<  "\n"
                  << "w1 = " << std::hex << commonRegsObj.w[1] <<  "\n"
                  << "w2 = " << std::hex << commonRegsObj.w[2] <<  "\n"
                  << "w3 = " << std::hex << commonRegsObj.w[3] <<  "\n"
                  << "w4 = " << std::hex << commonRegsObj.w[4] <<  "\n"
                  << "w5 = " << std::hex << commonRegsObj.w[5] <<  "\n"
                  << "w6 = " << std::hex << commonRegsObj.w[6] <<  "\n"
                  << "w7 = " << std::hex << commonRegsObj.w[7] <<  "\n";

        std::cout << "---------------------------------"       <<  "\n";
    }

    std::memcpy(&t_r6, &commonRegsObj.w[6], sizeof(uint64_t));
    std::cout << "w6 = " << std::dec << t_r6 <<  "\n";

    for (uint64_t number : add_array_r7) {
        commonDecodeObj.decodeInputData(number);

        std::cout << "---------------------------------"       <<  "\n";

        std::cout << "w0 = " << std::hex << commonRegsObj.w[0] <<  "\n"
                  << "w1 = " << std::hex << commonRegsObj.w[1] <<  "\n"
                  << "w2 = " << std::hex << commonRegsObj.w[2] <<  "\n"
                  << "w3 = " << std::hex << commonRegsObj.w[3] <<  "\n"
                  << "w4 = " << std::hex << commonRegsObj.w[4] <<  "\n"
                  << "w5 = " << std::hex << commonRegsObj.w[5] <<  "\n"
                  << "w6 = " << std::hex << commonRegsObj.w[6] <<  "\n"
                  << "w7 = " << std::hex << commonRegsObj.w[7] <<  "\n";

        std::cout << "---------------------------------"       <<  "\n";
    }

    std::memcpy(&t_r7, &commonRegsObj.w[7], sizeof(uint64_t));
    std::cout << "w7 = " << std::dec << t_r7 <<  "\n";

}
