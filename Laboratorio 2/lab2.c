#include "funcs.h"

int main(){
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//Tablero
///////////////////////////////////////////////////////////////////////////////////////////////////////////
    FILE *inicio = fopen("inicio.txt", "r");
    char **tablero;
    tablero = (char **)malloc(sizeof(char*)*15);
    if (tablero == NULL){
        printf("Error al asignar memoria\n");
        exit(1);
    }
    for (int i = 0; i < 15; i++){
        tablero[i] = (char *)malloc(sizeof(char)*15);
        if (tablero[i] == NULL){
            printf("Error al asignar memoria\n");
            exit(1);
        }
    }
    char **n_tablero;
    n_tablero = (char **)malloc(sizeof(char*)*5);
    for (int i = 0; i < 5; i++){
        n_tablero[i] = (char *)malloc(sizeof(char)*5);
    }
    int filas = 15, columnas = 15;
    char cartas[4] = {'B','E','B','E'};
    int cj[4],j_pos[4][2];
    asignar_carta(cj);
    int t1 = 0, t2 = 0, t3 = 0, t4 = 0, tps = 0; 
    crear_tablero(n_tablero, inicio, j_pos);
    iniciar_tablero(tablero, filas, columnas, n_tablero, j_pos);
    fclose(inicio);

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Subprocesos
///////////////////////////////////////////////////////////////////////////////////////////////////////////
    int pipes[8][2];
    pid_t pid;
    int turnos = 15, hijo, turno, casillas, jugada, camara = 0, B = 0, T = 0, E = 0;
    char direccion, c_act[4];
    int t[4];

    // todos parten en '0'
    for (int i = 0; i < 4; i++){
        c_act[i] = '0';
        t[i] = 0;
    }

    //crear pipes
    for (int i = 0; i < 8; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }
    int cont = 1;
    //crear 4 procesos con fork y asignarle el hijo a cada sub proceso y que cada hijo sepa cual hijo es
    for (int i = 0; i < 4 && cont; i++){
        pid = fork();
        if (pid == -1){
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0){
            hijo = i;
            cont = 0;
        }
    }

    // Código de los procesos
    if (pid!=0){
        //cerrar pipes sin uso
        for (int i = 0; i < 8; i++){
            if (i<4){
                close(pipes[i][1]); // cerrar escritura de los pipes de los hijos
            }
            else{
                close(pipes[i][0]); // cerrar lectura de los pipes de los hijos
            }
        }
        turno = 1;
        // administración nodo padre
        while (turnos > 0 && (!(t[0]) || !(t[1]) || !(t[2]) || !(t[3]))){
            //para cada hijo pide la acción a realizar
            printf("Turnos restantes: %d\n", turnos);
            printf("Tesoros encontrados: 1: %d, 2: %d, 3: %d, 4: %d\n", t[0], t[1], t[2], t[3]);
            printf("\n");
            for(int i = 0; i < 4; i++){
                write(pipes[i+4][1], &turno, sizeof(turno));
                B = revisarB(tablero, filas, columnas, i, j_pos, c_act);
                T = revisarT(tablero, filas, columnas, i, j_pos, t, c_act);
                E = revisarE(tablero, filas, columnas, i, j_pos, c_act);
                printf("TABLERO:\n");
                mostrar_tablero(tablero, filas, columnas);
                //mostrar2(tablero, filas, columnas, i, j_pos, c_act);
                printf("Jugador %d, carta: %c\n", i+1, cartas[cj[i]]);
                if(T||(E&& cartas[cj[i]] == 'E')||(B && cartas[cj[i]] == 'B')){
                    jugada = 0;
                    write(pipes[i+4][1], &jugada, sizeof(jugada));
                    printf("El jugador %d debe realizar una acción\n", i+1);
                    if (cartas[cj[i]] == 'B' && B && T){
                        jugada = 0;
                        write(pipes[i+4][1], &jugada, sizeof(jugada));
                        read(pipes[i][0], &jugada, sizeof(jugada));
                        if (jugada == 0){
                            printf("Jugador %d busco tesoro\n", i+1);
                            buscar_tesoro(tablero, filas, columnas, i, c_act, j_pos, t);
                        }
                        else{
                            printf("Jugador %d uso carta de accion\n", i+1);
                            carta_accion(&tablero, &filas, &columnas, i, cartas[cj[i]], c_act, j_pos, n_tablero, &t1, &t2, &t3, &t4, &tps);
                        }
                        }
                    else if (cartas[cj[i]] == 'E' && E && T){
                        jugada = 0;
                        write(pipes[i+4][1], &jugada, sizeof(jugada));
                        read(pipes[i][0], &jugada, sizeof(jugada));
                        if (jugada == 0){
                            printf("Jugador %d busco tesoro\n", i+1);
                            buscar_tesoro(tablero, filas, columnas, i, c_act, j_pos, t);
                        }
                        else{
                            printf("Jugador %d uso carta de accion\n", i+1);
                            carta_accion(&tablero, &filas, &columnas, i, cartas[cj[i]], c_act, j_pos, n_tablero, &t1, &t2, &t3, &t4, &tps);
                        }
                    }
                    else if (T){
                        jugada = 1;
                        write(pipes[i+4][1], &jugada, sizeof(jugada));
                        printf("El Jugador %d, sólo puede buscar tesoro.\n", i+1);
                        printf("Jugador %d busco un tesoro\n", i+1);
                        buscar_tesoro(tablero, filas, columnas, i, c_act, j_pos, t);

                    }
                    else if (B && cartas[cj[i]] == 'B'){
                        jugada = 1;
                        write(pipes[i+4][1], &jugada, sizeof(jugada));
                        printf("El Jugador %d, sólo puede realizar carta de acción.\n", i+1);
                        printf("Jugador %d uso carta de accion\n", i+1);
                        carta_accion(&tablero, &filas, &columnas, i, cartas[cj[i]], c_act, j_pos, n_tablero, &t1, &t2, &t3, &t4, &tps);
                    }
                    else if (E && cartas[cj[i]] == 'E'){
                        jugada = 1;
                        write(pipes[i+4][1], &jugada, sizeof(jugada));
                        printf("El Jugador %d, sólo puede realizar carta de acción.\n", i+1);
                        printf("Jugador %d uso carta de accion\n", i+1);
                        carta_accion(&tablero, &filas, &columnas, i, cartas[cj[i]], c_act, j_pos, n_tablero, &t1, &t2, &t3, &t4, &tps);
                    } 
                }
                else{ 
                    jugada = 1;
                    write(pipes[i+4][1], &jugada, sizeof(jugada));
                    read(pipes[i][0], &direccion, sizeof(direccion));
                    read(pipes[i][0], &casillas, sizeof(casillas));
                    mover_jugador(tablero, filas, columnas, i, direccion, casillas, c_act, j_pos, &turnos, &camara, &tps);
                }
            }
            turnos--;
        }
        if (turnos > 0){
            printf("Todos los jugadores hayaron los tesoros, han ganado!!!!\n");
        }
        else{
            printf("Se acabaron los turnos, han perdido X.X \n");
        }
        turno = 0;
        //le dice que ya no se seguirán ejecutando
        for (int i = 0; i < 4; i++){
            write(pipes[i+4][1], &turno, sizeof(turno));
        }
    }
    else{
        char buffer[10];
        //cierra las pipes sin usar
        for (int i = 0; i < 8; i++){
            if (i<4){
                close(pipes[i][0]); // cerrar lectura de los pipes de los hijos
            }
            else{
                close(pipes[i][1]); // cerrar escritura de los pipes de los hijos
            }
        }
        turno = 1;
        while(turno){
            read(pipes[hijo+4][0], &turno, sizeof(turno));
            if (turno){
                read(pipes[hijo+4][0], &jugada, sizeof(jugada));
                if(jugada == 0){ 
                    read(pipes[hijo+4][0], &jugada, sizeof(jugada));
                    if (jugada == 0) {
                        printf("Jugador %d elija una acción:\n", hijo + 1);
                        printf("0: Buscar tesoro, 1: Usar carta de acción\n");
                        fgets(buffer, sizeof(buffer), stdin); // Leer una línea completa
                        sscanf(buffer, "%d", &jugada);
                        write(pipes[hijo][1], &jugada, sizeof(jugada));
                    }
                }
                else{
                    printf("El Jugador %d sólo puede moverse.\n", hijo+1);
                    printf("Ingrese la dirección a moverse:\n");
                    printf("u: arriba, d: abajo, l: izquierda, r: derecha\n");
                    fgets(buffer, sizeof(buffer), stdin); // Leer una línea completa
                    sscanf(buffer, "%c", &direccion);
                    write(pipes[hijo][1], &direccion, sizeof(direccion));
                    printf("Ingrese la cantidad de casillas a moverse:\n");
                    fgets(buffer, sizeof(buffer), stdin); // Leer una línea completa
                    sscanf(buffer, "%d", &casillas);
                    write(pipes[hijo][1], &casillas, sizeof(casillas));
                }
            }
        }
    }
    // Esperar a que todos los procesos hijos terminen
    if (pid != 0) {
        for (int i = 0; i < 4; i++) {
            wait(NULL);
        }
    }

    for (int i = 0; i < filas; i++){
        free(tablero[i]);
    }
    free(tablero);
    for (int i = 0; i < 5; i++){
        free(n_tablero[i]);
    }
    free(n_tablero);    
    return 0;
}