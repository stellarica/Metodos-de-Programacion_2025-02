#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct dog {
        char name[24];
        char race[24];  
        int age;
        char sex[2];
        int vaccinated;
        struct dog* next;
}dog;

struct dog* dalloc(void) {
        // Allocate memory for a dog
        return (struct dog*) malloc(sizeof(struct dog));
}

void dfree(dog* dogTree) {
        // Free memory allocated for dog tree
        if (dogTree == NULL) {
                return;
        }
        dfree(dogTree->next);
        free(dogTree);
}

struct dog* addDog(struct dog* p) {
        if (p == NULL) {           /* New dog has arrived */
                p = dalloc();      /* Make a new dog node */
                printf("Ingrese el nombre: \n");
                scanf("%23s", p->name);
                printf("Ingrese la raza: \n");
                scanf("%23s", p->race);
                printf("Ingrese la edad: \n");
                scanf("%d", &(p->age));
                printf("Ingrese el sexo (M/F): \n");
                scanf("%1s", p->sex);
                printf("Ingrese si esta vacunado (1 para si, 0 para no): \n");
                scanf("%d", &(p->vaccinated));
                p->next = NULL;
        } else {
                p->next = addDog(p->next);
        }

        return p;
}

void registerDogs(dog** dogTree) {
        // Get number of dogs to register
        int n;
        printf("Ingrese la cantidad de perros a ingresar: \n");
        scanf("%d", &n);

        // Initialize dog tree as NULL
        *dogTree = NULL;
        
        int i;
        for (i = 0; i < n; i++) {
                printf("Registrando perro %d/%d \n", i+1, n);
                *dogTree = addDog(*dogTree);
        }
}

void printDog(dog* dog) {
        if (dog == NULL) {
                printf("Perro no encontrado\n");
                return;
        }
        printf("Nombre: %s\n", dog->name);
        printf("Raza: %s\n", dog->race);
        printf("Edad: %d\n", dog->age);
        printf("sexo: %s\n", dog->sex);
        printf("Vacunado: %d\n", dog->vaccinated);
        printf("\n");
}

dog* findDogByName(dog* dogTree, char* name) {
        dog* node = dogTree;
        while (node != NULL) {
                if (strcmp(node->name, name) == 0) {
                        return node;
                }
                node = node->next;
        }
        return NULL;
}

void printDogBySex(dog* dogTree, char* sex) {
        dog* node = dogTree;
        while (node != NULL) {
                if (toupper(node->sex[0]) == toupper(sex[0])) {
                        printDog(node);
                }
                node = node->next;
        }
        printf("Fin de la lista\n");
}

void printDogByVaccinated(dog* dogTree) {
        dog* node = dogTree;
        while (node != NULL) {
                if (node->vaccinated == 1) {
                        printDog(node);
                }
                node = node->next;
        }
        printf("Fin de la lista\n");
}

int showMenu(dog* dogTree) {
        int option;
        printf("Seleccione una opcion:\n");
        printf("1. Buscar perro por nombre\n");
        printf("2. Mostrar perros por sexo\n");
        printf("3. Mostrar perros vacunados\n");
        printf("4. Salir\n");
        scanf("%d", &option);
        switch (option) {
                case 1: {
                        char name[24];
                        printf("Ingrese el nombre del perro a buscar:\n");
                        scanf("%23s", name);
                        printf("Mostrando informacion del perro:\n");
                        printDog(findDogByName(dogTree, name));
                        break;
                }
                case 2: {
                        char sex[2];
                        printf("Ingrese el sexo a buscar (M/F):\n");
                        scanf("%1s", sex);
                        printf("Mostrando perros de sexo %s:\n", sex);
                        printDogBySex(dogTree, sex);
                        break;
                }
                case 3:
                        printf("Mostrando perros vacunados:\n");
                        printDogByVaccinated(dogTree);
                        break;
                case 4:
                        return 0;
                default:
                        printf("Opcion invalida\n");
        }
        return 1;
}

void loop(dog* dogTree) {
        while (showMenu(dogTree) != 0) {
        }
}

void init() {
        // Initialize dog array and register dogs
        dog* dogTree = NULL;
        registerDogs(&dogTree);

        // Start execution loop
        loop(dogTree);

        // Cleanup
        dfree(dogTree);
}


int main(int argc, char* argv[]) {
        init();
        return 0;
}