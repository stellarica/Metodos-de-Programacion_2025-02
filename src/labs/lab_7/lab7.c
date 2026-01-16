#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_ARRAY_LENGTH 128
#define MAX_CHAR_LENGTH 7

int main(int argc, char *argv[]);
int getIndex(int *array, size_t size, int value);
int* getPivot(int *array, size_t size, int low, int high, int *pivotIndex);
int* quicksort(int *array, size_t size, int low, int high);
int* getItems(int *array, size_t size, int start, int end);
int* append(int* array, size_t size, int value);
int* appendArray(int *array1, size_t size1, int *array2, size_t size2);
void printArray(int *array, size_t size);


void printArray(int *array, size_t size) {
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", array[i]);
	printf("\n");

	return;
}

int* append(int *array, size_t size, int value) {
	int *newArray = (int*) calloc(size+1, __SIZEOF_INT__);
	int i;
	for (i = 0; i < size; i++)
		newArray[i] = array[i];
	newArray[size] = value;

	return newArray;
}

int* appendArray(int *array1, size_t size1, int *array2, size_t size2) {
	int *newArray = (int*) calloc(size1 + size2, __SIZEOF_INT__);
	int i;
	for (i = 0; i < size1; i++)
		newArray[i] = array1[i];
	for (i = 0; i < size2; i++)
		newArray[size1+i] = array2[i];
	
	return newArray;
}

int* getItems(int *array, size_t size, int start, int end) {
	int i;
	int index;
	size_t actualSize = end - start;
	int *newArray = (int*) calloc(actualSize, __SIZEOF_INT__);
	for (i = 0; i < actualSize; i++) {
		index = start + i;
		newArray[i] = array[index];
	}

	return newArray;
}

int* quicksort(int *array, size_t size, int low, int high) {
	if (high < 0)
		high = (int) size - 1;

	if (low < high) {
		int pivotIndex;
		int *newArray = getPivot(array, size, low, high, &pivotIndex);
		free(array);
		array = newArray;
		
		array = quicksort(array, size, low, pivotIndex - 1);
		array = quicksort(array, size, pivotIndex + 1, high);
	}

	return array;
}

int* getPivot(int *array, size_t size, int low, int high, int *pivotIndex) {
	int pivot = array[high];
	int i = low - 1;
	int j;
	int *tmpArray1 = NULL;
	int *tmpArray2 = NULL;
	int *tmpArray3 = NULL;
	
	/* copy elements of array to newArray */
	int *newArray = (int*) calloc(size, __SIZEOF_INT__);
	int k;
	for (k = 0; k < size; k++)
		newArray[k] = array[k];

	for (j = low; j < high; j++) {
		if (newArray[j] <= pivot) {
			i++;
			
			if (i != j) {
				/* get arrays: array[0:i-1], array[i+1:j-1], array[j+1:end]
				   NULL is an empty pointer, so it also serves as an array to append to */
				tmpArray1 = (i > 0)      ? getItems(newArray, size, 0  , i)    : NULL;
				tmpArray2 = (j > i+1)    ? getItems(newArray, size, i+1, j)    : NULL;
				tmpArray3 = (j+1 < size) ? getItems(newArray, size, j+1, size) : NULL;
				
				int *result = NULL;
				size_t resultSize = 0;
				
				// from array[0:end] -> array[0:i-1]
				if (tmpArray1) {
					result = appendArray(result, resultSize, tmpArray1, i);
					resultSize = i;
					free(tmpArray1);
				}
				
				/* to array[0:i-1] append array[j] */
				result = append(result, resultSize, newArray[j]);
				resultSize++;
				
				/* to array[0:i-1]+array[j] append array[i+1:j-1] */
				if (tmpArray2) {
					int *temp = appendArray(result, resultSize, tmpArray2, j-i-1);
					free(result);
					result = temp;
					resultSize += (j-i-1);
					free(tmpArray2);
				}
				
				/* to array[0:i-1]+array[j]+array[i+1:j-1] append array[i] */
				result = append(result, resultSize, newArray[i]);
				resultSize++;
				
				/* to array[0:i-1]+array[j]+array[i+1:j-1]+array[i] append array[i+1:end]*/
				if (tmpArray3) {
					int *temp = appendArray(result, resultSize, tmpArray3, size-j-1);
					free(result);
					result = temp;
					free(tmpArray3);
				}
				
				free(newArray);
				newArray = result;
			}
		}
	}
	
	if (i+1 != high) {
		/* get arrays: array[0:i], array[i+2:high-1], array[high+1:end] */
		tmpArray1 = (i+1 > 0)       ? getItems(newArray, size, 0     , i+1)  : NULL;
		tmpArray2 = (i+2 < high)    ? getItems(newArray, size, i+2   , high) : NULL;
		tmpArray3 = (high+1 < size) ? getItems(newArray, size, high+1, size) : NULL;
		
		int *result = NULL;
		size_t resultSize = 0;
		
		/* from array[0:end] -> array[0:i+1] */
		if (tmpArray1) {
			result = appendArray(result, resultSize, tmpArray1, i+1);
			resultSize = i+1;
			free(tmpArray1);
		}
		
		/* to array[0:i] append array[high] */
		result = append(result, resultSize, newArray[high]);
		resultSize++;
		
		/* to array[0:i]+array[high] append array[i+2:high-1] */
		if (tmpArray2) {
			int *tmp = appendArray(result, resultSize, tmpArray2, high-i-2);
			free(result);
			result = tmp;
			resultSize += (high-i-2);
			free(tmpArray2);
		}
		
		/* to array[0:i]+array[high]+array[i+2:high-1] append array[i+1]  */
		result = append(result, resultSize, newArray[i+1]);
		resultSize++;
		
		/* to array[0:1]+array[high]+array[i+2:high-1]+array[i+1] append array[high+1:end] */
		if (tmpArray3) {
			int *tmp = appendArray(result, resultSize, tmpArray3, size-high-1);
			free(result);
			result = tmp;
			free(tmpArray3);
		}
		
		free(newArray);
		newArray = result;
	}
	
	*pivotIndex = i+1;
	return newArray;
}

int getIndex(int *array, size_t size, int value) {
	int i;
	for (i = 0; i < size; i++)
		if (array[i] == value)
			return i;

	return -1;
}

int main(int argc, char *argv[]) {
	int *array = (int*) calloc(MAX_ARRAY_LENGTH, __SIZEOF_INT__);

	char *c = (char*) malloc(sizeof(char) * (MAX_CHAR_LENGTH+1));
	memset(c, '\0', sizeof(char) * (MAX_CHAR_LENGTH+1));

	int num;
	size_t size = 0;
	
	while (1) {
		printf("Ingrese el numero %d del array o ingrese 'q' para finalizar: ", (int) size+1);
		scanf("%s", c);
		if (strncmp(c, "q", 1) == 0)
			break;
		if (strlen(c) > MAX_CHAR_LENGTH) {
			perror("Tamaño maximo de string alcanzado");
			goto cleanup;
		}
		if (size >= MAX_ARRAY_LENGTH) {
			perror("Tamaño maximo de array alcanzado");
			goto cleanup;
		}
		num = atoi(c);
		array[size] = num;
		size++;
	}


	int *sorted = quicksort(array, size, 0, (int) size - 1);

	printArray(sorted, size);
    
	if (sorted)  free(sorted);
	if (c)       free(c);
	
	return 0;

cleanup:
	if(array) free(array);
	if(c) 	  free(c);
	return -1;
}