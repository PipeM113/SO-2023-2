#include "funcs.h"

void iniciar_tablero(char**tablero, int filas, int columnas, char** n_tablero, int j_pos[4][2]){
    for (int i = 0; i<filas; i++){
        for (int j = 0; j<columnas; j++){
            if (i >=5 && i < 10 && j>=5 && j<10){
                tablero[i][j] = n_tablero[i-5][j-5];
                if (tablero[i][j]=='a'){
                    j_pos[0][0] = i;
                    j_pos[0][1] = j;
                }
                else if (tablero[i][j]=='b'){
                    j_pos[1][0] = i;
                    j_pos[1][1] = j;
                }
                else if (tablero[i][j]=='c'){
                    j_pos[2][0] = i;
                    j_pos[2][1] = j;
                }
                else if (tablero[i][j]=='d'){
                    j_pos[3][0] = i;
                    j_pos[3][1] = j;
                }
            }
            else{
                tablero[i][j] = '/';
            }
        }
    }
}

void crear_tablero(char **tablero, FILE *inicio, int j_pos[4][2]){
    int jugador,k;
    char casilla;
    for(int i = 0; i < 5 ; i++){
        k = 0; // el tablero es de 5x5 pero los jugadores se denominan Jn con n de 1 a 4 por lo que si aparece uno de estos caracteres se debe ignorar
        for(int j = 0; j < 11 && k<5; j++){
            fscanf(inicio, "%c", &casilla);
            if (casilla == 'J'){
                fscanf(inicio, "%d ", &jugador);
                if (jugador == 1){
                    tablero[i][k]= 'a';
                    j_pos[0][0] = i;
                    j_pos[0][1] = k;
                }
                else if(jugador == 2){
                    tablero[i][k]= 'b';
                    j_pos[1][0] = i;
                    j_pos[1][1] = k;
                }
                else if (jugador == 3){
                    tablero[i][k]= 'c';
                    j_pos[2][0] = i;
                    j_pos[2][1] = k;
                }
                else if (jugador == 4){
                    tablero[i][k]= 'd';
                    j_pos[3][0] = i;
                    j_pos[3][1] = k;
                }
                k++;
                j++;
            }
            else if (casilla == '0' || casilla == '/' || casilla == 'B' || casilla == 'E' || casilla == '1'|| casilla == '2' || casilla == '3' || casilla == '4'){
                tablero[i][k]= casilla;
                k++;
            } 
        }
    }
}       
            
void ubicar_tablero(char** tablero, char** n_tablero, int filas, int columnas, int i, int j){
    for (int k = 0; k < 5; k++){
        for (int l = 0; l < 5; l++){
            tablero[i+k][j+l] = n_tablero[k][l];
        }
    }
}

