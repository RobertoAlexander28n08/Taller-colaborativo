#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventario.h"
#include "facturacion.h"

int main() {
    int opcion;

    while (1) {
        printf("\n---------Bienvenido a nuestra tienda--------\n");
        printf("1. Ingresar producto\n");
        printf("2. Modificar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Consultar producto\n");
        printf("5. Ver productos\n");
        printf("6. Ingresar cliente\n");
        printf("7. Modificar cliente\n");
        printf("8. Consultar cliente\n");
        printf("9. Listar clientes\n");
        printf("10. Facturar\n");
        printf("11. Buscar factura\n");
        printf("12. Listar facturas\n");
        printf("13. Salir\n");
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                ingresarProducto();
                break;
            case 2:
                modificarProducto();
                break;
            case 3:
                eliminarProducto();
                break;
            case 4:
                consultarProducto();
                break;
            case 5:
                verProductos();
                break;
            case 6:
                ingresarCliente();
                break;
            case 7:
                modificarCliente();
                break;
            case 8:
                consultarCliente();
                break;
            case 9:
                listarClientes();
                break;
            case 10:
                facturar();
                break;
            case 11:
                buscarFactura();
                break;
            case 12:
                listarFacturas();
                break;
            case 13:
                printf("Gracias por usar nuestra tienda. ¡Hasta luego!\n");
                return 0;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    }

    return 0;
}
