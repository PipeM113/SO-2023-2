#include "funcs.h"

int crearMatriz(FILE *nombreArchivo,char matriz[][400]){
    int i =0, j = 0;
    char line[400];
    while (fgets(line, 400, nombreArchivo)) {
        eliminar_rn(line);
        j = 0;
        char* token = strtok(line, " ");
        while (token != NULL) {
            matriz[i][j] = token[0];
            j++;
            token = strtok(NULL, " ");
        }
    i++;
    }
    return j;
}

void eliminar_rn(char *string) {
    size_t len = strlen(string);
    for (int i = len - 1; i >= 0; i--) {
        if (iscntrl(string[i])) {
            string[i] = '\0';
        }
    }
}

void eliminarExtensionTxt(char *nombreArchivo) {
    char *token = strtok(nombreArchivo, ".");
    if (token != NULL) {
        strcpy(nombreArchivo, token);
    }
}

void convertirAMayusculas(char *cadena) {
    for (int i = 0; cadena[i]; i++) {
        cadena[i] = toupper(cadena[i]);
    }
}
   
void crearDirectorios() {
    int resultado1 = mkdir("horizontal", 0777);
    int resultado2 = mkdir("vertical", 0777);
    
    if (resultado1 == 0 && resultado2 == 0) {
        printf("Directorios creados con éxito\n");
        
        int resultado3 = mkdir("horizontal/50x50", 0777);
        int resultado4 = mkdir("horizontal/100x100", 0777);
        int resultado5 = mkdir("horizontal/200x200", 0777);
        
        int resultado6 = mkdir("vertical/50x50", 0777);
        int resultado7 = mkdir("vertical/100x100", 0777);
        int resultado8 = mkdir("vertical/200x200", 0777);
        
        if (resultado3 == 0 && resultado4 == 0 && resultado5 == 0 && 
            resultado6 == 0 && resultado7 == 0 && resultado8 == 0) {
            printf("Subdirectorios creados con éxito\n");
        } else {
            perror("Error al crear los subdirectorios");
        }
        
    } else {
        perror("Error al crear los directorios");
    }
}

void listarArchivosTxt(char archivosTxt[][256], int *numArchivos) {
    DIR *directorio;
    struct dirent *entrada;

    directorio = opendir(".");
    if (directorio == NULL) {
        perror("Error al abrir el directorio");
        return;
    }

    *numArchivos = 0;

    while ((entrada = readdir(directorio)) != NULL) {
        if (entrada->d_type == DT_REG) {
            const char *nombreArchivo = entrada->d_name;
            const char *extension = ".txt";

            size_t longitudNombre = strlen(nombreArchivo);
            size_t longitudExtension = strlen(extension);

            if (longitudNombre >= longitudExtension &&
                strcmp(nombreArchivo + longitudNombre - longitudExtension, extension) == 0) {
                strncpy(archivosTxt[*numArchivos], nombreArchivo, sizeof(archivosTxt[*numArchivos]));
                (*numArchivos)++;
            }
        }
    }

    closedir(directorio);
}

void moverArchivo(char *nombreArchivo, char *directorioDestino) {
    char comando[256];
    snprintf(comando, sizeof(comando), "mv %s %s/%s", nombreArchivo, directorioDestino, nombreArchivo);

    int resultado = system(comando);
    
    if (resultado == 0) {
        printf("Archivo %s movido con éxito\n", nombreArchivo);
    } else {
        perror("Error al mover el archivo");
    }
}

int resolver_horizontal(FILE *archivo, char *nombreArchivo) {
    char palabra[100];
    strcpy(palabra, nombreArchivo);
    eliminarExtensionTxt(palabra);
    convertirAMayusculas(palabra);

    char linea[400];
    int tamanoSopa = 0;
    char line[200];

    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        strcpy(line, "");
        char *letra = strtok(linea, " \r\n");
        while ((letra != NULL)) {
            strcat(line, letra);
            letra = strtok(NULL, " ");
        }
        eliminar_rn(line);
        if (tamanoSopa < 50) {
            tamanoSopa = strlen(line);
        }
        if (strstr(line, palabra) != NULL) {
            return tamanoSopa;
        }
    }
    return tamanoSopa;
}

