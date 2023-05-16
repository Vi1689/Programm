#include "input_output.h"
#include "check.h"
#include "process.h"

char* input(char* str)
{
    fgets(str, 300, stdin);
    fflush(stdin);
    return str;
}

void output(char* paths, char* delim)
{
    switch (check(paths, delim)) {
    case 0:
        printf("new paths : %s\n", process(paths, delim));
        break;
    case 1:
        printf("The delim is entered incorrectly\n");
        break;
    case 2:
        printf("There are forbidden characters in the path\n");
        break;
    case 3:
        printf("Path length exceeded\n");
        break;
    case 4:
        printf("Invalid file path\n");
        break;
    }
}