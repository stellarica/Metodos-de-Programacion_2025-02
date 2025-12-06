#include <stdio.h>
#include <stdlib.h>

typedef struct dog {
        char* name;
        char* race;
        int age;
        char* gender;
        int vaccinated;
}dog;

void registerDog(dog* newDog) {
        printf("Ingrese el nombre: \n");
        scanf("%s", &newDog.name);
}

int main(int argc, char* argv[]) {
        int n;
        printf("Ingrese la cantidad de perros a ingresar: \n");
        scanf("%d", &n);

        struct* dogArray = malloc(sizeof(dog)*n);

        int i;
        for (i = 0; i < n; i++) {
                registerDog(*dogArray + i);
        }                                                         
        return 0;
}