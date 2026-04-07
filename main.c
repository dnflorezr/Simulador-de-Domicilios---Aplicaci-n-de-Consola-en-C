/*
 * ===========================
 *  Simulador de Domicilios
 * ===========================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definicion de los valores constantes
#define NUM_PRODUCTOS  6
#define MAX_CARRITO    20
#define COSTO_DOMICILIO 5000.0
#define IVA             0.19

//
typedef struct {
    int    id;
    char   nombre[50];
    double precio;
} Producto;

typedef struct {
    Producto producto;
    int      cantidad;
} ItemCarrito;

// Catalogo de productos disponibles
Producto catalogo[NUM_PRODUCTOS] = {
    {1, "Hamburguesa Clásica",   18500.0},
    {2, "Pizza Personal",        22000.0},
    {3, "Wrap de Pollo",         15000.0},
    {4, "Perro Caliente",        10500.0},
    {5, "Ensalada César",        13000.0},
    {6, "Combo Papas + Bebida",  12000.0}
};

// Cracion de carrito de compra
ItemCarrito carrito[MAX_CARRITO];
int numItems = 0;

//Definicion de la funciones adicionales o auxiliares (limpiar pantalla, pausar, imprimir y encabezados)
void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar() {
    printf("\n  Presiona Enter para continuar...");
    while (getchar() != '\n');
    getchar();
}

void imprimirLinea(char c, int n) {
    for (int i = 0; i < n; i++) putchar(c);
    putchar('\n');
}

void encabezado(const char *titulo) {
    limpiarPantalla();
    imprimirLinea('=', 50);
    printf("  🍔  %s\n", titulo);
    imprimirLinea('=', 50);
}

/* ══════════════════════════════════════════════
   1. Ver menú de productos
══════════════════════════════════════════════ */
void verMenuProductos() {
    encabezado("MENU DE PRODUCTOS");
    printf("\n  %-4s  %-25s  %s\n", "ID", "Producto", "Precio");
    imprimirLinea('-', 50);

    for (int i = 0; i < NUM_PRODUCTOS; i++) {
        printf("  [%d]  %-25s  $%.0f\n",
               catalogo[i].id,
               catalogo[i].nombre,
               catalogo[i].precio);
    }

    imprimirLinea('-', 50);
    pausar();
}

/* ══════════════════════════════════════════════
   2. Agregar producto al carrito
══════════════════════════════════════════════ */
Producto *buscarProducto(int id) {
    for (int i = 0; i < NUM_PRODUCTOS; i++) {
        if (catalogo[i].id == id)
            return &catalogo[i];
    }
    return NULL;
}

int buscarEnCarrito(int id) {
    for (int i = 0; i < numItems; i++) {
        if (carrito[i].producto.id == id)
            return i;
    }
    return -1;
}

void agregarProducto() {
    encabezado("AGREGAR AL CARRITO");

    /* Mostrar catálogo compacto */
    printf("\n  %-4s  %-25s  %s\n", "ID", "Producto", "Precio");
    imprimirLinea('-', 50);
    for (int i = 0; i < NUM_PRODUCTOS; i++) {
        printf("  [%d]  %-25s  $%.0f\n",
               catalogo[i].id,
               catalogo[i].nombre,
               catalogo[i].precio);
    }
    imprimirLinea('-', 50);

    int id, cantidad;

    printf("\n  Ingresa el ID del producto (0 para cancelar): ");
    if (scanf("%d", &id) != 1) { while (getchar() != '\n'); return; }
    while (getchar() != '\n');

    if (id == 0) return;

    Producto *p = buscarProducto(id);
    if (p == NULL) {
        printf("\n  Producto con ID %d no encontrado.\n", id);
        pausar();
        return;
    }

    /* Validar cantidad > 0 con do…while */
    do {
        printf("  Cantidad a agregar: ");
        if (scanf("%d", &cantidad) != 1) { cantidad = 0; }
        while (getchar() != '\n');

        if (cantidad <= 0)
            printf(" La cantidad debe ser mayor a 0. Intenta de nuevo.\n");

    } while (cantidad <= 0);

    if (numItems >= MAX_CARRITO) {
        printf("\n  El carrito está lleno (máximo %d ítems).\n", MAX_CARRITO);
        pausar();
        return;
    }

    /* Si ya existe en el carrito, sumar cantidad */
    int idx = buscarEnCarrito(id);
    if (idx >= 0) {
        carrito[idx].cantidad += cantidad;
        printf("\n Cantidad actualizada: %s x%d\n",
               p->nombre, carrito[idx].cantidad);
    } else {
        carrito[numItems].producto  = *p;
        carrito[numItems].cantidad  = cantidad;
        numItems++;
        printf("\n  Agregado: %s x%d\n", p->nombre, cantidad);
    }

    pausar();
}

