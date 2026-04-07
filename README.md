# Domicilios Express — Simulador de Consola en C

# Funcionalidades

| Opción | Descripción |
|--------|-------------|
| 1 | Ver el catálogo completo de productos
| 2 | Agregar ítems al carrito (con validación de ID y cantidad
| 3 | Ver carrito con subtotal, IVA 19 % y costo de domicilio
| 4 | Confirmar pedido y vaciar el carrito
| 0 | Salir de la aplicación

# Catálogo de producto
1. Hamburguesa Clásica — $18 500
2. Pizza Personal — $22 000
3. Wrap de Pollo — $15 000
4. Perro Caliente — $10 500
5. Ensalada César — $13 000
6. Combo Papas + Bebida — $12 000

# Cálculo del total
```
Total = Subtotal + IVA (19%) + Costo domicilio ($5 000)
```
#  Estructura del proyecto
```
domicilios/
├── main.c      # Código fuente completo
└── README.md   # Este archivo
```
##  Compilación y ejecución
### Windows
```bash
gcc -o domicilios.exe main.c
domicilios.exe
``
Proyecto académico — Programación en C  
