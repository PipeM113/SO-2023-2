#ifndef funcs_h
#define funcs_h

#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <dirent.h>  
#include <sys/time.h>

int crearMatriz(FILE *nombreArchiv, char matriz[][400]); //crea una matriz de filas x columnas

void eliminar_rn(char *string); //elimina el \r\n de un string

void eliminarExtensionTxt(char *nombreArchivo); //elimina la extension .txt de un archivo

void convertirAMayusculas(char *cadena); //convierte una cadena a mayusculas

void crearDirectorios(); //crea los directorios que se utilizaran en el programa

void listarArchivosTxt(char archivosTxt[][256], int *numArchivos); //lista los archivos .txt que se encuentran en el directorio

void moverArchivo(char *nombreArchivo, char *directorioDestino); //mueve un archivo a un directorio

int resolver_horizontal(FILE *archivo, char *nombreArchivo); //resuelve la sopa de letras horizontalmente

int resolver_vertical(FILE *archivo, char *nombreArchivo); //resuelve la sopa de letras verticalmente

void resolver_sopa(char *nombreArchivo); //resuelve la sopa de letras

void resolver_sopa2(char *nombreArchivo); //resuelve la sopa de letras y retorna el tiempo que se demoro en resolverla

void buscarPalabra(char grid[][400], char* palabra, int tam , char* orientacion); //busca una palabra en la sopa de letras

#endif