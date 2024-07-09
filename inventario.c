#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventario.h"

#define ARCHIVO_PRODUCTOS "productos.txt"

FILE *archivoProductos;

typedef struct {
    char nombre[50];
    char color[50];
    char talla[50];
    float precio;
} Producto;

void guardarProductosEnArchivo(Producto *productos, int numProductos) {
    archivoProductos = fopen(ARCHIVO_PRODUCTOS, "w");
    if (archivoProductos == NULL) {
        printf("No se pudo abrir el archivo %s.\n", ARCHIVO_PRODUCTOS);
        return;
    }

    for (int i = 0; i < numProductos; i++) {
        fprintf(archivoProductos, "Nombre: %s\n", productos[i].nombre);
        fprintf(archivoProductos, "Color: %s\n", productos[i].color);
        fprintf(archivoProductos, "Talla: %s\n", productos[i].talla);
        fprintf(archivoProductos, "Precio: %.2f\n", productos[i].precio);
    }

    fclose(archivoProductos);
}

void ingresarProducto() {
    Producto producto;

    printf("Ingrese el nombre del producto: ");
    scanf("%s", producto.nombre);

    printf("Ingrese el color del producto: ");
    scanf("%s", producto.color);

    printf("Ingrese la talla del producto: ");
    scanf("%s", producto.talla);

    printf("Ingrese el precio del producto: ");
    scanf("%f", &producto.precio);

    archivoProductos = fopen(ARCHIVO_PRODUCTOS, "a");
    if (archivoProductos == NULL) {
        printf("No se pudo abrir el archivo %s.\n", ARCHIVO_PRODUCTOS);
        return;
    }

    fprintf(archivoProductos, "Nombre: %s\n", producto.nombre);
    fprintf(archivoProductos, "Color: %s\n", producto.color);
    fprintf(archivoProductos, "Talla: %s\n", producto.talla);
    fprintf(archivoProductos, "Precio: %.2f\n", producto.precio);

    fclose(archivoProductos);
    printf("Producto ingresado correctamente.\n");
}

void modificarProducto() {
    char nombreProducto[50];
    printf("Ingrese el nombre del producto a modificar: ");
    scanf("%s", nombreProducto);

    archivoProductos = fopen(ARCHIVO_PRODUCTOS, "r");
    if (archivoProductos == NULL) {
        printf("No se pudo abrir el archivo %s.\n", ARCHIVO_PRODUCTOS);
        return;
    }

    FILE *tempArchivo = fopen("temp.txt", "w");
    if (tempArchivo == NULL) {
        printf("No se pudo crear el archivo temporal.\n");
        fclose(archivoProductos);
        return;
    }

    char linea[256];
    int encontrado = 0;

    while (fgets(linea, sizeof(linea), archivoProductos)) {
        if (strstr(linea, "Nombre:")) {
            char nombre[50];
            sscanf(linea, "Nombre: %[^\n]", nombre);

            if (strcmp(nombre, nombreProducto) == 0) {
                encontrado = 1;
                printf("Ingrese el nuevo nombre del producto: ");
                scanf("%s", linea); // Aquí podrías usar un scanf("%s", producto.nombre) si prefieres.
                fprintf(tempArchivo, "Nombre: %s\n", linea); // Aquí modificarías el nombre del producto.
                fgets(linea, sizeof(linea), archivoProductos); // Saltar la línea actual (Color).
                printf("Ingrese el nuevo color del producto: ");
                scanf("%s", linea); // Aquí podrías usar un scanf("%s", producto.color) si prefieres.
                fprintf(tempArchivo, "Color: %s\n", linea); // Aquí modificarías el color.
                fgets(linea, sizeof(linea), archivoProductos); // Saltar la línea actual (Talla).
                printf("Ingrese la nueva talla del producto: ");
                scanf("%s", linea); // Aquí podrías usar un scanf("%s", producto.talla) si prefieres.
                fprintf(tempArchivo, "Talla: %s\n", linea); // Aquí modificarías la talla.
                fgets(linea, sizeof(linea), archivoProductos); // Saltar la línea actual (Precio).
                fprintf(tempArchivo, "%s", linea); // Conservar la línea de Precio sin modificar.
            } else {
                fprintf(tempArchivo, "%s", linea); // Conservar la línea sin modificar.
            }
        } else {
            fprintf(tempArchivo, "%s", linea); // Conservar la línea sin modificar.
        }
    }

    fclose(archivoProductos);
    fclose(tempArchivo);

    if (encontrado) {
        remove(ARCHIVO_PRODUCTOS);
        rename("temp.txt", ARCHIVO_PRODUCTOS);
        printf("Producto modificado correctamente.\n");
    } else {
        remove("temp.txt");
        printf("Producto no encontrado.\n");
    }
}

