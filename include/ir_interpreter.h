#ifndef IR_INTERPRETER_H
#define IR_INTERPRETER_H

#include "ir_instructions.h"
#include <stdint.h>

#define TOTAL_MEMORY_CELLS 100000

typedef struct {
    uint64_t inst_ptr;
    uint64_t mem_ptr;
    uint8_t mem[TOTAL_MEMORY_CELLS];
    IRInst* ir_prg;
} IRInterpreter;

void irinter_init(IRInterpreter* irinter);
void irinter_load_ir(IRInterpreter* irinter, IRInst* ir_prg);
void irinter_interpret_ir(IRInterpreter* irinter);
void irinter_deinit(IRInterpreter* irinter);

#endif
