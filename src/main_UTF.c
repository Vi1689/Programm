#include "coder.h"
#include "command.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    for (int i = 0; i < argc; ++i) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    if (argc == 4) {
        if (strcmp(argv[1], "encode") == 0) {
            encode_file(argv[2], argv[3]);
        } else if (strcmp(argv[1], "decode") == 0) {
            decode_file(argv[2], argv[3]);
        } else {
            printf("Usage:\n");
            printf("./src/main encode <in-file-name> <out-file-name>\n");
            printf("./src/main decode <in-file-name> <out-file-name>\n");
            return -1;
        }
    } else {
        printf("Usage:\n");
        printf("./src/main encode <in-file-name> <out-file-name>\n");
        printf("./src/main decode <in-file-name> <out-file-name>\n");
        return -1;
    }
    return 0;
}