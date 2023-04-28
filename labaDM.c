#include <stdio.h>
#include <stdlib.h>

int count = 1;

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void lol(int* a, int n, int num)
{
    if (n == num) {
        printf("%d: ", count++);
        for (int i = 0; i < num; ++i) {
            printf("%d ", a[i]);
        }
        printf("\n");
    } else {
        for (int i = n; i < num; ++i) {
            swap(&a[n], &a[i]);
            lol(a, n + 1, num);
            swap(&a[n], &a[i]);
        }
    }
}

int main()
{
    int num;
    scanf("%d", &num);
    int* a = malloc(sizeof(int) * num);
    for (int i = 0; i < num; ++i) {
        a[i] = i + 1;
    }
    lol(a, 0, num);
    free(a);
    return 0;
}