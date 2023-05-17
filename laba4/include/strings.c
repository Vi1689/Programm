#include "strings.h"

int slen(const char* str)
{
    int count = 0;
    while (str[count] != '\0' && str[count] != '\n') {
        count++;
    }
    return count;
}

int* stok(char* str, const char* sep, int* count)
{
    int j = 0, temp = slen(str);
    for (int i = 0; i < temp; ++i) {
        if (str[i] == sep[0]) {
            (*count)++;
        }
    }
    if ((*count) < 1) {
        return NULL;
    }
    int* arr = malloc(sizeof(int) * (*count));
    for (int i = 0; i < temp; ++i) {
        if (str[i] == sep[0]) {
            str[i] = '\0';
            arr[j++] = i;
        }
    }
    return arr;
}

int sspn(const char* str, const char* sym)
{
    for (int i = 0; i < slen(str); ++i) {
        for (int j = 0; j < slen(sym); ++j) {
            if (str[i] == sym[j]) {
                return 1;
            }
        }
    }
    return 0;
}

int scmp(const char* str1, const char* str2)
{
    int i;
    for (i = 0; (str1[i] == str2[i]) && str1[i] != '\n' && str1[i] != '\0'
         && str2[i] != '\n' && str2[i] != '\0';
         ++i)
        ;
    if (str1[i] > str2[i]) {
        return 1;
    }
    if (str1[i] < str2[i]) {
        return -1;
    }
    return 0;
}

char* scpy(char* destination, const char* source, int n)
{
    int i;
    for (i = 0; i < n && source[i] != '\0' && source[i] != '\n'; ++i) {
        destination[i] = source[i];
    }
    for (int k = i; k < n; ++k) {
        destination[k] = '\0';
    }
    return destination;
}

char* erase(const char* str, int s, int e)
{
    char* temp = malloc(sizeof(char) * (slen(str) - 2));
    int k = 0;
    for (int i = 0; i < s; ++i) {
        temp[k++] = str[i];
    }
    for (int i = e; i < slen(str); ++i) {
        temp[k++] = str[i];
    }
    return temp;
}

char* copy_m(char* temp, const char* str, int s, int k)
{
    for (int i = s + 1; str[i] != '\0'; ++i) {
        temp[k++] = str[i];
    }
    for (int i = k; i < slen(str); ++i) {
        temp[i] = '\0';
    }
    return temp;
}