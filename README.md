# Domicilios Express — Simulador de Consola en C

Aplicación de consola que simula un flujo básico de pedidos a domicilio, desarrollada en C puro.  
Aplica **condicionales** (`if/else`, `switch`) y **ciclos** (`while`, `do…while`, `for`).

---

## Funcionalidades

| Opción | Descripción |
|--------|-------------|
| 1 | Ver el catálogo completo de productos |
| 2 | Agregar ítems al carrito (con validación de ID y cantidad) |
| 3 | Ver carrito con subtotal, IVA 19 % y costo de domicilio |
| 4 | Confirmar pedido y vaciar el carrito |
| 0 | Salir de la aplicación |

### Catálogo de productos (6 ítems)
1. Hamburguesa Clásica — $18 500
2. Pizza Personal — $22 000
3. Wrap de Pollo — $15 000
4. Perro Caliente — $10 500
5. Ensalada César — $13 000
6. Combo Papas + Bebida — $12 000

### Cálculo del total
```
Total = Subtotal + IVA (19%) + Costo domicilio ($5 000)
```

---

##  Estructura del proyecto

```
domicilios/
├── main.c      # Código fuente completo
└── README.md   # Este archivo
```

---

##  Compilación y ejecución

### Linux / macOS
```bash
gcc -o domicilios main.c
./domicilios
```

### Windows (MinGW / GCC)
```bash
gcc -o domicilios.exe main.c
domicilios.exe
```

> Requiere únicamente GCC (estándar C99 o superior). Sin dependencias externas.

---

## 🧩 Estructuras de datos utilizadas

```c
typedef struct { int id; char nombre[50]; double precio; } Producto;
typedef struct { Producto producto; int cantidad; }         ItemCarrito;
```

- **Catálogo**: arreglo estático de 6 `Producto`.
- **Carrito**: arreglo de hasta 20 `ItemCarrito`; si el producto ya existe se acumula la cantidad.

---

## 🔁 Estructuras de control aplicadas

| Estructura | Uso |
|---|---|
| `switch` | Despacho del menú principal |
| `while` | Bucle principal de la aplicación |
| `do…while` | Validación de cantidad > 0 al agregar producto |
| `for` | Recorrer catálogo, carrito y calcular subtotales |
| `if / else` | Validación de ID, carrito vacío, confirmación |

---

Proyecto académico — Programación en C  
