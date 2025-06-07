#include <stdio.h>

// Función para leer un número entero
int leerNumero() {
    int numero;
    while (scanf("%d", &numero) != 1) {  // Mientras no lea un número válido
        printf("Error: Ingrese un número válido: ");
        limpiarBuffer();                  // Limpia la entrada incorrecta
    }
    return numero;
}
