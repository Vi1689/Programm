#include "varint.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUMBERS_COUNT 100
#define conclusion 10
/*
 * Диапазон Вероятность
 * -------------------- -----------
 * [0; 128) 90%
 * [128; 16384) 5%
 * [16384; 2097152) 4%
 * [2097152; 268435455) 1%
 */
uint32_t generate_number()
{
    const int r = rand();
    const int p = r % 100;
    if (p < 90) {
        return r % 128;
    }
    if (p < 95) {
        return r % 16384;
    }
    if (p < 99) {
        return r % 2097152;
    }
    return r % 268435455;
}

int main()
{
    srand(time(NULL));
    char* uncompressed_file_path = "uncompressed.dat";
    char* compressed_file_path = "compressed.dat";
    FILE* uncompressed = fopen(uncompressed_file_path, "wb");
    FILE* compressed = fopen(compressed_file_path, "wb");
    if ((uncompressed == NULL) || (compressed == NULL)) {
        printf("Failed to create binary file for writing\n");
        return -1;
    }
    int i;
    uint32_t num;
    uint8_t buf[4];
    size_t size_of_encode;
    for (i = 0; i < NUMBERS_COUNT; ++i) {
        num = generate_number();
        //num = 0x31608;
        fwrite(&num, sizeof(uint32_t), 1, uncompressed);
        size_of_encode = encode_varint(num, buf);
        fwrite(buf, sizeof(uint8_t) * size_of_encode, 1, compressed);
    }
    fclose(uncompressed);
    fclose(compressed);
    uncompressed = fopen(uncompressed_file_path, "rb");
    compressed = fopen(compressed_file_path, "rb");
    if ((uncompressed == NULL) || (compressed == NULL)) {
        printf("Failed to open binary file for reading\n");
        return -1;
    }
    fseek(uncompressed, 0, SEEK_END);
    fseek(compressed, 0, SEEK_END);
    rewind(uncompressed);
    rewind(compressed);
    uint32_t num_uncompressed = 0;
    uint8_t* bufp = malloc(200000000);
    uint8_t byte;
    i = 0;
    while(!feof(compressed)){
        fread(&byte, 1, 1, compressed);
        bufp[i++] = byte;
    }
    uint8_t* one_buf = bufp;
    for (i = 0; i < conclusion; ++i) {
        fread(&num_uncompressed, sizeof(uint8_t) * size_of_encode, 4, uncompressed);
        int qq = decode_varint(&bufp);
        printf("i = %d\t", i);
        printf("%d\t ", num_uncompressed);
        printf("%d\n", qq);
        if(num_uncompressed != qq){
            printf("Error");
        }
    }
    fclose(uncompressed);
    fclose(compressed);
    free(one_buf);
    return 0;
}
