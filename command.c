#include "command.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int encode_file(const char* in_file_name, const char* out_file_name)
{
    FILE* in_file = fopen("encode.txt", "r");
    if (!in_file) {
        return -1;
    }
    FILE* out_file = fopen("out_emcode.txt", "w");
    if (!out_file) {
        return -1;
    }
    return 0;
}

int decode_file(const char* in_file_name, const char* out_file_name)
{
    FILE* in_file = fopen("decode.txt", "r");
    if (!in_file) {
        return -1;
    }
    FILE* out_file = fopen("out_decode.txt", "w");
    if (!out_file) {
        return -1;
    }
    return 0;
}

int encode(uint32_t code_point, CodeUnit* code_units)
{
    uint8_t count = 0;
    for (uint32_t i = code_point; i > 0; i >>= 1) {
        count++;
    }
    if (count <= 7) {
        code_units->code[0] = code_point;
        code_units->length = 1;
        return 0;
    } else if (count <= 11) {
        code_units->code[0] = 0xc0 | (code_point >> 6);
        code_units->code[1] = 0x80 | (code_point & 0x3f);
        code_units->length = 2;
        return 0;
    } else if (count <= 16) {
        code_units->code[0] = 0xe0 | (code_point >> 12);
        code_units->code[1] = 0x80 | ((code_point & 0xfc0) >> 6);
        code_units->code[2] = 0x80 | (code_point & 0x3f);
        code_units->length = 3;
        return 0;
    } else if (count <= 21) {
        code_units->code[0] = 0xf0 | (code_point >> 18);
        code_units->code[1] = 0x80 | ((code_point & 0x3f000) >> 12);
        code_units->code[2] = 0x80 | ((code_point & 0xfc0) >> 6);
        code_units->code[3] = 0x80 | (code_point & 0x3f);
        code_units->length = 4;
        return 0;
    }
    return -1;
}

uint32_t decode(const CodeUnit* code_unit)
{
    uint32_t code_point = 0;
    if ((code_unit->code[0] >> 7) == 0) {
        code_point = code_unit->code[0];
    } else if (code_unit->code[0] <= 0xdf) {
        code_point = ((code_unit->code[0] & 0x1f) << 6)
                | (code_unit->code[1] & 0x3f);
    } else if (code_unit->code[0] <= 0xef) {
        code_point = ((code_unit->code[0] & 0xf) << 12)
                | ((code_unit->code[1] & 0x3f) << 6)
                | (code_unit->code[2] & 0x3f);
    } else if (code_unit->code[0] <= 0xf7) {
        code_point = ((code_unit->code[0] & 0x7) << 18)
                | ((code_unit->code[1] & 0x3f) << 12)
                | ((code_unit->code[2] & 0x3f) << 6)
                | (code_unit->code[3] & 0x3f);
    }
    return code_point;
}

int read_next_code_unit(FILE* in, CodeUnit* code_units)
{
    
}

int write_code_unit(FILE* out, const CodeUnit* code_unit)
{
    fwrite(code_unit, sizeof(uint8_t), code_unit->length, out);
    return 0;
}