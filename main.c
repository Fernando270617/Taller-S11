
#include <stdio.h>      
#include <string.h>     
#include "mostrarMenu.h"
#include "leerTexto.h"
#include "leerNumero.h"

//Constantes
#define MAX_LIBROS 10      // número de libros máximos
#define MAX_TITULO 100     // caracteres para título max 100
#define MAX_AUTOR 50    // caracteres para autor

// Estructuras de libro 
struct Libro {
    int id;                     // Número único del libro para cadenas
    char titulo[MAX_TITULO];    // Nombre del libro en cadena 
    char autor[MAX_AUTOR];      // Nombre del autor en cadena 
    int anio;                   // Año de publicación dentro de la cadena
    char estado[20];            // Estado del libro está o no disponible 
};

// Definición de estructura global para todas las funciones
struct Libro libros[MAX_LIBROS];  // Para guardar todos los libros
int totalLibros = 0;              // Contador de libros guardados

// Función para limpiar la variable almacenada de entrada
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); //Esto evita que se limpie \n evitando que se salte de líena
}

// Función con retorno para verificar si un "id" ya existe o no 
int existeID(int id) {
    for (int i = 0; i < totalLibros; i++) {
        if (libros[i].id == id) {
            return 1;  // Sí existe el libro 
        }
    }
    return 0;  // No existe el libro
}

// Función para agregar un libro nuevo
void agregarLibro() {
    // Verificar si hay espacio
    if (totalLibros >= MAX_LIBROS) {
        printf("No se pueden agregar más libros ya registraste máximo %d)\n", MAX_LIBROS);
        return;
    }
    
    printf("\nAgregar nuevo libro\n");
    
    int id;
    do {
        printf("ID del libro: ");
        id = leerNumero();
        if (existeID(id)) {
            printf("El 'id' %d ya existe. \n Use otro:\n", id);
        }
    } while (existeID(id));
    
    libros[totalLibros].id = id;
    
    // Leer título
    printf("Título: ");
    leerTexto(libros[totalLibros].titulo, MAX_TITULO);
    
    // Leer autor
    printf("Autor: ");
    
    leerTexto(libros[totalLibros].autor, MAX_AUTOR);
    
    // Leer año
    printf("Año de publicación: ");
    
    libros[totalLibros].anio = leerNumero();
    
    // Mostrar libro disponible al agregar libro 
    strcpy(libros[totalLibros].estado, "Libro Disponible");
    
    totalLibros++;  // Aumentar contador de libros para otro registro
    printf("Libro agregado exitosamente\n");
}

// Función Mostrar todos los libros
void mostrarLibros() {
    if (totalLibros == 0) {
        printf("No hay libros registrados.\n");
        return;
    }
    
    printf("\n--- LISTA DE LIBROS ---\n");
    printf("ID\tTitulo\t\t\tAutor\t\tAño\tEstado\n");
    printf("----------------------------------------------------------------\n");
    
    for (int i = 0; i < totalLibros; i++) {
        printf("%d\t%s\t%s\t%d\t%s\n", libros[i].id, libros[i].titulo, libros[i].autor, libros[i].anio, libros[i].estado);
    }
}