/* ══════════════════════════════════════════════
   3. Ver carrito y total
══════════════════════════════════════════════ */
double calcularSubtotal() {
    double subtotal = 0.0;
    for (int i = 0; i < numItems; i++)
        subtotal += carrito[i].producto.precio * carrito[i].cantidad;
    return subtotal;
}

void verCarrito() {
    encabezado("TU CARRITO");

    if (numItems == 0) {
        printf("\n  El carrito está vacío.\n");
        pausar();
        return;
    }

    printf("\n  %-25s  %6s  %12s\n", "Producto", "Cant.", "Subtotal");
    imprimirLinea('-', 50);

    for (int i = 0; i < numItems; i++) {
        double sub = carrito[i].producto.precio * carrito[i].cantidad;
        printf("  %-25s  %6d  $%10.0f\n",
               carrito[i].producto.nombre,
               carrito[i].cantidad,
               sub);
    }

    imprimirLinea('-', 50);

    double subtotal = calcularSubtotal();
    double iva      = subtotal * IVA;
    double total    = subtotal + iva + COSTO_DOMICILIO;

    printf("  %-33s $%10.0f\n", "Subtotal:",         subtotal);
    printf("  %-33s $%10.0f\n", "IVA (19%):",        iva);
    printf("  %-33s $%10.0f\n", "Costo domicilio:",  COSTO_DOMICILIO);
    imprimirLinea('=', 50);
    printf("  %-33s $%10.0f\n", "TOTAL:",            total);
    imprimirLinea('=', 50);

    pausar();
}

/* ══════════════════════════════════════════════
   4. Confirmar pedido
══════════════════════════════════════════════ */
void confirmarPedido() {
    encabezado("CONFIRMAR PEDIDO");

    if (numItems == 0) {
        printf("\n  No hay productos en el carrito.\n");
        pausar();
        return;
    }

    /* Resumen */
    printf("\n  Resumen de tu pedido:\n\n");
    for (int i = 0; i < numItems; i++) {
        printf("    • %-25s x%d\n",
               carrito[i].producto.nombre,
               carrito[i].cantidad);
    }

    double subtotal = calcularSubtotal();
    double total    = subtotal + subtotal * IVA + COSTO_DOMICILIO;

    printf("\n  Total a pagar: $%.0f\n", total);
    imprimirLinea('-', 50);

    char confirm;
    printf("\n  ¿Confirmas el pedido? (s/n): ");
    scanf(" %c", &confirm);
    while (getchar() != '\n');

    if (confirm == 's' || confirm == 'S') {
        printf("\n");
        imprimirLinea('*', 50);
        printf("  ¡Pedido confirmado! En camino...\n");
        printf("  Tiempo estimado: 30-45 minutos\n");
        imprimirLinea('*', 50);

        /* Vaciar carrito */
        numItems = 0;
        memset(carrito, 0, sizeof(carrito));
    } else {
        printf("\n  Pedido cancelado. Tu carrito se mantiene.\n");
    }

    pausar();
}

/* ══════════════════════════════════════════════
   Menú principal
══════════════════════════════════════════════ */
void mostrarMenu() {
    encabezado("DOMICILIOS EXPRESS");
    printf("\n");
    printf("  [1]  Ver menú de productos\n");
    printf("  [2]  Agregar producto al carrito\n");
    printf("  [3]  Ver carrito y total\n");
    printf("  [4]  Confirmar pedido\n");
    printf("  [0]  Salir\n");
    printf("\n");
    imprimirLinea('-', 50);
    printf("  Opción: ");
}

int main(void) {
    int opcion;

    /* Bucle principal con while */
    while (1) {
        mostrarMenu();

        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n');
            opcion = -1;
        }
        while (getchar() != '\n');

        /* switch para despachar opciones */
        switch (opcion) {
            case 1:
                verMenuProductos();
                break;
            case 2:
                agregarProducto();
                break;
            case 3:
                verCarrito();
                break;
            case 4:
                confirmarPedido();
                break;
            case 0:
                encabezado("HASTA PRONTO");
                printf("\n  ¡Gracias por usar Domicilios Express! \n\n");
                return EXIT_SUCCESS;
            default:
                printf("\n Opción inválida. Elige entre 0 y 4.\n");
                pausar();
        }
    }
}
