#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_MAX 0x80000000

int* append(int* array, size_t* size, int value) {
    int i;
    int* newArray = (int*) malloc(sizeof(int) * *size);
    for (i = 0; i < *size; i++) {
        newArray[i] = array[i];
    }
    free(array);
    newArray[*size-1] = value;
    
    return newArray;
}

int main(int argc, char* argv[]) {
    int* array = (int*) malloc(sizeof(int));
    int* oddArray = (int*) malloc(sizeof(int));
    size_t size;
    size_t oddSize;
    int max = DEFAULT_MAX;
    int n;
    int i;

    for (i = 0; i < 10; i++) {
        printf("Ingrese el numero %d/10 del array: ", i+1);
        scanf("%d", &n);
        if ((n % 2 == 1) || (n % 2 == -1)) {
            oddSize++;
            oddArray = append(oddArray, &oddSize, n);
            if (n > max) max = n;
        }
        size++;
        array = append(array, &size, n);
    }

    printf("array = ");
    for (i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }

    printf("\noddArray = ");
    for (i = 0; i < oddSize; i++) {
        printf("%d ", oddArray[i]);
    }
    
    if (max != DEFAULT_MAX) {
        printf("\nEl numero mas grande de oddArray es: %d\n", max);
    } else {
        printf("\nNo se ingresaron numeros impares\n");
    }
    
    return 0;
}