// Función buscar un libro
void buscarLibro() {
    if (totalLibros == 0) {
        printf("No hay libros para buscar.\n");
        return;
    }
    
    printf("\n--- Escoger la opcion para buscar el libro ---\n");
    printf("1. Buscar por ID\n");
    printf("2. Buscar por título\n");
    printf("Puede buscar esta información en la opcion 2 del menú principal si no tiene la informacio\n");
    printf("Seleccione opción: ");
    
    int opcion = leerNumero();
    int encontrado = 0;
    
    if (opcion == 1) {
        // Buscar por ID
        printf("Ingrese ID a buscar: ");
        int id = leerNumero();
        
        for (int i = 0; i < totalLibros; i++) {
            if (libros[i].id == id) {
                printf("\nLIBRO ENCONTRADO \n\n");
                printf("ID: %d\n", libros[i].id);
                printf("Título: %s\n", libros[i].titulo);
                printf("Autor: %s\n", libros[i].autor);
                printf("Año: %d\n", libros[i].anio);
                printf("Estado: %s\n", libros[i].estado);
                encontrado = 1;
                break;
            }
        }
    }
    else if (opcion == 2) {
        // Buscar por título
        char titulo[MAX_TITULO];
        printf("Ingrese título a buscar: ");
        leerTexto(titulo, MAX_TITULO);
        
        for (int i = 0; i < totalLibros; i++) {
            if (strcmp(libros[i].titulo, titulo) == 0) {
                printf("\n--- LIBRO ENCONTRADO ---\n");
                printf("ID: %d\n", libros[i].id);
                printf("Título: %s\n", libros[i].titulo);
                printf("Autor: %s\n", libros[i].autor);
                printf("Año: %d\n", libros[i].anio);
                printf("Estado: %s\n", libros[i].estado);
                encontrado = 1;
                break;
            }
        }
    }
    else {
        printf("Opción inválida.\n");
        return;
    }
    
    if (!encontrado) {
        printf("Libro no encontrado.\n");
    }
}

// Función Cambiar estado de un libro
void cambiarEstado() {
    if (totalLibros == 0) {
        printf("No hay libros registrados.\n");
        return;
    }
    
    printf("\n--- CAMBIAR ESTADO ---\n");
    printf("Ingrese ID del libro: ");
    int id = leerNumero();
    
    // Buscar el libro
    for (int i = 0; i < totalLibros; i++) {
        if (libros[i].id == id) {
            printf("Libro: %s\n", libros[i].titulo);
            printf("Estado actual: %s\n", libros[i].estado);
            
            // Cambiar el estado
            if (strcmp(libros[i].estado, "Disponible") == 0) {
                strcpy(libros[i].estado, "Prestado");
                printf("Estado cambiado a: Prestado\n");
            } else {
                strcpy(libros[i].estado, "Disponible");
                printf("Estado cambiado a: Disponible\n");
            }
            return;
        }
    }
    
    printf("Libro con ID %d no encontrado.\n", id);
}

// Función Eliminar un libro
void eliminarLibro() {
    if (totalLibros == 0) {
        printf("No hay libros para eliminar.\n");
        return;
    }
    
    printf("\n--- ELIMINAR LIBRO ---\n");
    printf("Ingrese ID del libro a eliminar: ");
    int id = leerNumero();
    
    // Buscar el libro
    for (int i = 0; i < totalLibros; i++) {
        if (libros[i].id == id) {
            printf("¿Desea Eliminar el libro '%s'? \n Presione(s/n)\nSi = s\nNo = n\n Ingrese:", libros[i].titulo);
            limpiarBuffer();
            char respuesta = getchar();
            
            if (respuesta == 's' || respuesta == 'S') {
                // Mover todos los libros hacia atrás para llenar el hueco
                for (int j = i; j < totalLibros - 1; j++) {
                    libros[j] = libros[j + 1];
                }
                totalLibros--;  // Reducir contador
                printf("El libro ha sido eliminado.\n");
            } else {
                printf("Ha decidido cancelar la eliminación.\n");
            }
            return;
        }
    }
    
    printf("Libro con ID %d no encontrado.\n", id);
}

// Menu principal
int main() {
    int opcion;
    
    printf("===== SISTEMA DE BIBLIOTECA =====\n");
    printf("Bienvenido al sistema de gestión\n");
    
    do {
        mostrarMenu();
        opcion = leerNumero();
        
        switch (opcion) {
            case 1:
                system("clear");  //limpieza de pantalla
                agregarLibro();
                break;
            case 2:
                system("clear"); 
                mostrarLibros();
                break;
            case 3:
                system("clear"); 
                buscarLibro();
                break;
            case 4:
                system("clear"); 
                cambiarEstado();
                break;
            case 5:
                system("clear"); 
                eliminarLibro();
                break;
            case 6:
                printf("Gracias vuelva pronto\n");
                break;
            default:
                printf("Opción inválida. Intente de nuevo.\n");
        }
    } while (opcion != 6);
    
    return 0;
}
