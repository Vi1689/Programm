#include <stdio.h>
#include <stdlib.h>

struct node {
    char* parent;
    char** children;
};

int main()
{
    int n;
    scanf("%d", &n);
    while (n--) {
        char* a = malloc(sizeof(char) * 32);
        char* b = malloc(sizeof(char) * 32);
        scanf("%s %s", a, b);
        printf("%s\n%s\n", a, b);
    }
    return 0;
}