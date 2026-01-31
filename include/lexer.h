/*

Copyright (c) 2026 - Yann BOYER

*/
#ifndef LEXER_H
#define LEXER_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint64_t code_len;
    uint64_t code_pos;
    char* code; // Empty dynamic array of char storing BF insts !
} Lexer;

void lexer_init(Lexer* lex);
void lexer_fill(Lexer* lex, char* code);
bool lexer_is_valid_command(char p_inst);
char lexer_next(Lexer* lex);
void lexer_deinit(Lexer* lex);

#endif
