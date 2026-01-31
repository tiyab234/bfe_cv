#ifndef IR_GENERATOR_H
#define IR_GENERATOR_H

#include "lexer.h"
#include "ir_instructions.h"

typedef struct {
    Lexer lexer;
} IRGenerator;

void irgen_init(IRGenerator* irgen);
IRInst* irgen_generate_ir_from_raw_insts(IRGenerator* irgen, char* code);
void irgen_deinit(IRGenerator* irgen);

#endif
