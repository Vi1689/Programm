#include "/home/vitaliy/Programm/laba4/include/input_output.h"

int main()
{
    char* paths = malloc(sizeof(char) * 300);
    char* delim = malloc(sizeof(char));
    char* name = malloc(sizeof(char) * 10);
    char* dir = malloc(sizeof(char) * 100);
    printf("delim : ");
    input(delim);
    printf("user name: ");
    input(name);
    printf("dir: ");
    input(dir);
    printf("paths : ");
    input(paths);
    output(paths, delim, dir);
    free(paths);
    free(delim);
}