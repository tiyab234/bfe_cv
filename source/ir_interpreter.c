#include "ir_interpreter.h"
#include <string.h>
#include <stdio.h>
#include "ir_instructions.h"
#include "stb_ds.h"

void irinter_init(IRInterpreter* irinter) {
    irinter->inst_ptr = 0;
    irinter->mem_ptr = 0;
    for (uint64_t i = 0; i < TOTAL_MEMORY_CELLS; i++) {
        irinter->mem[i] = 0;
    }
    irinter->ir_prg = NULL;
}

void irinter_load_ir(IRInterpreter* irinter, IRInst* ir_prg) {
    irinter->ir_prg = ir_prg;
}

void irinter_interpret_ir(IRInterpreter* irinter) {
    uint64_t* stack = NULL;
    uint64_t* targets = NULL;
    uint64_t prg_len = arrlen(irinter->ir_prg);


    // This is so dumb.....................
    for (uint64_t i = 0; i < prg_len; i++) {
        arrpush(targets, 0);
    }


    // Precomputing the jumps.
    // NOTE : On bigger programs and/or slower processors it might
    // add extra delay before program execution !
    for (uint64_t i = 0, j; i < prg_len; i++) {
        if (irinter->ir_prg[i].kind == JUMP_IF_ZERO)
            arrpush(stack, i);
        else if (irinter->ir_prg[i].kind == JUMP_IF_NOT_ZERO) {
            if (arrlen(stack) == 0) {
                fprintf(stderr, "[FATAL ERROR] Unmatched ']' at byte %llu\n", i + 1);
                irinter_deinit(irinter);
                exit(EXIT_FAILURE);
            } else {
                j = arrpop(stack);
                targets[i] = j;
                targets[j] = i;
            }
        }
    }

    arrfree(stack);

    // Here he ware, finally executing the IR instructions.
    while (irinter->inst_ptr < prg_len) {
        IRInst ir_inst = irinter->ir_prg[irinter->inst_ptr];

        switch (ir_inst.kind) {
            case INCREMENT_POINTER: irinter->mem_ptr += ir_inst.operand; break;
            case DECREMENT_POINTER: irinter->mem_ptr -= ir_inst.operand; break;
            case INCREMENT_BYTE: irinter->mem[irinter->mem_ptr] += ir_inst.operand; break;
            case DECREMENT_BYTE: irinter->mem[irinter->mem_ptr] -= ir_inst.operand; break;
            case PRINT_BYTE_STDOUT:
                {
                    uint8_t repeat_count = ir_inst.operand;
                    char byte_as_char = (char)irinter->mem[irinter->mem_ptr];

                    for (uint8_t i = 0; i < repeat_count; i++) {
                        printf("%c", byte_as_char);
                        fflush(stdout); // YES, FLUSHING AFTER EVERY CHARACTER !
                    }
                }
                break;
            case READ_BYTE_STDIN:
                {
                    char input_byte;
                    // I'm too lazy to check for error after scanf usage !
                    // It's a hobby project after all, I'm the king ! :D
                    scanf("%c", &input_byte);
                    irinter->mem[irinter->mem_ptr] = (uint8_t)input_byte;
                }
                break;

            case JUMP_IF_ZERO:
                if (irinter->mem[irinter->mem_ptr] == 0)
                    irinter->inst_ptr = targets[irinter->inst_ptr];
                break;
            case JUMP_IF_NOT_ZERO:
                if (irinter->mem[irinter->mem_ptr] != 0)
                    irinter->inst_ptr = targets[irinter->inst_ptr];
                break;
        }

        irinter->inst_ptr++;
    }

    arrfree(targets);
}

void irinter_deinit(IRInterpreter* irinter) {
    arrfree(irinter->ir_prg);
}
