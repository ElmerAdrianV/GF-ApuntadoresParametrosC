#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LONG_NOMBRE 30
#define MAX_LONG_APELLIDO 30
#define MAX_LONG_TITULO 40

// Define una estructura para un libro
typedef struct libros {
    int id_libro;
    char nombres_autor[MAX_LONG_NOMBRE];
    char apellidos_autor[MAX_LONG_APELLIDO];
    char titulo[MAX_LONG_TITULO];
    int anio_compra;
    int num_prestamos;
    struct libros* sig;
} LIB;

// Funcion para buscar un libro por su ID
LIB* buscar_libro(LIB* inicio, int clave) {
    if (inicio == NULL) {
        return NULL;
    }

    LIB* actual = inicio;
    // Para cuando acabe de recorrer la lista o sobre pase la clave ordenada
    while (actual != NULL && actual->id_libro <= clave) {
        if (actual->id_libro == clave) {
            return actual;
        }
        actual = actual->sig;
    }

    return NULL;
}

// Funcion para imprimir detalles de un libro
void mostrar_libro(LIB* libro) {
    if (libro == NULL) {
        printf("Libro no encontrado.\n");
    }
    else {
        printf("----------------------------------------------------------------------------------\n");
        printf("ID del libro: %d\n", libro->id_libro);
        printf("Autor: %s %s\n", libro->nombres_autor, libro->apellidos_autor);
        printf("Titulo: %s\n", libro->titulo);
        printf("Ano de compra: %d\n", libro->anio_compra);
        printf("Numero de prestamos: %d\n", libro->num_prestamos);
        printf("----------------------------------------------------------------------------------\n");
    }
}

// Funcion para mostrar todos los libros
void los_libros(LIB* inicio) {
    if (inicio == NULL) {
        printf("No hay libros que mostrar.\n");
    }
    else {
        //Iteramos sobre todos los libros que hay en la lista
        LIB* actual = inicio;
        while (actual != NULL) {
            mostrar_libro(actual);
            actual = actual->sig;
        }
    }
}

// Funcion para crear un nuevo libro
LIB* crear_libro() {
    LIB* newLib = (LIB*)malloc(sizeof(LIB));
    if (newLib == NULL) {
        printf("ERROR: No hay mas memoria disponible");
    }
    else {
        // Ingresar detalles del libro
        printf("Agregar datos para un nuevo libro:\n");
        printf("Identificador del libro: ");
        scanf_s("%d", &(newLib->id_libro)); // Leer el ID del libro
        getchar(); // Consume el caracter de nueva linea en el bufer de entrada

        printf("Nombre del autor: ");
        fgets(newLib->nombres_autor, MAX_LONG_NOMBRE, stdin);
        newLib->nombres_autor[strcspn(newLib->nombres_autor, "\n")] = '\0'; // Eliminar el caracter de nueva linea

        printf("Apellido del autor: ");
        fgets(newLib->apellidos_autor, MAX_LONG_APELLIDO, stdin);
        newLib->apellidos_autor[strcspn(newLib->apellidos_autor, "\n")] = '\0'; // Eliminar el caracter de nueva linea

        printf("Titulo del libro: ");
        fgets(newLib->titulo, MAX_LONG_TITULO, stdin);
        newLib->titulo[strcspn(newLib->titulo, "\n")] = '\0'; // Eliminar el caracter de nueva linea

        printf("Ano de compra: ");
        scanf_s("%d", &(newLib->anio_compra));

        printf("Numero de prestamos: ");
        scanf_s("%d", &(newLib->num_prestamos));

        newLib->sig = NULL;
    }
    
    return newLib;
}

LIB* busca_ultimo_libro_con_clave_menor(LIB* inicio, int id_libro_objetivo) {
    // Caso donde se inserta en medio o al final de la lista
    LIB* actual = inicio;
    // Se busca el ultimo libro con clave menor al nuevo libro para mantener el orden
    while (actual->sig != NULL && actual->sig->id_libro < id_libro_objetivo) {
        actual = actual->sig;
    }
    return actual;
}

// Funcion para insertar un libro en orden segun el ID
void insertar_libro(LIB** inicio) {
    LIB* nuevoLibro = crear_libro();
    if (nuevoLibro == NULL) {
        printf("ERROR: Crear libro fallo!");
    }
    else {
        //Caso donde se inserta un libro al inicio de la lista
        if (*inicio == NULL || nuevoLibro->id_libro < (*inicio)->id_libro) {
            nuevoLibro->sig = *inicio;
            *inicio = nuevoLibro;
        }
        else {
            // Caso donde se inserta en medio o al final de la lista
            // Se busca el ultimo libro con clave menor al nuevo libro para mantener el orden
            LIB* actual = busca_ultimo_libro_con_clave_menor(*inicio, nuevoLibro->id_libro);
            //Se hace el nuevo enlace correspondiente
            nuevoLibro->sig = actual->sig;
            actual->sig = nuevoLibro;
        }
    }
}

// Funcion para borrar un libro por su ID
void borrar_libro(LIB** inicio, int id_libro) {
   // Caso de la lista vacia
    if (*inicio == NULL) {
        printf("No hay libros que borrar.\n");
        return;
    }

    // Caso donde se borra el primer elemento de la lista
    if ((*inicio)->id_libro == id_libro) {
        LIB* aux = *inicio;
        *inicio = (*inicio)->sig;
        free(aux);
        return;
    }

    // Se busca el ultimo libro con clave menor al nuevo libro para mantener el orden
    LIB* actual = busca_ultimo_libro_con_clave_menor(*inicio,id_libro);

    //Si encontramos el libro con el id, lo eliminamos
    if (actual->sig != NULL && actual->sig->id_libro == id_libro) {
        LIB* aux = actual->sig;
        actual->sig = aux->sig;
        free(aux);
    }
    else {
        printf("Libro no encontrado.\n");
    }
}

// Funcion para contar el numero de libros en la lista
int num_libros(LIB* inicio) {
    int count = 0;
    LIB* actual = inicio;
    //Se recorre la lista completa contando
    while (actual != NULL) {
        count++;
        actual = actual->sig;
    }
    return count;
}

// Funcion para liberar la memoria de la lista de libros
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
            mostrar_libro(libroEncontrado);
            break;
        }
        case 5:
            los_libros(inicio);
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
