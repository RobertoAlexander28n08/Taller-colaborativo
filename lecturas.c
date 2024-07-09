#include <stdio.h>
#include "lecturas.h"

int leerEntero(const char *mensaje) {
    int valor;
    printf("%s", mensaje);
    scanf("%d", &valor);
    return valor;
}

int leerEnteroPositivo(const char *mensaje) {
    int valor;
    do {
        printf("%s", mensaje);
        scanf("%d", &valor);
        if (valor <= 0) {
            printf("Ingrese un valor positivo.\n");
        }
    } while (valor <= 0);
    return valor;
}

float leerFlotante(const char *mensaje) {
    float valor;
    printf("%s", mensaje);
    scanf("%f", &valor);
    return valor;
}

float leerFlotantePositivo(const char *mensaje) {
    float valor;
    do {
        printf("%s", mensaje);
        scanf("%f", &valor);
        if (valor <= 0) {
            printf("Ingrese un valor positivo.\n");
        }
    } while (valor <= 0);
    return valor;
}

char leerCaracter(const char *mensaje) {
    char valor;
    printf("%s", mensaje);
    scanf(" %c", &valor);
    return valor;
}

int leerEnteroEntre(const char *mensaje, int minimo, int maximo) {
    int valor;
    do {
        printf("%s (entre %d y %d): ", mensaje, minimo, maximo);
        scanf("%d", &valor);
        if (valor < minimo || valor > maximo) {
            printf("Ingrese un valor entre %d y %d.\n", minimo, maximo);
        }
    } while (valor < minimo || valor > maximo);
    return valor;
}

float leerFlotanteEntre(const char *mensaje, float minimo, float maximo) {
    float valor;
    do {
        printf("%s (entre %.2f y %.2f): ", mensaje, minimo, maximo);
        scanf("%f", &valor);
        if (valor < minimo || valor > maximo) {
            printf("Ingrese un valor entre %.2f y %.2f.\n", minimo, maximo);
        }
    } while (valor < minimo || valor > maximo);
    return valor;
}



void leerCadena(char* buffer, int size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Eliminar el salto de línea final
}