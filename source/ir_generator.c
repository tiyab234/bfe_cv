#include "ir_generator.h"
#include <string.h>
#include <stdio.h>
#include "stb_ds.h"

void irgen_init(IRGenerator* irgen) {
    lexer_init(&irgen->lexer);
}

IRInst* irgen_generate_ir_from_raw_insts(IRGenerator* irgen, char* code) {
    lexer_fill(&irgen->lexer, code);

    char c = lexer_next(&irgen->lexer);

    IRInst* tmp_prg = NULL;

    while (c) {
        IRInst ir_inst;
        switch (c) {
            case '>':
            case '<':
            case '+':
            case '-':
            case '.':
                {
                    // We already have one occurrence of the inst.
                    uint8_t i_combo = 1;
                    char s = lexer_next(&irgen->lexer);

                    while (c == s) {
                        i_combo++;
                        s = lexer_next(&irgen->lexer);
                    }

                    ir_inst = (IRInst) { (IRInstKind)c, i_combo };

                    c = s;
                }
                break;
            case ',':
            case '[':
            case ']':
                ir_inst = (IRInst) { (IRInstKind)c, 0 };
                c = lexer_next(&irgen->lexer);
                break;
            default: continue;
        }

        arrpush(tmp_prg, ir_inst);
    }

    if (arrlen(tmp_prg) == 0) {
        irgen_deinit(irgen);
        fprintf(stderr, "[FATAL ERROR] This is not a BF program !\n");
        exit(EXIT_FAILURE);
    }

    return tmp_prg;
}

void irgen_deinit(IRGenerator* irgen) {
    lexer_deinit(&irgen->lexer);
}
