/*

Copyright (c) 2026 - Yann BOYER

*/
#ifndef IR_INSTRUCTIONS_H
#define IR_INSTRUCTIONS_H

#include <stdint.h>

typedef enum {
    INCREMENT_POINTER = '>',
    DECREMENT_POINTER = '<',
    INCREMENT_BYTE = '+',
    DECREMENT_BYTE = '-',
    PRINT_BYTE_STDOUT = '.',
    READ_BYTE_STDIN = ',',
    JUMP_IF_ZERO = '[',
    JUMP_IF_NOT_ZERO = ']',
} IRInstKind;

typedef struct {
    IRInstKind kind;
    uint8_t operand; // The operand is not a required field !
} IRInst;

#endif
