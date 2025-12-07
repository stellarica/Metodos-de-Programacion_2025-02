#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    
    /*-------------------------------------------------------------------------.
    |  Ingresar numeros uno a uno hasta que el usuario pare                    |
    |  Se ingresan dos numero distintos de largo N                             |
    |  Se suman como si los numeros de las listas fueran un solo numero cada   |
    |  Dejar los digitos de la suma en otra lista                              |
    `--------------------------------------------------------------------------*/

    int n;
    size_t size = 0;
    int* n1 = (int*) malloc(sizeof(int));
    while(1) {
        printf("Ingrese el numero %d de la primera lista o 'q' para terminar: ", size+1);
        scanf("%d", &n);
        if (strcmp(&n, "q") == 0) {
            break;
        }
        size++;
        n1 = append(n1, &size, n);
    }
    
    int* n2 = (int*) malloc(sizeof(int));
    int* sum = (int*) malloc(sizeof(int));
    size_t size2 = 0;
    while (size2 < size) {
        printf("Ingrese el numero %d de la segunda lista: ", size2+1);
        scanf("%d", &n);
        size2++;
        n2 = append(n2, &size2, n);
        sum = append(sum, &size2, (n1[size2-1] + n));
    }
    
    int i;
    printf("Lista 1: ");
    for (i = 0; i < size; i++) {
        printf("%d ", n1[i]);
    }
    printf(("\n"));
    
    printf("Lista 2: ");
    for (i = 0; i < size; i++) {
        printf("%d ", n2[i]);
    }
    printf(("\n"));
    
    printf("Suma:    ");
    for (i = 0; i < size; i++) {
        printf("%d ", sum[i]);
    }

    return 0;
}