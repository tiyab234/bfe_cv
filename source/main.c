#include "ir_generator.h"
#include "ir_interpreter.h"
#include "ir_instructions.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "[FATAL ERROR] No program provided !\n");
        fprintf(stdout, "[INFO] Usage : ./bfe_cv program.bf\n");
        return EXIT_FAILURE;
    }

    char* prg_path = argv[1];

    FILE* prg_file = fopen(prg_path, "rb");
    if (!prg_file) {
        fprintf(stderr, "[FATAL ERROR] Unable to open the file !\n");
        return EXIT_FAILURE;
    }

    fseek(prg_file, 0, SEEK_END);
    unsigned long prg_buf_size = ftell(prg_file);
    fseek(prg_file, 0, SEEK_SET);

    char* prg_buf = malloc(prg_buf_size + 1);
    if (!prg_buf) {
        fclose(prg_file);
        fprintf(stderr, "[FATAL ERROR] Memory Alloc Error !\n");
        return EXIT_FAILURE;
    }

    size_t n = 0;
    int c;
    while ((c = fgetc(prg_file)) != EOF) {
        prg_buf[n++] = (char)c;
    }
    prg_buf[n] = '\0';

    fclose(prg_file);

    IRGenerator irgen;
    IRInterpreter irinter;

    irgen_init(&irgen);
    IRInst* ir_prg = irgen_generate_ir_from_raw_insts(&irgen, prg_buf);
    free(prg_buf);
    irgen_deinit(&irgen);

    irinter_init(&irinter);
    irinter_load_ir(&irinter, ir_prg);
    irinter_interpret_ir(&irinter);
    irinter_deinit(&irinter);

    return EXIT_SUCCESS;
}
