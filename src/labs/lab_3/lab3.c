#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    // Ingresar numeros uno a uno hasta que el usuario pare
    // Se ingresan dos numero distintos de largo N
    // Se suman como si los numeros de las listas fueran un solo numero cada
    // Dejar los digitos de la suma en otra lista

    printf("Ingrese :\n");

    int** array = (int**) malloc(sizeof(int*) * 2);
    int i;

    for (i = 0; i < 5; i++) {
        array[i] = (int*) malloc(sizeof(int) * 2);
    }

    for (i = 0; i < 5; i++) {
        printf("%d\n", *(array+i));
    }

    for (i = 0; i < 5; i++) {
        free(array[i]);
    }

    free(array);

    return 0;
}