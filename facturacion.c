#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "facturacion.h"
#include "inventario.h"

#define ARCHIVO_CLIENTES "clientes.txt"
#define ARCHIVO_FACTURAS "facturacion.txt"
#define ARCHIVO_PRODUCTOS "productos.txt"  

FILE *archivoClientes;
FILE *archivoFacturas;

void ingresarCliente() {
    char nombre[50];
    int cedula;
    char direccion[100];
    char telefono[20];

    printf("Ingrese el nombre del cliente: ");
    scanf("%s", nombre);
    
    // Validación de la cédula
    do {
        printf("Ingrese la cédula del cliente");
        scanf("%d", &cedula);
        if (cedula < 1000000000 || cedula > 9999999999) {
            printf("El número de cédula es inválido.\n");
        }
    } while (cedula < 1000000000 || cedula > 9999999999);

    printf("Ingrese la dirección del cliente: ");
    scanf("%s", direccion);
    printf("Ingrese el teléfono del cliente: ");
    scanf("%s", telefono);

    archivoClientes = fopen(ARCHIVO_CLIENTES, "a");
    if (archivoClientes == NULL) {
        printf("No se pudo abrir el archivo %s.\n", ARCHIVO_CLIENTES);
        return;
    }

    fprintf(archivoClientes, "Nombre: %s\n", nombre);
    fprintf(archivoClientes, "Cédula: %d\n", cedula);
    fprintf(archivoClientes, "Dirección: %s\n", direccion);
    fprintf(archivoClientes, "Teléfono: %s\n", telefono);

    fclose(archivoClientes);
    printf("Cliente ingresado correctamente.\n");
}

void modificarCliente() {
    int cedula;
    char nombre[50], direccion[100], telefono[20];

    printf("Ingrese la cédula del cliente a modificar: ");
    scanf("%d", &cedula);

    archivoClientes = fopen(ARCHIVO_CLIENTES, "r");
    if (archivoClientes == NULL) {
        printf("No se pudo abrir el archivo %s.\n", ARCHIVO_CLIENTES);
        return;
    }

    FILE *tempArchivo = fopen("temp.txt", "w");
    if (tempArchivo == NULL) {
        printf("No se pudo crear el archivo temporal.\n");
        fclose(archivoClientes);
        return;
    }

    char linea[256];
    int encontrado = 0;

    while (fgets(linea, sizeof(linea), archivoClientes)) {
        if (strstr(linea, "Cédula: ") && atoi(&linea[8]) == cedula) {
            encontrado = 1;
            printf("Ingrese el nuevo nombre del cliente: ");
            scanf("%s", nombre);
            printf("Ingrese la nueva dirección del cliente: ");
            scanf("%s", direccion);
            printf("Ingrese el nuevo teléfono del cliente: ");
            scanf("%s", telefono);
            fprintf(tempArchivo, "Nombre: %s\n", nombre);
            fprintf(tempArchivo, "Cédula: %d\n", cedula);
            fprintf(tempArchivo, "Dirección: %s\n", direccion);
            fprintf(tempArchivo, "Teléfono: %s\n", telefono);
        } else {
            fprintf(tempArchivo, "%s", linea);
        }
    }

    fclose(archivoClientes);
    fclose(tempArchivo);

    if (encontrado) {
        remove(ARCHIVO_CLIENTES);
        rename("temp.txt", ARCHIVO_CLIENTES);
        printf("Cliente modificado correctamente.\n");
    } else {
        remove("temp.txt");
        printf("Cliente no encontrado.\n");
    }
}

