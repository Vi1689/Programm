#pragma once

#include <stdio.h>
#include <stdlib.h>

int slen(const char* str);
int* stok(char* str, const char* sep, int* count);
int sspn(const char* str, const char* sym);
int scmp(const char* str1, const char* str2);
char* scpy(char* destination, const char* source, int n);
char* erase(const char* str, int s, int e);
char* copy_m(char* temp, const char* str, int s, int k);