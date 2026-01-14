#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY_LENGTH 128
#define MAX_CHAR_LENGTH 7

int main(int argc, char *argv[]);
int* quicksort(int *array, size_t size);


int* quicksort(int *array, size_t size) {
	if (size > 2) {
		int array1[size/2];
	}

	return;
}


int main(int argc, char *argv[]) {
	int array[MAX_ARRAY_LENGTH];
	memset(array, 0, sizeof(array));

	char c[MAX_CHAR_LENGTH];
	memset(c, '\0', sizeof(c));

	size_t size = 0;
	
	while (1) {
		printf("Ingrese el numero %d del array o ingrese 'q' para finalizar: ", size+1);
		scanf("%d", c);
		if (strncmp(c, 'q', 1))
			break;
		size++;
		array[size] = c;
	}

	int *sorted;
	memset(sorted, 0, MAX_ARRAY_LENGTH);

	sorted = quicksort(array, size);

	return 0;
}