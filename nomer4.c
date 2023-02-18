#include <stdio.h>

// Here been SAMOXA :)

void swap(int *a, int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void bubble_sort(int *array, int size){
	int i, j;
	for(i = 0; i < size - 1; ++i){
		for(j = 0; j < size - i; ++j){
			if(array[j] > array[j + 1]){
				swap(&array[j], &array[j + 1]);
			}
		}
	}
}

int main(){
	int array[100] = {10, 15, 5, 4, 21, 7};
	bubble_sort(array, 5);
	int i;
	for(i = 0; i < 6; ++i){
		printf("%d ", array[i]);
	}
	printf("\n");
	return 0;
}