void ampliar_tablero(char*** tablero, int *filas, int *columnas, char direccion, int j_pos[4][2]){
    char** n_tablero;
    int f = *filas;
    if (direccion=='u'||direccion=='d'){
        *filas = *filas+5;
        n_tablero=(char**)malloc(*filas*sizeof(char*));
        for (int i = 0; i < *filas; i++){
            n_tablero[i]=(char*)malloc(*columnas*sizeof(char));
        }
        for (int i = 0; i < *filas; i++){
            for (int j = 0; j < *columnas; j++){
                if (direccion=='u'){
                    if (i<5){
                        n_tablero[i][j] = '/';
                    }
                    else{
                        n_tablero[i][j] = (*tablero)[i-5][j];
                        if (n_tablero[i][j]=='a'){
                            j_pos[0][0] = i;
                            j_pos[0][1] = j;
                        }
                        else if (n_tablero[i][j]=='b'){
                            j_pos[1][0] = i;
                            j_pos[1][1] = j;
                        }
                        else if (n_tablero[i][j]=='c'){
                            j_pos[2][0] = i;
                            j_pos[2][1] = j;
                        }
                        else if (n_tablero[i][j]=='d'){
                            j_pos[3][0] = i;
                            j_pos[3][1] = j;
                        }
                    }
                }
                else{
                    if (i>*filas-6){
                        n_tablero[i][j] = '/';
                    }
                    else{
                        n_tablero[i][j] = (*tablero)[i][j];
                        if (n_tablero[i][j]=='a'){
                            j_pos[0][0] = i;
                            j_pos[0][1] = j;
                        }
                        else if (n_tablero[i][j]=='b'){
                            j_pos[1][0] = i;
                            j_pos[1][1] = j;
                        }
                        else if (n_tablero[i][j]=='c'){
                            j_pos[2][0] = i;
                            j_pos[2][1] = j;
                        }
                        else if (n_tablero[i][j]=='d'){
                            j_pos[3][0] = i;
                            j_pos[3][1] = j;
                        }
                    }
                }
            }
        }
    }
    else{
        *columnas = *columnas+5;
        n_tablero=(char**)malloc(*filas*sizeof(char*));
        for (int i = 0; i < *filas; i++){
            n_tablero[i]=(char*)malloc(*columnas*sizeof(char));
            for (int j = 0; j < *columnas; j++){
                if (direccion=='l'){
                    if (j<5){
                        n_tablero[i][j] = '/';
                    }
                    else{
                        n_tablero[i][j] = (*tablero)[i][j-5];
                        if (n_tablero[i][j]=='a'){
                            j_pos[0][0] = i;
                            j_pos[0][1] = j;
                        }
                        else if (n_tablero[i][j]=='b'){
                            j_pos[1][0] = i;
                            j_pos[1][1] = j;
                        }
                        else if (n_tablero[i][j]=='c'){
                            j_pos[2][0] = i;
                            j_pos[2][1] = j;
                        }
                        else if (n_tablero[i][j]=='d'){
                            j_pos[3][0] = i;
                            j_pos[3][1] = j;
                        }
                    }
                }
                else{
                    if (j>*columnas-6){
                        n_tablero[i][j] = '/';
                    }
                    else{
                        n_tablero[i][j] = (*tablero)[i][j];
                        if (n_tablero[i][j]=='a'){
                            j_pos[0][0] = i;
                            j_pos[0][1] = j;
                        }
                        else if (n_tablero[i][j]=='b'){
                            j_pos[1][0] = i;
                            j_pos[1][1] = j;
                        }
                        else if (n_tablero[i][j]=='c'){
                            j_pos[2][0] = i;
                            j_pos[2][1] = j;
                        }
                        else if (n_tablero[i][j]=='d'){
                            j_pos[3][0] = i;
                            j_pos[3][1] = j;
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < f ; i++){
        free((*tablero)[i]);
    }
    free(*tablero);
    *tablero = n_tablero;
}

void rellenar_tablero(char **tablero,int *t1,int *t2, int *t3, int *t4, int *tps){
    srand(getpid());
    int x,y;
    x = rand()%5;
    y = rand()%5;
    while (tablero[x][y] != '0'){
        x = rand()%5;
        y = rand()%5;
    }
    int casilla = rand()%2;
    if (casilla == 0){
        casilla = rand()%4;
        while(!(*t1) || !(*t2) || !(*t3) || !(*t4)){           
            if (casilla == 0 && !(*t1)){
                tablero[x][y] = '1';
                *t1 = 1;
                return;
            }
            else if (casilla == 1 && !(*t2)){
                tablero[x][y] = '2';
                *t2 = 1;
                return;
            }
            else if (casilla == 2 && !(*t3)){
                tablero[x][y] = '3';
                *t3 = 1;
                return;
            }
            else if (casilla == 3 && !(*t4)){
                tablero[x][y] = '4';
                *t4 = 1;
                return;
            }
            casilla = rand()%4;
        }
    }
    else{
        casilla = rand()%4;
        if (casilla == 0){
            tablero[x][y] = 'S';
        }
        else if (casilla == 1){
            tablero[x][y] = 'R';
        }
        else if (casilla == 2){
            tablero[x][y] = 'C';
        }
        else{
            tablero[x][y] = 'T';
            *tps++;
        }
    }
}

void mostrar_tablero(char** tablero, int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (tablero[i][j] == 'a') {
                printf("J1 ");
            } else if (tablero[i][j] == 'b') {
                printf("J2 ");
            } else if (tablero[i][j] == 'c') {
                printf("J3 ");
            } else if (tablero[i][j] == 'd') {
                printf("J4 ");
            } else if (tablero[i][j] == '1' || tablero[i][j] == '2' || tablero[i][j] == '3' || tablero[i][j] == '4') {
                printf("T%c ", tablero[i][j]);
            } else if (tablero[i][j] == 'S') {
                printf("bt ");
            } else if (tablero[i][j] == 'R') {
                printf("bn ");
            } else if (tablero[i][j] == 'C') {
                printf("bc ");
            } else if (tablero[i][j] == 'T') {
                printf("tp ");
            }
            else if(tablero[i][j]=='/'){
                printf("/  ");
            } 
            else {
                printf("%c  ", tablero[i][j]);
            }
        }
        printf("\n");
    }
}

void buscar_tablero(char*** tablero, int* filas, int* columnas, int i, int j, char** n_tablero, int *t1, int* t2, int* t3, int* t4, int* tps, int j_pos[4][2]){
    srand(time(NULL));
    int d = rand()%8;
    char num[20];
    int vod[4][2];
    FILE *tab;
    char direccion;
    int verificar = 1;
    while (verificar){
        sprintf(num, "tablero%d.txt", d);
        tab = fopen(num, "r");
        crear_tablero(n_tablero, tab, vod);
        fclose(tab);
        if (i%5 == 0 && n_tablero[4][j%5]=='B'){
            n_tablero[4][j%5] = '0';
            direccion = 'u';
            i = i-i%5;
            j = j-j%5;
            if ( i-5 < 0){
                ampliar_tablero(tablero, filas, columnas, direccion, j_pos);
                ubicar_tablero(*tablero, n_tablero, *filas, *columnas, i, j);
                return;
            }
            rellenar_tablero(n_tablero, t1, t2, t3, t4, tps);
            ubicar_tablero(*tablero, n_tablero, *filas, *columnas, i-5,j );
            return;
        }
        else if (i%5 == 4 && n_tablero[0][j%5]=='B'){
            n_tablero[0][j%5] = '0';
            direccion = 'd';
            i = i-i%5;
            j = j-j%5;
            if (i+9 >= *filas){
                ampliar_tablero(tablero, filas, columnas, direccion, j_pos);
            }
            rellenar_tablero(n_tablero, t1, t2, t3, t4, tps);
            ubicar_tablero(*tablero, n_tablero, *filas, *columnas, i+5, j);
            return;
        }
        else if (j%5 == 0 && n_tablero[i%5][4]=='B'){
            n_tablero[i%5][4] = '0';
            direccion = 'l';
            i = i-i%5;
            j = j-j%5;
            if (j-5 < 0){
                ampliar_tablero(tablero, filas, columnas, direccion, j_pos);
                ubicar_tablero(*tablero, n_tablero, *filas, *columnas, i, j);
                return;
            }
            rellenar_tablero(n_tablero, t1, t2, t3, t4, tps);
            ubicar_tablero(*tablero, n_tablero, *filas, *columnas, i, j-5);
            return;
        }
        else if (j%5 == 4 && n_tablero[i%5][0]=='B'){
            n_tablero[i%5][0] = '0';
            direccion = 'r';
            i = i-i%5;
            j = j-j%5;
            if (j+9 >= *columnas){
                ampliar_tablero(tablero, filas, columnas, direccion, j_pos);
            }
            rellenar_tablero(n_tablero, t1, t2, t3, t4, tps);
            ubicar_tablero(*tablero, n_tablero, *filas, *columnas, i, j+5);
            return;
        }
        d = rand()%8;
    }
}

void asignar_carta(int cj[4]){
    srand(time(NULL));
    // asignar un número aleatorio del 0 al 3 a cada carta
    cj[0] = rand() % 4;
    do {
        cj[1] = rand() % 4;
    } while (cj[0] == cj[1]);
    do {
        cj[2] = rand() % 4;
    } while (cj[2] == cj[0] || cj[2] == cj[1]);
    do {
        cj[3] = rand() % 4;
    } while (cj[3] == cj[0] || cj[3] == cj[1] || cj[3] == cj[2]);
}

int teleport (char**tablero, int filas, int columnas, int jugador, int j_pos[4][2], int *tps, char c_act[4]){
    if (*tps == 0){
        return 0;
    }
    else{
        int x = j_pos[jugador][0];
        int y = j_pos[jugador][1];
        char aux;
        srand(time(NULL));
        int pos = rand()%4;
        if (pos == 0){
            // parte por la esquina superior izquierda
            for (int i = 0; i<= filas; i++){
                for(int j = 0; j <= columnas; j++){
                    if (i!=x && j != y && tablero[x][y]=='T'){
                        aux = tablero[x][y];
                        tablero[x][y] = tablero[i][j];
                        tablero[i][j] = c_act[jugador];
                        c_act[jugador] = aux;
                        j_pos[jugador][0] = i;
                        j_pos[jugador][1] = j;
                        return 1;
                    }
                }
            }
        }
        else if (pos == 1){
            //parte por la esquina superior derecha
            for(int i = 0; i<= filas; i++){
                for(int j = columnas-1; j >= 0; j--){
                    if (i!=x && j != y && tablero[x][y]=='T'){
                        aux = tablero[x][y];
                        tablero[x][y] = tablero[i][j];
                        tablero[i][j] = c_act[jugador];
                        c_act[jugador] = aux;
                        j_pos[jugador][0] = i;
                        j_pos[jugador][1] = j;
                        return 1;
                    }
                }
            }
        }
        else if (pos == 2){
            //parte por la esquina inferior izquierda
            for(int i = filas-1; i>= 0; i--){
                for(int j = 0; j <= columnas; j++){
                    if (i!=x && j != y && tablero[x][y]=='T'){
                        aux = tablero[x][y];
                        tablero[x][y] = tablero[i][j];
                        tablero[i][j] = c_act[jugador];
                        c_act[jugador] = aux;
                        j_pos[jugador][0] = i;
                        j_pos[jugador][1] = j;
                        return 1;
                    }
                }
            }
        }
        else{
            //parte por la esquina inferior derecha
            for(int i = filas-1; i>= 0; i--){
                for(int j = columnas-1; j >= 0; j--){
                    if (i!=x && j != y && tablero[x][y]=='T'){
                        aux = tablero[x][y];
                        tablero[x][y] = tablero[i][j];
                        tablero[i][j] = c_act[jugador];
                        c_act[jugador] = aux;
                        j_pos[jugador][0] = i;
                        j_pos[jugador][1] = j;
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

void mover_jugador(char** tablero, int filas, int columnas,int jugador ,char direccion, int casillas, char c_act[4], int j_pos[4][2], int *turnos, int*camara, int*tps){
    char aux;
    int i = j_pos[jugador][0];
    int j = j_pos[jugador][1];
    if (direccion == 'l'){
       for(int k = 1; k<= casillas; k++){
            if (j-1 < 0){
                printf("El Jugador %d no puede seguir avanzando, choco con algo...\n", jugador+1);
                return;
            }
            aux = tablero[i][j-1];
            if (aux == 'a' || aux == 'b' || aux == 'c' || aux == 'd' || aux == '/' || aux =='E' ){
                printf("El Jugador %d no puede seguir avanzando, choco con algo...\n", jugador+1);
                return;    
            }
            else if (aux == 'S' && *camara < 2){
                *turnos = *turnos+5;
                aux = '0';
                printf("El Jugador %d gano 5 turnos para todos!\n", jugador+1);
            }
            else if (aux == 'R'){
                *turnos = *turnos-5;
                aux = '0';
                printf("El Jugador %d perdio 5 turnos para todos :( \n", jugador+1);
            }
            else if (aux == 'C'){
                printf("El Jugador %d piso una camara secreta!\n", jugador+1);
                *camara++;
                printf("Cantidad de camaras activas: %d\n", *camara);
                if(*camara>=2){
                    printf("Los jugadores no pueden ganar mas turnos :(\n");
                }
                aux = 'A';
            }
            else if (aux == 'A'){
                printf("El Jugador %d cerro una camara abierta!\n", jugador+1);
                *camara--;
                printf("Cantidad de camaras activas: %d\n", *camara);
                aux = 'C';
            }
            else if (aux == 'T' && *tps >=2){
                teleport(tablero, filas, columnas, jugador, j_pos,tps, c_act);
                printf("El Jugador %d se teletransporto a un lugar aleatorio!\n", jugador+1);
                return;
            }
            tablero[i][j-1] = tablero[i][j];
            tablero[i][j] = c_act[jugador];
            c_act[jugador] = aux;
            j_pos[jugador][0] = i;
            j_pos[jugador][1] = j-1;
            i = j_pos[jugador][0];
            j = j_pos[jugador][1];
        }
    }
    else if(direccion=='r'){
        for (int k = 1; k<= casillas ; k++){
            if (j+1 >= columnas){
                printf("El Jugador %d no puede seguir avanzando, choco con algo...\n", jugador+1);
                return;
            }
            aux = tablero[i][j+1];
            if (aux == 'a' || aux == 'b' || aux == 'c' || aux == 'd' || aux == '/' || aux =='E' ){
                printf("El Jugador %d no puede seguir avanzando, choco con algo...\n", jugador+1);
                return;    
            }
            else if (aux == 'S'  && *camara < 2){
                *turnos = *turnos+5;
                printf("El Jugador %d gano 5 turnos para todos!\n", jugador+1);
                aux = '0';
            }
            else if (aux == 'R'){
                *turnos = *turnos-5;
                printf("El Jugador %d perdio 5 turnos para todos :( \n", jugador+1);
                aux = '0';
            }
            else if (aux == 'C'){
                printf("El Jugador %d piso una camara secreta!\n", jugador+1);
                *camara++;
                printf("Cantidad de camaras activas: %d\n", *camara);
                if(*camara>=2){
                    printf("Los jugadores no pueden ganar mas turnos :(\n");
                }
                aux = 'A';
            }
            else if (aux == 'A'){
                printf("El Jugador %d cerro una camara abierta!\n", jugador+1);
                *camara--;
                printf("Cantidad de camaras activas: %d\n", *camara);
                aux = 'C';
            }
            else if (aux == 'T' && *tps >=2){
                if (teleport(tablero, filas, columnas, jugador, j_pos,tps, c_act)){
                    printf("El Jugador %d se teletransporto a un lugar aleatorio!\n", jugador+1);
                    return;
                }
            }
            tablero[i][j+1] = tablero[i][j];
            tablero[i][j] = c_act[jugador];
            c_act[jugador] = aux;
            j_pos[jugador][0] = i;
            j_pos[jugador][1] = j+1;
            i = j_pos[jugador][0];
            j = j_pos[jugador][1];
        }
    }
    else if(direccion=='d'){
        for (int k = 1; k<= casillas; k++){
            if (i+1 >= filas){
                printf("El Jugador %d no puede seguir avanzando, choco con algo...\n", jugador+1);
                return;
            }
            aux = tablero[i+1][j];
            if (aux == 'a' || aux == 'b' || aux == 'c' || aux == 'd' || aux == '/' || aux =='E' ){
                printf("El Jugador %d no puede seguir avanzando, choco con algo...\n", jugador+1);
                return;    
            }
            else if (aux == 'S'  && *camara < 2){
                *turnos = *turnos+5;
                printf("El Jugador %d gano 5 turnos para todos!\n", jugador+1);
                aux = '0';
            }
            else if (aux == 'R'){
                *turnos = *turnos-5;
                printf("El Jugador %d perdio 5 turnos para todos :( \n", jugador+1);
                aux = '0';
            }
            else if (aux == 'C'){
                printf("El Jugador %d piso una camara secreta!\n", jugador+1);
                *camara++;
                printf("Cantidad de camaras activas: %d\n", *camara);
                if(*camara>=2){
                    printf("Los jugadores no pueden ganar mas turnos :(\n");
                }
                aux = 'A';
            }
            else if (aux == 'A'){
                printf("El Jugador %d cerro una camara abierta!\n", jugador+1);
                *camara--;
                printf("Cantidad de camaras activas: %d\n", *camara);
                aux = 'C';
            }
            else if (aux == 'T' && *tps >=2){
                if (teleport(tablero, filas, columnas, jugador, j_pos,tps, c_act)){
                    printf("El Jugador %d se teletransporto a un lugar aleatorio!\n", jugador+1);
                    return;
                }
            }
            tablero[i+1][j] = tablero[i][j];
            tablero[i][j] = c_act[jugador];
            c_act[jugador] = aux;
            j_pos[jugador][0] = i+1;
            j_pos[jugador][1] = j;
            i = j_pos[jugador][0];
            j = j_pos[jugador][1];
        }
    }
    else if(direccion=='u'){
        for (int k = 1; k<= casillas; k++){
            if (i-1 < 0){
                printf("El Jugador %d no puede seguir avanzando, choco con algo...\n", jugador+1);
                return;
            }
            aux = tablero[i-1][j];
            if (aux == 'a' || aux == 'b' || aux == 'c' || aux == 'd' || aux == '/' || aux =='E' ){
                printf("El Jugador %d no puede seguir avanzando, choco con algo...\n", jugador+1);
                return;    
            }
            else if (aux == 'S'  && *camara < 2){
                *turnos = *turnos+5;
                printf("El Jugador %d gano 5 turnos para todos!\n", jugador+1);
                aux = '0';
            }
            else if (aux == 'R'){
                *turnos = *turnos-5;
                printf("El Jugador %d perdio 5 turnos para todos :( \n", jugador+1);
                aux = '0';
            }
            else if (aux == 'C'){
                printf("El Jugador %d piso una camara secreta!\n", jugador+1);
                *camara++;
                printf("Cantidad de camaras activas: %d\n", *camara);
                if(*camara>=2){
                    printf("Los jugadores no pueden ganar mas turnos :(\n");
                }
                aux = 'A';
            }
            else if (aux == 'A'){
                printf("El Jugador %d cerro una camara abierta!\n", jugador+1);
                *camara--;
                printf("Cantidad de camaras activas: %d\n", *camara);
                aux = 'C';
            }
            else if (aux == 'T' && *tps >=2){
                if (teleport(tablero, filas, columnas, jugador, j_pos,tps, c_act)){
                    printf("El Jugador %d se teletransporto a un lugar aleatorio!\n", jugador+1);
                    return;
                }
            }
            tablero[i-1][j] = tablero[i][j];
            tablero[i][j] = c_act[jugador];
            c_act[jugador] = aux;
            j_pos[jugador][0] = i-1;
            j_pos[jugador][1] = j;
            i = j_pos[jugador][0];
            j = j_pos[jugador][1];
        }
    }
}

void buscar_tesoro(char** tablero, int filas, int columnas, int jugador, char c_act[4], int j_pos[4][2],int t[4]){
    char jug = '0'+jugador+1;
    int i = j_pos[jugador][0];
    int j = j_pos[jugador][1];
    if (tablero [i+1][j] == jug){
        t[jugador] = 1;
        tablero [i+1][j] = '0';
    }
    else if (tablero [i][j-1] == jug){
        t[jugador] = 1;
        tablero [i][j-1] = '0';
    } 
    else if (tablero [i-1][j] == jug){
        t[jugador] = 1;
        tablero [i-1][j] = '0';
    }
    else if (tablero [i][j+1] == jug){
        t[jugador] = 1;
        tablero [i][j+1] = '0';
    }
    else if (tablero [i][j] == jug){
        t[jugador] = 1;
        c_act[jugador] = '0';
    }
    printf("Jugador %d encontró el tesoro!\n", jugador+1);
}

void carta_accion(char*** tablero, int *filas, int *columnas, int jugador, int carta, char c_act[4], int j_pos[4][2], char** n_tablero, int *t1, int* t2, int* t3, int* t4, int* tps) {
    int i = j_pos[jugador][0];
    int j = j_pos[jugador][1];
    if ((*tablero)[i + 1][j] == carta) {
        (*tablero)[i + 1][j] = '0';
        if (carta == 'B') {
            buscar_tablero(tablero, filas, columnas, i + 1, j, n_tablero, t1, t2, t3, t4, tps, j_pos);
        }
    } else if ((*tablero)[i][j - 1] == carta) {
        (*tablero)[i][j - 1] = '0';
        if (carta == 'B') {
            buscar_tablero(tablero, filas, columnas, i, j - 1, n_tablero, t1, t2, t3, t4, tps, j_pos);
        }
    } else if ((*tablero)[i - 1][j] == carta) {
        (*tablero)[i - 1][j] = '0';
        if (carta == 'B') {
            buscar_tablero(tablero, filas, columnas, i - 1, j, n_tablero, t1, t2, t3, t4, tps, j_pos);
        }
    } else if ((*tablero)[i][j + 1] == carta) {
        (*tablero)[i][j + 1] = '0';
        if (carta == 'B') {
            buscar_tablero(tablero, filas, columnas, i, j + 1, n_tablero, t1, t2, t3, t4, tps, j_pos);
        }
    } else if (c_act[jugador] == carta) {
        c_act[jugador] = '0';
        if (carta == 'B') {
            buscar_tablero(tablero, filas, columnas, i, j, n_tablero, t1, t2, t3, t4, tps, j_pos);
        }
    }
    if (carta == 'B') {
        printf("El Jugador %d abrió un nuevo tablero!\n", jugador + 1);
        mostrar_tablero(*tablero, *filas, *columnas);
    } else {
        printf("El Jugador %d abrió una puerta!\n", jugador + 1);
    }
}

int revisarB(char** tablero, int filas, int columnas, int jugador, int j_pos[4][2], char c_act[4]){
    int i = j_pos[jugador][0], j = j_pos[jugador][1];
    return (tablero [i+1][j]=='B' || tablero [i][j-1]=='B' || tablero [i-1][j]=='B' || tablero [i][j+1]=='B' || c_act[jugador]=='B');
}

int revisarE(char** tablero, int filas, int columnas, int jugador, int j_pos[4][2], char c_act[4]){
    int i = j_pos[jugador][0], j = j_pos[jugador][1];
    return (tablero [i+1][j]=='E' || tablero [i][j-1]=='E' || tablero [i-1][j]=='E' || tablero [i][j+1]=='E' || c_act[jugador]=='E');
}

int revisarT(char** tablero, int filas, int columnas, int jugador, int j_pos[4][2], int t[4], char c_act[4]){
    int i = j_pos[jugador][0], j = j_pos[jugador][1];
    char jug = '0'+jugador+1;
    if (!t[jugador]){
        return (tablero[i+1][j]==jug || tablero [i][j-1]==jug || tablero [i-1][j]==jug || tablero [i][j+1]==jug || c_act[jugador]==jug);
    }
    return 0;
}

void mostrar2(char** tablero, int filas, int columnas, int jugador, int j_pos[4][2], char c_act[4]){
    for(int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            printf("%c ", tablero[i][j]);
        }
        printf("\n");
    }    
}