void eliminarProducto() {
    char nombreProducto[50];
    printf("Ingrese el nombre del producto a eliminar: ");
    scanf("%s", nombreProducto);

    archivoProductos = fopen(ARCHIVO_PRODUCTOS, "r");
    if (archivoProductos == NULL) {
        printf("No se pudo abrir el archivo %s.\n", ARCHIVO_PRODUCTOS);
        return;
    }

    FILE *tempArchivo = fopen("temp.txt", "w");
    if (tempArchivo == NULL) {
        printf("No se pudo crear el archivo temporal.\n");
        fclose(archivoProductos);
        return;
    }

    char linea[256];
    int encontrado = 0;

    while (fgets(linea, sizeof(linea), archivoProductos)) {
        if (strstr(linea, "Nombre:")) {
            char nombre[50];
            sscanf(linea, "Nombre: %[^\n]", nombre);

            if (strcmp(nombre, nombreProducto) == 0) {
                encontrado = 1;
                // Saltamos las siguientes líneas que pertenecen al producto.
                fgets(linea, sizeof(linea), archivoProductos); // Color
                fgets(linea, sizeof(linea), archivoProductos); // Talla
                fgets(linea, sizeof(linea), archivoProductos); // Precio
            } else {
                fprintf(tempArchivo, "%s", linea); // Conservar la línea sin modificar.
            }
        } else {
            fprintf(tempArchivo, "%s", linea); // Conservar la línea sin modificar.
        }
    }

    fclose(archivoProductos);
    fclose(tempArchivo);

    if (encontrado) {
        remove(ARCHIVO_PRODUCTOS);
        rename("temp.txt", ARCHIVO_PRODUCTOS);
        printf("Producto eliminado correctamente.\n");
    } else {
        remove("temp.txt");
        printf("Producto no encontrado.\n");
    }
}

void consultarProducto() {
    char nombreProducto[50];
    printf("Ingrese el nombre del producto a consultar: ");
    scanf("%s", nombreProducto);

    archivoProductos = fopen(ARCHIVO_PRODUCTOS, "r");
    if (archivoProductos == NULL) {
        printf("No se pudo abrir el archivo %s.\n", ARCHIVO_PRODUCTOS);
        return;
    }

    char linea[256];
    int encontrado = 0;

    while (fgets(linea, sizeof(linea), archivoProductos)) {
        if (strstr(linea, "Nombre:")) {
            char nombre[50];
            sscanf(linea, "Nombre: %[^\n]", nombre);

            if (strcmp(nombre, nombreProducto) == 0) {
                printf("Producto encontrado:\n");
                printf("%s", linea); // Imprimir la línea del nombre
                fgets(linea, sizeof(linea), archivoProductos); // Color
                printf("%s", linea); // Imprimir la línea del color
                fgets(linea, sizeof(linea), archivoProductos); // Talla
                printf("%s", linea); // Imprimir la línea de la talla
                fgets(linea, sizeof(linea), archivoProductos); // Precio
                printf("%s", linea); // Imprimir la línea del precio
                encontrado = 1;
                break;
            }
        }
    }

    if (!encontrado) {
        printf("Producto no encontrado.\n");
    }

    fclose(archivoProductos);
}

void verProductos() {
    archivoProductos = fopen(ARCHIVO_PRODUCTOS, "r");
    if (archivoProductos == NULL) {
        printf("No se pudo abrir el archivo %s.\n", ARCHIVO_PRODUCTOS);
        return;
    }

    char linea[256];
    printf("\nProductos en el archivo:\n");
    while (fgets(linea, sizeof(linea), archivoProductos)) {
        printf("%s", linea);
    }

    fclose(archivoProductos);
}