void consultarCliente() {
    int cedula;
    printf("Ingrese la cédula del cliente a consultar: ");
    scanf("%d", &cedula);

    archivoClientes = fopen(ARCHIVO_CLIENTES, "r");
    if (archivoClientes == NULL) {
        printf("No se pudo abrir el archivo %s.\n", ARCHIVO_CLIENTES);
        return;
    }

    char linea[256];
    int encontrado = 0;

    while (fgets(linea, sizeof(linea), archivoClientes)) {
        if (strstr(linea, "Cédula: ") && atoi(&linea[8]) == cedula) {
            printf("Cliente encontrado:\n");
            printf("%s", linea);
            encontrado = 1;
            while (fgets(linea, sizeof(linea), archivoClientes) && linea[0] != '\n') {
                printf("%s", linea);
            }
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente no encontrado.\n");
    }

    fclose(archivoClientes);
}

void listarClientes() {
    archivoClientes = fopen(ARCHIVO_CLIENTES, "r");
    if (archivoClientes == NULL) {
        printf("No se pudo abrir el archivo %s.\n", ARCHIVO_CLIENTES);
        return;
    }

    char linea[256];
    printf("\nClientes en el archivo:\n");
    while (fgets(linea, sizeof(linea), archivoClientes)) {
        printf("%s", linea);
    }

    fclose(archivoClientes);
}

int obtenerUltimoNumeroFactura() {
    FILE *archivoFacturas = fopen(ARCHIVO_FACTURAS, "r");
    if (archivoFacturas == NULL) {
        return 0;  // Si no existe el archivo, retornar 0 como último número de factura
    }

    int ultimoNumero = 0;
    char linea[256];
    while (fgets(linea, sizeof(linea), archivoFacturas)) {
        if (strstr(linea, "Factura Nº: ")) {
            ultimoNumero = atoi(&linea[12]); // Obtener el número de la última factura
        }
    }

    fclose(archivoFacturas);
    return ultimoNumero;
}

void facturar() {
    int cedulaCliente, numProductos;
    float totalFactura = 0;

    printf("Ingrese la cédula del cliente: ");
    scanf("%d", &cedulaCliente);

    printf("Ingrese el número de productos a facturar: ");
    scanf("%d", &numProductos);

    // Obtener el número de factura único
    int numeroFactura = obtenerUltimoNumeroFactura() + 1;

    archivoFacturas = fopen(ARCHIVO_FACTURAS, "a");
    if (archivoFacturas == NULL) {
        printf("No se pudo abrir el archivo %s.\n", ARCHIVO_FACTURAS);
        return;
    }

    FILE *archivoClientes = fopen(ARCHIVO_CLIENTES, "r");
    if (archivoClientes == NULL) {
        printf("No se pudo abrir el archivo de clientes.\n");
        fclose(archivoFacturas);
        return;
    }

    char nombreCliente[50];
    char linea[256];
    int encontrado = 0;

    while (fgets(linea, sizeof(linea), archivoClientes)) {
        if (strstr(linea, "Cédula: ") && atoi(&linea[8]) == cedulaCliente) {
            encontrado = 1;
            fgets(linea, sizeof(linea), archivoClientes); // Leer nombre
            sscanf(linea, "Nombre: %[^\n]", nombreCliente); // Obtener el nombre del cliente
            break;
        }
    }

    fclose(archivoClientes);

    if (!encontrado) {
        printf("Cliente no encontrado.\n");
        fclose(archivoFacturas);
        return;
    }

    fprintf(archivoFacturas, "Factura Nº: %d\n", numeroFactura);
    fprintf(archivoFacturas, "Cliente: %s\n", nombreCliente);
    fprintf(archivoFacturas, "Productos:\n");

    for (int i = 0; i < numProductos; ++i) {
        char nombreProducto[50];
        float precioProducto;

        printf("Ingrese el nombre del producto %d: ", i + 1);
        scanf(" %[^\n]", nombreProducto);

        FILE *archivoProductos = fopen(ARCHIVO_PRODUCTOS, "r");
        if (archivoProductos == NULL) {
            printf("No se pudo abrir el archivo %s.\n", ARCHIVO_PRODUCTOS);
            fclose(archivoFacturas);
            return;
        }

        encontrado = 0;
        while (fgets(linea, sizeof(linea), archivoProductos)) {
            if (strstr(linea, "Nombre: ") && strstr(linea, nombreProducto)) {
                encontrado = 1;
                fgets(linea, sizeof(linea), archivoProductos); // Leer la línea siguiente (Color)
                fgets(linea, sizeof(linea), archivoProductos); // Leer la línea siguiente (Talla)
                fgets(linea, sizeof(linea), archivoProductos); // Leer la línea siguiente (Precio)
                sscanf(linea, "Precio: %f", &precioProducto); // Obtener el precio del producto
                totalFactura += precioProducto;
                fprintf(archivoFacturas, "  - %s, Precio: %.2f\n", nombreProducto, precioProducto);
                break;
            }
        }

        fclose(archivoProductos);

        if (!encontrado) {
            printf("Producto '%s' no encontrado.\n", nombreProducto);
        }
    }

    fprintf(archivoFacturas, "Total: %.2f\n", totalFactura);
    fprintf(archivoFacturas, "\n");

    fclose(archivoFacturas);
    printf("Factura Nº %d generada correctamente para el cliente %s.\n", numeroFactura, nombreCliente);
}

void buscarFactura() {
    archivoFacturas = fopen(ARCHIVO_FACTURAS, "r");
    if (archivoFacturas == NULL) {
        printf("No se pudo abrir el archivo %s.\n", ARCHIVO_FACTURAS);
        return;
    }

    int numeroFactura;
    printf("Ingrese el número de factura a buscar: ");
    scanf("%d", &numeroFactura);

    char linea[256];
    int encontradas = 0;

    while (fgets(linea, sizeof(linea), archivoFacturas)) {
        if (strstr(linea, "Factura Nº: ") && atoi(&linea[12]) == numeroFactura) {
            encontradas = 1;
            printf("Factura encontrada:\n");
            printf("%s", linea); // Imprimir la línea con el número de factura
            while (fgets(linea, sizeof(linea), archivoFacturas) && linea[0] != '\n') {
                printf("%s", linea); // Imprimir el resto de la factura hasta la línea en blanco
            }
            break;
        }
    }

    fclose(archivoFacturas);

    if (!encontradas) {
        printf("Factura no encontrada.\n");
    }
}

void listarFacturas() {
    archivoFacturas = fopen(ARCHIVO_FACTURAS, "r");
    if (archivoFacturas == NULL) {
        printf("No se pudo abrir el archivo %s.\n", ARCHIVO_FACTURAS);
        return;
    }

    char linea[256];
    printf("\nFacturas en el archivo:\n");
    while (fgets(linea, sizeof(linea), archivoFacturas)) {
        printf("%s", linea);
    }

    fclose(archivoFacturas);
}
