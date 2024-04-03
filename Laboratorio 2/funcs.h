#ifndef funcs_h
#define funcs_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

void iniciar_tablero(char**tablero, int filas, int columnas, char** n_tablero, int j_pos[4][2]); //inicia el tablero

void crear_tablero(char **tablero, FILE *inicio, int j_pos[4][2]); //crea el tablero

void ubicar_tablero(char** tablero, char** n_tablero, int filas, int columnas, int i, int j); //ubica el tablero

void ampliar_tablero(char*** tablero, int *filas, int *columnas, char direccion, int j_pos[4][2]); //amplia el tablero

void rellenar_tablero(char **tablero,int *t1,int *t2, int *t3, int *t4, int *tps); //rellena el tablero con las casillas especiales

void mostrar_tablero(char** tablero, int filas, int columnas); //muestra el tablero

void buscar_tablero(char*** tablero, int* filas, int* columnas, int i, int j, char** n_tablero, int *t1, int* t2, int* t3, int* t4, int* tps, int j_pos[4][2]); //busca el tablero para ampliarlo

void asignar_carta(int cj[4]);//asigna las cartas a los jugadores

int teleport (char**tablero, int filas, int columnas, int jugador, int j_pos[4][2], int *tps, char c_act[4]); //teletransporta al jugador a una casilla B_tpN

void mover_jugador(char** tablero, int filas, int columnas,int jugador ,char direccion, int casillas, char c_act[4], int j_pos[4][2], int *turnos, int*camara, int*tps); //mueve al jugador

void buscar_tesoro(char** tablero, int filas, int columnas, int jugador, char c_act[4], int j_pos[4][2],int t[4]); //busca el tesoro

void carta_accion(char*** tablero, int *filas, int *columnas, int jugador, int carta, char c_act[4], int j_pos[4][2], char** n_tablero, int *t1, int* t2, int* t3, int* t4, int* tps) ; //ejecuta la carta de accion

int revisarB(char** tablero, int filas, int columnas, int jugador, int j_pos[4][2], char c_act[4]); //revisa si el jugador esta en una casilla B

int revisarE(char** tablero, int filas, int columnas, int jugador, int j_pos[4][2], char c_act[4]); //revisa si el jugador esta en una casilla E

int revisarT(char** tablero, int filas, int columnas, int jugador, int j_pos[4][2], int t[4], char c_act[4]); //revisa si el jugador esta en una casilla T

void mostrar2(char** tablero, int filas, int columnas, int jugador, int j_pos[4][2], char c_act[4]); //muestra el tablero con los jugadores

#endif