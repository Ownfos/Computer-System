#pragma once

namespace ownfos
{
    class Constants
    {
    public:
        using Bits = const unsigned int;

        static Bits INSTRUCTION_BITMASK           = 0xff000000;
        static Bits SINGLE_OPERAND_BITMASK        = 0x00ffffff;
        static Bits DOUBLE_OPERAND_FIRST_BITMASK  = 0x00fff000;
        static Bits DOUBLE_OPERAND_SECOND_BITMASK = 0x00000fff;
        static Bits MOVE_BIT                      = 0x11000000;
        static Bits JUMP_BIT                      = 0x22000000;
        static Bits LOAD_BIT                      = 0x33000000;
        static Bits STORE_BIT                     = 0x44000000;
        static Bits ADD_BIT                       = 0x55000000;
    };
}