#include <stdio.h> //Libreria estandar input output para utilizar scanf y printf
#include <stdlib.h> //Libreria estandar para utilizar malloc (memory allocation)
#include <string.h> //Libreria strings para utilizar strcmp (comparacion de cadenas de caracteres)

//Declaracion del "tipo de dato" producto
//typedef para ponerle un apodo
typedef struct producto{
	char* nombre;
	int serie;
	int precio;
	int peso;
	int volumen;
	int cantidad_disponible;
}producto; //apodo del tipo de dato struc producto

//en caso de no utilizar typedef antes de struct con el apodo al final
//se puede utilizar la siguiente linea de codigo luego del struct
//typedef struct producto producto;
//donde el tipo de dato es struct producto y el apodo es producto
//(no es necesario que el apodo tenga el mismo nombre que la estructura)

//funcion para solicitar datos de un producto al usuario
//Entrada:
//Salida: producto
producto solicitar_datos(){
	producto prod; //se declara un tipo de dato producto de nombre producto
	prod.nombre = (char*)malloc(sizeof(char)*20); //Declaracion de memoria para el nombre del producto
	printf("Ingrese el nombre del producto: ");
	scanf("%s", prod.nombre);
	printf("Ingrese el numero de serie: ");
	scanf("%d", &prod.serie);
	printf("Ingrese el precio del producto: ");
	scanf("%d", &prod.precio);
	printf("Ingrese el peso del producto: ");
	scanf("%d", &prod.peso);
	printf("Ingrese el volumen del producto: ");
	scanf("%d", &prod.volumen);
	printf("Ingrese la cantidad disponible: ");
	scanf("%d", &prod.cantidad_disponible);
	return prod; //se retorna el producto creado con todos los datos ingresados por el usuario
}

//Procedimiento para mostrar todos los datos de un producto
//Entrada: producto
//Salida:
void mostrar_datos(producto prod){
	printf("Nombre: %s \n", prod.nombre);
	printf("Numero de serie: %d\n", prod.serie);
	printf("Precio: %d \n", prod.precio);
	printf("Peso: %d \n", prod.peso);
	printf("Volumen: %d \n", prod.volumen);
	printf("Cantidad disponible: %d \n\n", prod.cantidad_disponible);
	return;
}

//Funcion para agregar un producto a una lista de productos de tamano n
//Entrada: arreglo de productos, tamano n del arreglo de productos, producto
//Salida: arreglo de productos
producto* agregar_producto(producto* productos, int n, producto nuevo_producto){
	//Declaracion de memoria dinamica para el nuevo arreglo de productos de tamano n+1
	producto* productos_actualizados = (producto*)malloc(sizeof(producto)*(n+1)); 
	int i;
	//Se itera sobre el arreglo de productos anterior para copiar los elementos de cada producto en el nuevo arreglo de productos
	for (i = 0; i < n; i++){
		productos_actualizados[i].nombre = productos[i].nombre;
		productos_actualizados[i].serie = productos[i].serie;
		productos_actualizados[i].precio = productos[i].precio;
		productos_actualizados[i].peso = productos[i].peso;
		productos_actualizados[i].volumen = productos[i].volumen;
		productos_actualizados[i].cantidad_disponible = productos[i].cantidad_disponible;
	}
	//Se libera la memoria del arreglo productos
	free(productos);
	
	//En la posicion n del nuevo arreglo de productos se agrega el nuevo producto
	productos_actualizados[n].nombre = nuevo_producto.nombre;
	productos_actualizados[n].serie = nuevo_producto.serie;
	productos_actualizados[n].precio = nuevo_producto.precio;
	productos_actualizados[n].peso = nuevo_producto.peso;
	productos_actualizados[n].volumen = nuevo_producto.volumen;
	productos_actualizados[n].cantidad_disponible = nuevo_producto.cantidad_disponible;
	//Se retorna el nuevo arreglo de productos con el nuevo producto en la posicion final
	return productos_actualizados;
}

