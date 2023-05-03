#include "varint.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUMBERS_COUNT 1000000
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
    size_t size_of_buf[100];
    for (i = 0; i < NUMBERS_COUNT; ++i) {
        num = generate_number();
        fwrite(&num, sizeof(uint32_t), 1, uncompressed);
        size_of_encode = encode_varint(num, buf);
        fwrite(buf, sizeof(uint8_t), size_of_encode, compressed);
        if (i < 100) {
            size_of_buf[i] = size_of_encode;
        }
    }
    fclose(uncompressed);
    fclose(compressed);
    uncompressed = fopen(uncompressed_file_path, "rb");
    compressed = fopen(compressed_file_path, "rb");
    if ((uncompressed == NULL) || (compressed == NULL)) {
        printf("Failed to open binary file for reading\n");
        return -1;
    }
    // get size of files
    fseek(uncompressed, 0, SEEK_END);
    fseek(compressed, 0, SEEK_END);
    printf("Size: %ld kb (uncompressed).\nSize: %ld kb(compressed).\n\n",
           ftell(uncompressed) / 1024,
           ftell(compressed) / 1024);
    rewind(uncompressed);
    rewind(compressed);
    uint32_t num_uncompressed = 0;
    uint32_t num_compressed = 0;
    for (i = 0; i < 100; ++i) {
        fread(&num_uncompressed,
              sizeof(uint8_t),
              sizeof(uint32_t),
              uncompressed);
        fread(&num_compressed, sizeof(uint8_t), size_of_buf[i], compressed);
        const uint8_t* bufp = (uint8_t*)&num_compressed;
        num_compressed = decode_varint(&bufp);
        printf("i = %d\t", i);
        printf("%d\t", num_uncompressed);
        printf("%d\n", num_compressed);
    }
    fclose(uncompressed);
    fclose(compressed);
    return 0;
}
