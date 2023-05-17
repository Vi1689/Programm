#include "check.h"
#include "strings.h"

int check(char* str, char* delim, char* dir)
{
    if (delim[0] != ' ' && delim[0] != '+' && delim[0] != ':') {
        return 1;
    }
    char sym[] = {'\\', ':', '*', '?', '"', '<', '>', '|'};
    if (sspn(str, sym)) {
        return 2;
    }
    if (sspn(dir, sym)) {
        return 5;
    }
    char* temp = malloc(sizeof(char) * slen(str));
    int* ls;
    int count = 0;
    ls = stok(temp, delim, &count);
    for (int i = 0; i < count; ++i) {
        temp = copy_m(temp, str, ls[i], 0);
        if (slen(temp) > 260) {
            free(ls);
            free(temp);
            return 3;
        }
    }
    if (check_paths(str, delim)) {
        return 4;
    }
    return 0;
}

int check_paths(char* str, char* delim)
{
    int* arr;
    int count = 0;
    char* temp = malloc(sizeof(char) * slen(str));
    temp = scpy(temp, str, slen(str));
    arr = stok(temp, delim, &count);
    if (str[0] != '/' && str[0] != '~') {
        free(arr);
        return 1;
    }
    for (int i = 0; i < count; ++i) {
        if (str[arr[i] + 1] != '/' && str[arr[i] + 1] != '~') {
            free(arr);
            return 1;
        }
    }
    free(arr);
    return 0;
}