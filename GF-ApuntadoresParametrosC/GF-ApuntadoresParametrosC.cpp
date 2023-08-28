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


LIB* buscar_libro(LIB* inicio, int clave, int numLibros) {
    // Encuentra el libro que apunta al libro con la última clave que es menor o igual que la clave dada

    if (numLibros == 0) {
        return inicio; // Regresa NULL si no hay libros en la lista
    }

    LIB* actual = inicio; // Comienza desde el inicio de la lista
    LIB* sigActual = actual->sig; // Obtiene el siguiente libro

    // Recorre la lista mientras no sea NULL y el siguiente libro sea menor o igual a la clave
    while (sigActual != NULL && sigActual->id_libro <= clave) {
        actual = actual->sig; // Avanza al siguiente libro
        sigActual = sigActual->sig; // Avanza al siguiente libro después del actual
    }

    return actual; // Retorna un puntero al libro que apunta al libro con la última clave menor o igual a la clave dada
}

void imprime_libro(LIB* libro) {
    // Imprime los detalles del libro dado
    printf("----------------------------------------------------------------------------------\n");
    printf("ID del libro: %d\n", libro->id_libro);
    printf("Autor: %s %s\n", libro->nombres_autor, libro->apellidos_autor);
    printf("Titulo: %s\n", libro->titulo);
    printf("Anio de compra: %d\n", libro->anio_compra);
    printf("Numero de prestamos: %d\n", libro->num_prestamos);
    printf("----------------------------------------------------------------------------------\n");
}

void mostrar_libro(LIB* inicio, int numLibros) {
    int id_libro;
    printf("Ingresa el id del libro que desea que se muestre:\n");
    printf("Identificador del libro: \n");
    scanf_s("%d", &id_libro); // Leer el ID del libro
    LIB* libro = buscar_libro(inicio, id_libro, numLibros);
    if (libro->sig != NULL && libro->sig->id_libro == id_libro) {
        imprime_libro(libro->sig);
    }
    //else Lanzar posible excepcion
}

void los_libros(LIB* inicio, int numLibros) {
    // Encuentra el libro que apunta al libro con la última clave que es menor o igual que la clave dada

    if (numLibros == 0) {
        printf("No hay libros que imprimir\n");
    }
    else {

        LIB* actual = inicio; // Comienza desde el inicio de la lista

        // Recorre la lista mientras no sea NULL y el siguiente libro sea menor o igual a la clave
        while (actual != NULL ) {
            imprime_libro(actual);
            actual = actual->sig; // Avanza al siguiente libro
        }
    }
}

void crear_libro(LIB* newLib) {

    // Ingresar detalles del libro
    printf("Agregar datos para un nuevo libro:\n");
    printf("Identificador del libro: ");
    scanf_s("%d", &(newLib->id_libro)); // Leer el ID del libro
    getchar(); // Consume the newline character left in the input buffer

    printf("Nombre del autor: ");
    fgets(newLib->nombres_autor, MAX_LONG_NOMBRE, stdin);
    newLib->nombres_autor[strcspn(newLib->nombres_autor, "\n")] = '\0'; // Eliminar el carácter de nueva línea

    printf("Apellido del autor: ");
    fgets(newLib->apellidos_autor, MAX_LONG_APELLIDO, stdin);
    newLib->apellidos_autor[strcspn(newLib->apellidos_autor, "\n")] = '\0'; // Eliminar el carácter de nueva línea

    printf("Titulo del libro: ");
    fgets(newLib->titulo, MAX_LONG_TITULO, stdin);
    newLib->titulo[strcspn(newLib->titulo, "\n")] = '\0'; // Eliminar el carácter de nueva línea

    printf("Anio de compra: ");
    scanf_s("%d", &(newLib->anio_compra));

    printf("Numero de prestamos: ");
    scanf_s("%d", &(newLib->num_prestamos));

    newLib->sig = NULL; // Inicializar el puntero 'sig'
}

void insertar_libro(LIB* inicio, int* numLibros) {
    if (*numLibros == 0) {
        crear_libro(inicio);
    }
    else {
        LIB* nuevoLibro = (LIB*)malloc(sizeof(LIB));
        crear_libro(nuevoLibro);
        LIB* aux = buscar_libro(inicio, nuevoLibro->id_libro, *numLibros);
        if (aux == inicio && nuevoLibro->id_libro < inicio->id_libro) {
            nuevoLibro->sig = inicio;
            inicio = nuevoLibro;
        }
        else {
            nuevoLibro->sig = aux->sig;
            aux->sig = nuevoLibro;
        }
    }
    (*numLibros)++;
}

void borrar_libro(LIB* inicio, int* numLibros) 
{
    int id_libro;
    printf("Ingresa el id del libro que desea borrar:\n");
    printf("Identificador del libro: ");
    scanf_s("%d", &id_libro); // Leer el ID del libro
    LIB* libro = buscar_libro(inicio, id_libro,*numLibros);
    if (libro->sig != NULL && libro->sig->id_libro == id_libro) {
        if (*numLibros == 1) {
            free(inicio);
        }
        else {
            LIB* aux = libro->sig;
            libro->sig = aux->sig;
            free(aux);
        }
        (*numLibros)--;
    }
    // No se encontro el libro
}
int main() {
    int metodo = 0;
    int numLibros = 0; 
    LIB* inicio = (LIB*) malloc(sizeof(LIB));

    printf("Bienvenido a la libreria de Elmer \n");
    printf("1. Quiero insertar un libro \n");
    printf("2. Quiero borrar un libro \n");
    printf("3. Quiero saber el numero de libros\n");
    printf("4. Quiero buscar un libro \n");
    printf("5. Quiero ver todos los libros\n");
    printf("-1. Salir\n"); // Incluir opción de salida

    do {
        printf("Ingresa la tarea que quieres realizar\n");
        scanf_s("%d", &metodo);

        switch (metodo) {
        case 1:
            insertar_libro(inicio, &numLibros);
            break;
        case 2:
            borrar_libro(inicio, &numLibros);
            break;
        case 3:
            printf("El número de libros que tenemos es: %d\n", numLibros);
            break;
        case 4:
            mostrar_libro(inicio,numLibros);
            break;
        case 5:
            los_libros(inicio,numLibros);
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

