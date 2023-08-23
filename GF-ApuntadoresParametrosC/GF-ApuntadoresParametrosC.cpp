#include <stdio.h>
#include <stdlib.h> // Include for malloc and free
#include <string.h>

#define MAX_LONG_NOMBRE 30
#define MAX_LONG_APELLIDO 30
#define MAX_LONG_TITULO 40

typedef struct libros {
    int id_libro;
    char nombres_autor[MAX_LONG_NOMBRE];
    char apellidos_autor[MAX_LONG_APELLIDO];
    char titulo[MAX_LONG_TITULO];
    int anio_compra;
    int num_prestamos;
    struct libros* sig;
} LIB;

LIB* buscar_libro(LIB* inicio, int clave) {
    //Encuentra el libro con la última clave que es menor o igual que la clave dada
    if (inicio == NULL) {
        return inicio;
    }

    LIB* actual = inicio; // Comienza desde el inicio de la lista

    // Recorre la lista mientras no sea NULL y el siguiente libro sea menor o igual a la clave
    while (actual->sig != NULL && actual->id_libro <= clave) {
        // Si encuentra un libro con clave mayor, se detiene
        if ((actual->sig)->id_libro > clave) {
            return actual; // Retorna el libro con la clave dada
        }
        actual = actual->sig; // Avanza al siguiente libro
    }

    return actual; // Retorna NULL si no se encontró un libro con la clave dada o si la lista es vacía
}


LIB* crear_libro(int* numLibros) {
    LIB* newLib = (LIB*)malloc(sizeof(LIB));

    // Ingresar detalles del libro
    printf("Agregar datos para un nuevo libro:\n");
    printf("Identificador del libro: ");
    scanf("%d", &(newLib->id_libro)); // Leer el ID del libro
    getchar(); // Consumir el carácter de nueva línea dejado en el búfer de entrada

    printf("Nombre del autor: ");
    fgets(newLib->nombres_autor, MAX_LONG_NOMBRE, stdin);
    newLib->nombres_autor[strcspn(newLib->nombres_autor, "\n")] = '\0'; // Eliminar el carácter de nueva línea

    printf("Apellido del autor: ");
    fgets(newLib->apellidos_autor, MAX_LONG_APELLIDO, stdin);
    newLib->apellidos_autor[strcspn(newLib->apellidos_autor, "\n")] = '\0'; // Eliminar el carácter de nueva línea

    printf("Título del libro: ");
    fgets(newLib->titulo, MAX_LONG_TITULO, stdin);
    newLib->titulo[strcspn(newLib->titulo, "\n")] = '\0'; // Eliminar el carácter de nueva línea

    printf("Año de compra: ");
    scanf("%d", &(newLib->anio_compra));

    printf("Número de préstamos: ");
    scanf("%d", &(newLib->num_prestamos));

    newLib->sig = NULL; // Inicializar el puntero 'sig'

    (*numLibros)++; // Incrementar la cantidad de libros

    return newLib;
}

int main() {
    int metodo = 0;
    int numLibros = 0; 

    printf("Bienvenido a la librería de Elmer \n");
    printf("1. Quiero insertar un libro \n");
    printf("2. Quiero borrar un libro \n");
    printf("3. Quiero saber el número de libros\n");
    printf("4. Quiero buscar un libro \n");
    printf("5. Quiero ver todos los libros\n");
    printf("-1. Salir\n"); // Incluir opción de salida

    do {
        scanf("%d", &metodo);

        switch (metodo) {
        case 1:
            // Llamar a tu función para crear e insertar un libro
            break;
        case 2:
            // Implementar la lógica para borrar un libro
            break;
        case 3:
            // Implementar la lógica para contar el número de libros
            break;
        case 4:
            // Implementar la lógica para buscar un libro
            break;
        case 5:
            // Implementar la lógica para mostrar todos los libros
            break;
        case -1:
            printf("Saliendo del programa.\n");
            break;
        default:
            printf("Opción no válida.\n");
            break;
        }
    } while (metodo != -1);

    return 0;
}

