#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Nodo {
    char nombre[50];
    struct Nodo* siguiente;
};

void insertarAlFinal(struct Nodo** cabeza, const char* nombre) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    strncpy(nuevoNodo->nombre, nombre, sizeof(nuevoNodo->nombre));
    nuevoNodo->nombre[sizeof(nuevoNodo->nombre) - 1] = '\0';
    nuevoNodo->siguiente = NULL;

    if (*cabeza == NULL) {
        *cabeza = nuevoNodo;
    } else {
        struct Nodo* temp = *cabeza;
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoNodo;
    }
}

void mostrarLista(struct Nodo* cabeza) {
    printf("Nombres en la lista:\n");
    while (cabeza != NULL) {
        printf("%s -> ", cabeza->nombre);
        cabeza = cabeza->siguiente;
    }
    printf("NULL\n");
}

void eliminarNombre(struct Nodo** cabeza, const char* nombre) {
    if (*cabeza == NULL) {
        printf("La lista está vacía. No se puede eliminar.\n");
        return;
    }

    struct Nodo* actual = *cabeza;
    struct Nodo* anterior = NULL;

    while (actual != NULL && strcmp(actual->nombre, nombre) != 0) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        printf("El nombre '%s' no se encontró en la lista.\n", nombre);
        return;
    }

    if (anterior == NULL) {
        *cabeza = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    free(actual);
    printf("Se ha eliminado el nombre '%s' de la lista.\n");
}

int main() {
    struct Nodo* cabeza = NULL;
    char opcion;

    do {
        char nombre[50];
        printf("Ingrese un nombre: ");
        scanf("%s", nombre);

        insertarAlFinal(&cabeza, nombre);

        printf("¿Desea ingresar otro nombre? (S/N): ");
        scanf(" %c", &opcion);
    } while (opcion == 'S' || opcion == 's');

    mostrarLista(cabeza);

    char nombreEliminar[50];
    printf("Ingrese el nombre que desea eliminar: ");
    scanf("%s", nombreEliminar);

    eliminarNombre(&cabeza, nombreEliminar);
    mostrarLista(cabeza);

    while (cabeza != NULL) {
        struct Nodo* temp = cabeza;
        cabeza = cabeza->siguiente;
        free(temp);
    }

    return 0;
}