int resolver_vertical(FILE *archivo, char *nombreArchivo) {
    char palabra[100];
    strcpy(palabra, nombreArchivo);
    eliminarExtensionTxt(palabra);
    convertirAMayusculas(palabra);

    char linea[400];
    char columnas[400][400];
    int anchoSopa = 0;

    // Leer y procesar cada línea
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        char *letra = strtok(linea, " "); // Usar espacio como delimitador
        int columna = 0;
        while (letra != NULL) {
            strcpy(columnas[columna], letra);
            letra = strtok(NULL, " ");
            columna++;
        }
        if (anchoSopa == 0) {
            anchoSopa = columna; // Actualiza el ancho de la sopa en la primera línea
        }

    }

    // Buscar la palabra en cada columna
    for (int j = 0; j < anchoSopa; j++) {
        if (strstr(columnas[j], palabra) != NULL) {
            return anchoSopa;
        }
    }
    return anchoSopa;
}

void resolver_sopa(char *nombreArchivo){
    //struct timeval start_time, end_time;
    char orientacion[11];
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }
    fgets(orientacion, 11, archivo);
    if (strcmp(orientacion, "horizontal")== 0){
        //gettimeofday(&start_time, NULL);
        int tam = resolver_horizontal(archivo, nombreArchivo);
        //gettimeofday(&end_time, NULL);
        //double time_spent = ((double) end_time.tv_sec + end_time.tv_usec / 1e6) - ((double) start_time.tv_sec + start_time.tv_usec / 1e6);
        //printf("Tiempo de resolucion de %s:  %.15f s, tamaño %d\n", nombreArchivo, time_spent, tam);
        fclose(archivo);
        if (tam == 50){ 
            moverArchivo(nombreArchivo, "horizontal/50x50");
        } 
        else if (tam == 100){
                moverArchivo(nombreArchivo, "horizontal/100x100");
        } else if (tam == 200){
                moverArchivo(nombreArchivo, "horizontal/200x200");
            } 
    }
    else{
        //gettimeofday(&start_time, NULL);
        int tam = resolver_vertical(archivo, nombreArchivo);
        //gettimeofday(&end_time, NULL);
        //double time_spent = ((double) end_time.tv_sec + end_time.tv_usec / 1e6) - ((double) start_time.tv_sec + start_time.tv_usec / 1e6);
        //printf("Tiempo de resolucion de %s:  %.15f s, tamaño %d\n", nombreArchivo, time_spent, tam);
        fclose(archivo);
        if (tam == 50){ 
            moverArchivo(nombreArchivo, "vertical/50x50");
        } 
        else if (tam == 100){
                moverArchivo(nombreArchivo, "vertical/100x100");
        } 
        else if (tam == 200){
                moverArchivo(nombreArchivo, "vertical/200x200");
            }
    }
}

void resolver_sopa2(char *nombreArchivo){
    struct timeval start_time, end_time;
    char orientacion[11];
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }
    fgets(orientacion, 11, archivo);
    char matriz[400][400];
    int tam = crearMatriz(archivo, matriz);
    char palabra[100];
    strcpy(palabra, nombreArchivo);
    eliminarExtensionTxt(palabra);
    gettimeofday(&start_time, NULL);
    buscarPalabra(matriz, palabra, tam, orientacion);
    gettimeofday(&end_time, NULL);
    double time_spent = ((double) end_time.tv_sec + end_time.tv_usec / 1e6) - ((double) start_time.tv_sec + start_time.tv_usec / 1e6);
    printf("Tiempo de resolucion de %s:  %.15f s, tamaño %d \n", nombreArchivo, time_spent, tam);
    fclose(archivo);
}

void buscarPalabra(char grid[][400], char* palabra, int tam , char* orientacion) {
    int longitud = strlen(palabra);

    // Convertimos la palabra a mayúsculas
    convertirAMayusculas(palabra);

    // Recorremos la sopa de letras
    for (int row = 0; row < tam; row++) {
        for (int col = 0; col < tam; col++) {
            // Comprobamos horizontalmente hacia la derecha
            if (strcmp(orientacion, "horizontal") == 0 && col + longitud <= tam) {
                int k;
                for (k = 0; k < longitud; k++) {
                    if (grid[row][col + k] != palabra[k])
                        break;
                }
                if (k == longitud) {
                    return;
                }
            }
            // Comprobamos verticalmente hacia abajo
            else if (strcmp(orientacion, "vertical") == 0 && row + longitud <= tam) {
                int k;
                for (k = 0; k < longitud; k++) {
                    if (grid[row + k][col] != palabra[k])
                        break;
                }
                if (k == longitud) {
                    return;
                }
            }
        }
    }
}