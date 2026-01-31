/*

Copyright (c) 2026 - Yann BOYER

*/
#include "lexer.h"
#include <string.h>
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"
#include <stdio.h>

void lexer_init(Lexer* lex) {
    lex->code_len = 0;
    lex->code_pos = 0;
    lex->code = NULL;
}

void lexer_fill(Lexer* lex, char* code) {
    for (uint64_t i = 0; i < strlen(code); i++) {
        arrpush(lex->code, code[i]);
    }
    lex->code_len = arrlen(lex->code);
}

bool lexer_is_valid_command(char p_inst) {
    char* VALID_INSTS = "><+-.,[]"; // 8 Valid instructions.
    if (strchr(VALID_INSTS, p_inst) != NULL)
        return true;
    else
        return false;
}

char lexer_next(Lexer* lex) {
    while (lex->code_pos < lex->code_len && !lexer_is_valid_command(lex->code[lex->code_pos]))
        lex->code_pos++;

    if (lex->code_pos >= lex->code_len) return 0; // EOF.
    return lex->code[lex->code_pos++];
}

void lexer_deinit(Lexer* lex) {
    arrfree(lex->code);
}


