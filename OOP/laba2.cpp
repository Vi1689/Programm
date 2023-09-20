#include <iostream>
#include <time.h>

using namespace std;

int** creating_matrix(int size)
{
    int** matrix = new int*[size];
    for (int i = 0; i < size; ++i) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = rand() % 100;
        }
    }
    return matrix;
}

void print_matrix(int** matrix, int size)
{
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

void print_arr(int* D, int size)
{
    for (int i = 0; i < size; ++i) {
        cout << D[i] << " ";
    }
    cout << "\n";
}

int* creating_D(int size)
{
    int* D = new int[size];
    return D;
}

void punkt_a(int* D, int size, int** matrix)
{
    int k = 0;
    for (int count = size - 1; count >= 0; --count) {
        int i = 0, j = count;
        while (i != (size) && j != (size)) {
            D[k++] = matrix[i++][j++];
        }
    }
    for (int count = 1; count <= size - 1; ++count) {
        int i = count, j = 0;
        while (i != (size) && j != (size)) {
            D[k++] = matrix[i++][j++];
        }
    }
    cout << "Punkt a: ";
    print_arr(D, k);
}

void punkt_b(int* D, int size, int** matrix)
{
    int k = 0;
    for (int count = 0; count < size; ++count) {
        int i = 0, j = count;
        while (i != (size) && j >= 0) {
            D[k++] = matrix[i++][j--];
        }
    }
    for (int count = 1; count <= size - 1; ++count) {
        int i = count, j = size - 1;
        while (i != (size) && j >= 0) {
            D[k++] = matrix[i++][j--];
        }
    }
    cout << "Punkt b: ";
    print_arr(D, k);
}

void punkt_c(int* D, int size, int** matrix)
{
    int k = size * size - 1, i = 0, j = 0, ch;
    if (size % 2) {
        ch = size / 2 + 1;
    } else {
        ch = size / 2;
    }
    for (int temp = 0; temp < ch; ++temp) {
        while (i != (size - 1 - temp)) {
            D[k--] = matrix[i++][j];
        }
        while (j != (size - 1 - temp)) {
            D[k--] = matrix[i][j++];
        }
        while (i > temp) {
            D[k--] = matrix[i--][j];
        }
        while (j > temp + 1) {
            D[k--] = matrix[i][j--];
        }
    }
    D[k--] = matrix[i][j];
    cout << "Punkt c: ";
    print_arr(D, size * size);
}

void punkt_d(int* D, int size, int** matrix)
{
    int k = 0, i = 0, j = 0, ch;
    if (size % 2) {
        ch = size / 2 + 1;
    } else {
        ch = size / 2;
    }
    for (int temp = 0; temp < ch; ++temp) {
        while (i != (size - 1 - temp)) {
            D[k++] = matrix[i++][j];
        }
        while (j != (size - 1 - temp)) {
            D[k++] = matrix[i][j++];
        }
        while (i > temp) {
            D[k++] = matrix[i--][j];
        }
        while (j > temp + 1) {
            D[k++] = matrix[i][j--];
        }
    }
    D[k++] = matrix[i][j];
    cout << "Punkt d: ";
    print_arr(D, k);
}

void Task_2(int n)
{
    int** a = new int*[n];
    int* b = new int[n];
    for (int i = 0; i < n; ++i) {
        b[i] = rand() % 5 + 1;
        a[i] = new int[b[i]];
        for (int j = 0; j < b[i]; ++j) {
            a[i][j] = rand() % 100;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < b[i]; ++j) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
    for (int i = 0; i < n; ++i) {
        free(a[i]);
    }
    free(a);
    free(b);
}

int main()
{
    srand(time(NULL));
    cout << "\nЗадание 1\n";
    int size = rand() % 5 + 1;
    int** matrix = creating_matrix(size);
    print_matrix(matrix, size);
    int* D = creating_D(size * size);
    punkt_a(D, size, matrix);
    punkt_b(D, size, matrix);
    punkt_c(D, size, matrix);
    punkt_d(D, size, matrix);
    for (int i = 0; i < size; ++i) {
        free(matrix[i]);
    }
    free(matrix);
    free(D);
    cout << "\nЗадание 2\n";
    int n = rand() % 5 + 1;
    Task_2(n);
}