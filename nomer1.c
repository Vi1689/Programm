#include <stdio.h>
#include <stdlib.h>

void merge(int* arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int* L = malloc(sizeof(int) * n1);
    int* R = malloc(sizeof(int) * n2);
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int* arr, int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main()
{
    int n, count = 0;
    scanf("%d", &n);
    n += 2;
    int* a = malloc(sizeof(int) * n);
    for (int i = 1; i < n - 1; ++i) {
        scanf("%d", &a[i]);
    }
    a[0] = 0;
    a[n - 1] = 0;
    mergeSort(a, 0, n - 2);
    for (int i = 1; i < n - 1; ++i) {
        if (a[i - 1] != a[i] && a[i + 1] != a[i]) {
            count++;
        }
    }
    printf("%d", count);
    free(a);
    return 0;
}