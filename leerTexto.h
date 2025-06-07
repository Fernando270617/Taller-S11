#include <stdio.h>

// Función para leer una línea de texto
void leerTexto(char texto[], int tamaño) {
    limpiarBuffer();                    // llamada a la función limpiarBuffer
    fgets(texto, tamaño, stdin);        // Lee la línea completa
    
    // Luego de la llamda se hace quita el /n y se remplaza por /0 para visaulizar toda la cadena guardad
    int len = strlen(texto);
    if (len > 0 && texto[len-1] == '\n') {
        texto[len-1] = '\0';
    }
}
