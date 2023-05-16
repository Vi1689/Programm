#include "/home/vitaliy/Programm/laba4/include/input_output.h"

int main()
{
    char* paths = malloc(sizeof(char) * 300);
    char* delim = malloc(sizeof(char));
    printf("delim : ");
    input(delim);
    printf("paths : ");
    input(paths);
    output(paths, delim);
    free(paths);
    free(delim);
}