#include "command.h"
#include "coder.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int encode_file(const char* in_file_name, const char* out_file_name)
{
    uint32_t code_point;
    CodeUnit code_units;
    FILE* in_file = fopen(in_file_name, "r");
    if (!in_file) {
        printf("Failed to read file located at %s\n", in_file_name);
        return -1;
    }
    FILE* out_file = fopen(out_file_name, "wb");
    if (!out_file) {
        printf("Failed to create file located at %s\n", out_file_name);
        return -1;
    }
    while (!feof(in_file)) {
        fscanf(in_file, "%" SCNx32, &code_point);
        encode(code_point, &code_units);
        write_code_unit(out_file, &code_units);
    }
    fclose(in_file);
    fclose(out_file);
    return 0;
}

int decode_file(const char* in_file_name, const char* out_file_name)
{
    CodeUnit code_units;
    FILE* in_file = fopen(in_file_name, "rb");
    if (!in_file) {
        printf("Failed to read file located at %s\n", in_file_name);
        return -1;
    }
    FILE* out_file = fopen(out_file_name, "w");
    if (!out_file) {
        printf("Failed to create file located at %s\n", out_file_name);
        return -1;
    }
    while (!feof(in_file)) {
        if (!read_next_code_unit(in_file, &code_units)) {
            fprintf(out_file, "%" PRIx32 "\n", decode(&code_units));
        }
    }
    fclose(in_file);
    fclose(out_file);
    return 0;
}
