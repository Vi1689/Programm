#include "process.h"
#include "strings.h"

char* process(char* str, char* delim)
{
    int* arr;
    int count = 0, count_1 = 0, mull = 0;
    arr = stok(str, delim, &count);
    char* temp = malloc(sizeof(char) * slen(str));
    temp = scpy(temp, str, slen(str));
    int* ls;
    char* sep = malloc(sizeof(char));
    sep[0] = '/';
    ls = stok(temp, sep, &count_1);
    char* new_str = malloc(sizeof(char) * slen(str));
    new_str = scpy(new_str, str, slen(str));
    int i = 0;
    char* print = malloc(sizeof(char) * 300);
    while (count_1--) {
        if (ls[i + 1] - ls[i] == 2) {
            new_str = erase(new_str, ls[i], ls[i + 1]);
            temp = scpy(temp, new_str, slen(new_str));
            ls = stok(temp, sep, &mull);
            i--;
        }
        if (ls[i + 1] - ls[i] == 3) {
            new_str = erase(new_str, ls[i - 1], ls[i + 1]);
            temp = scpy(temp, new_str, slen(new_str));
            ls = stok(temp, sep, &mull);
            i--;
        }
        i++;
    }
    free(ls);
    int arr_count = 0;
    print = copy_m(print, new_str - 1, 0, 0);
    while (count--) {
        print = copy_m(print, delim - 1, 0, slen(print));
        count_1 = 0;
        temp = copy_m(temp, str, arr[arr_count], 0);
        int* ls;
        ls = stok(temp, sep, &count_1);
        new_str = copy_m(new_str, str, arr[arr_count++], 0);
        i = 0;
        while (count_1--) {
            if (ls[i + 1] - ls[i] == 2) {
                new_str = erase(new_str, ls[i], ls[i + 1]);
                temp = scpy(temp, new_str, slen(new_str));
                ls = stok(temp, sep, &mull);
                i--;
            }
            if (ls[i + 1] - ls[i] == 3) {
                new_str = erase(new_str, ls[i - 1], ls[i + 1]);
                temp = scpy(temp, new_str, slen(new_str));
                ls = stok(temp, sep, &mull);
                i--;
            }
            i++;
        }
        free(ls);
        print = copy_m(print, new_str - 1, 0, slen(print));
    }
    return print;
}