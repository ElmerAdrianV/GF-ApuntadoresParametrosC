#include <stdio.h>
#include <stdlib.h>
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
    if (inicio == NULL) {
        return NULL;
    }

    LIB* actual = inicio;
    while (actual != NULL && actual->id_libro <= clave) {
        if (actual->id_libro == clave) {
            return actual;
        }
        actual = actual->sig;
    }

    return NULL;
}

void imprime_libro(LIB* libro) {
    if (libro == NULL) {
        printf("Libro no encontrado.\n");
    }
    else {
        printf("----------------------------------------------------------------------------------\n");
        printf("ID del libro: %d\n", libro->id_libro);
        printf("Autor: %s %s\n", libro->nombres_autor, libro->apellidos_autor);
        printf("Titulo: %s\n", libro->titulo);
        printf("Anio de compra: %d\n", libro->anio_compra);
        printf("Numero de prestamos: %d\n", libro->num_prestamos);
        printf("----------------------------------------------------------------------------------\n");
    }
}

void mostrar_libros(LIB* inicio) {
    if (inicio == NULL) {
        printf("No hay libros que mostrar.\n");
    }
    else {
        LIB* actual = inicio;
        while (actual != NULL) {
            imprime_libro(actual);
            actual = actual->sig;
        }
    }
}

LIB* crear_libro() {
    LIB* newLib = (LIB*)malloc(sizeof(LIB));

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

    newLib->sig = NULL;
    return newLib;
}

void insertar_libro(LIB** inicio) {
    LIB* nuevoLibro = crear_libro();

    if (*inicio == NULL || nuevoLibro->id_libro < (*inicio)->id_libro) {
        nuevoLibro->sig = *inicio;
        *inicio = nuevoLibro;
    }
    else {
        LIB* actual = *inicio;
        while (actual->sig != NULL && actual->sig->id_libro < nuevoLibro->id_libro) {
            actual = actual->sig;
        }
        nuevoLibro->sig = actual->sig;
        actual->sig = nuevoLibro;
    }
}

void borrar_libro(LIB** inicio, int id_libro) {
    if (*inicio == NULL) {
        printf("No hay libros que borrar.\n");
        return;
    }

    if ((*inicio)->id_libro == id_libro) {
        LIB* aux = *inicio;
        *inicio = (*inicio)->sig;
        free(aux);
        return;
    }

    LIB* actual = *inicio;
    while (actual->sig != NULL && actual->sig->id_libro != id_libro) {
        actual = actual->sig;
    }

    if (actual->sig != NULL) {
        LIB* aux = actual->sig;
        actual->sig = aux->sig;
        free(aux);
    }
    else {
        printf("Libro no encontrado.\n");
    }
}

int num_libros(LIB* inicio) {
    int count = 0;
    LIB* actual = inicio;
    while (actual != NULL) {
        count++;
        actual = actual->sig;
    }
    return count;
}

void liberar_memoria(LIB* inicio) {
    while (inicio != NULL) {
        LIB* aux = inicio;
        inicio = inicio->sig;
        free(aux);
    }
}

int main() {
    int opcion;
    LIB* inicio = NULL;

    printf("Bienvenido a la libreria de Elmer\n");

    do {
        printf("1. Insertar un libro\n");
        printf("2. Borrar un libro\n");
        printf("3. Contar el numero de libros\n");
        printf("4. Buscar un libro\n");
        printf("5. Ver todos los libros\n");
        printf("-1. Salir\n");
        printf("Ingresa la tarea que quieres realizar: ");
        scanf_s("%d", &opcion);

        switch (opcion) {
        case 1:
            insertar_libro(&inicio);
            break;
        case 2:
            if (inicio != NULL) {
                int id;
                printf("Ingresa el ID del libro que deseas borrar: ");
                scanf_s("%d", &id);
                borrar_libro(&inicio, id);
            }
            else {
                printf("No hay libros que borrar.\n");
            }
            break;
        case 3:
            printf("Numero de libros actuales: %d\n", num_libros(inicio));
            break;
        case 4: {
            int id;
            printf("Ingresa el ID del libro que deseas buscar: ");
            scanf_s("%d", &id);
            LIB* libroEncontrado = buscar_libro(inicio, id);
            imprime_libro(libroEncontrado);
            break;
        }
        case 5:
            mostrar_libros(inicio);
            break;
        case -1:
            printf("Saliendo del programa.\n");
            break;
        default:
            printf("Opcion no valida.\n");
            break;
        }
    } while (opcion != -1);

    // Liberar la memoria antes de salir
    liberar_memoria(inicio);

    return 0;
}
