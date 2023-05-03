#include "coder.h"
#include "command.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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
    code_units->length = 0;
    uint8_t byte;
    while (code_units->length == 0) {
        fread(&byte, sizeof(uint8_t), 1, in);
        if (feof(in)) {
            return -1;
        }
        if (byte < 0x80) {
            code_units->code[code_units->length++] = byte;
            return 0;
        }
        if (byte >= 0xc0) {
            int i = 3;
            for (uint8_t buf = byte >> 4; buf != 1; buf >>= 1, --i) {
                if ((buf == 0x3) || (buf == 0x7) || (buf == 0xf)) {
                    code_units->code[0] = byte;
                    for (int j = 0; j != i; ++j) {
                        fread(&byte, sizeof(uint8_t), 1, in);
                        if ((byte >= 0x80) && (byte <= 0xbf)) {
                            code_units->code[j + 1] = byte;
                        } else if (!feof(in)) {
                            fseek(in, -1, SEEK_CUR);
                            return -1;
                        } else {
                            return -1;
                        }
                    }
                    code_units->length = i + 1;
                    break;
                }
            }
        }
        return 0;
    }
}

int write_code_unit(FILE* out, const CodeUnit* code_unit)
{
    fwrite(code_unit, sizeof(uint8_t), code_unit->length, out);
    return 0;
}