int main(){
	//Se declara el tamano del arreglo inicial de productos
	int n = 0;
	//Declaracion de memoria dinamica para el arreglo de productos de tamano n
	producto* productos = (producto*)malloc(sizeof(producto)*n);
	printf("-----BIENVENID@ AL SISTEMA----- \n\n\n");
	//Menu
	int producto_esta_en_productos; //Verificar si se encontro el producto en la busqueda
	int opcion = 0;
	int opcion2 = 0;
	int i;
	char* nombre_producto_a_buscar = (char*)malloc(sizeof(char)*20);
	int serie;
	while (opcion != 4){
		printf("OPCIONES: \n");
		printf("1. Ingresar un producto al sistema \n");
		printf("2. Listar productos \n");
		printf("3. Buscar productos \n");
		printf("4. Salir \n\n");
		printf("Ingrese una opción: ");
		scanf("%d",&opcion);
		if (opcion == 1){
			printf(" \n ---- INGRESAR UN PRODUCTO AL SISTEMA ---- \n");
			//Se crea un nuevo producto solicitando los datos al usuario
			producto nuevo_producto = solicitar_datos();
			//con el metodo agregar producto se ingresa el nuevo producto solicitado a
			//un nuevo arreglo de productos que tiene toda la informacion del anterior
			productos = agregar_producto(productos, n, nuevo_producto);
			n++;
		}else if (opcion == 2){
			printf("\n ---- LISTAR PRODUCTOS CON DISPONIBILIDAD ----\n");
			for (i = 0; i<n; i++){
				printf("PRODUCTO: %s \n", productos[i].nombre);
				printf("DISPONIBILIDAD: %d \n\n", productos[i].cantidad_disponible);
			}
		}else if (opcion == 3){
			while (opcion2 !=3){
				printf("\n ---- BUSCAR PRODUCTOS ----\n");
				printf("OPCIONES: \n");
				printf("1. Buscar por nombre \n");
				printf("2. Buscar por numero de serie \n");
				printf("3. Volver\n");
				printf("Ingrese una opción: ");
				scanf("%d", &opcion2);
				producto_esta_en_productos = 0; //se inicializa en cero 
				if (opcion2 == 1){
					printf("\n ---- BUSCAR PRODUCTOS POR NOMBRE ----\n");
					printf("Ingrese nombre del producto: ");
					//como el nombre es una direccion de memoria no es necesario utilizar &
					scanf("%s", nombre_producto_a_buscar);
					
					for (i=0; i<n; i++){
						//Se compara si el nombre del producto a buscar coincide en el arreglo de productos y si coincide lo muestra
						if(!strcmp(nombre_producto_a_buscar,productos[i].nombre)){
							mostrar_datos(productos[i]);
							producto_esta_en_productos = 1; //si se encuentra el producto en el arreglo se cambia a 1
						}
					}
					if (producto_esta_en_productos == 0){ //si el producto no se encontro en el arreglo (valor 0) se muestra que no se encontro 
						printf("\n El producto no se encuentra en el sistema\n");
					}
				}else if(opcion2 == 2){
					printf("\n ---- BUSCAR PRODUCTOS POR SERIE ----\n");
					printf("Ingrese serie del producto: ");
					scanf("%d", &serie);
					for (i=0; i<n; i++){
						if (serie == productos[i].serie){
							mostrar_datos(productos[i]);
							producto_esta_en_productos = 1;
						}
					}
					if (producto_esta_en_productos == 0){
						printf("\n El producto no se encuentra en el sistema\n");
					}
				}else if (opcion2 == 3){
					printf("Volviendo al sistema... \n\n");
				}else{
					printf("\n\n ENTRADA INVALIDA, INTENTE NUEVAMENTE \n\n");
				}
			}
		}else if (opcion == 4){
			printf("\n\n SALIENDO DEL SISTEMA \n\n");
		}else{
			printf("\n\n ENTRADA INVALIDA, INTENTE NUEVAMENTE \n\n");
		}
	}
	//Se libera el arreglo productos al salir del sistema
	free(productos);
	return 0;
}

