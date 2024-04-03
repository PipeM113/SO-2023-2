==================================================================================================
PARALELO: 201
==================================================================================================
NOMBRES
==================================================================================================
Felipe Mellado
ROL      : 201973525-K

Cristopher Fuentes Llanten
ROL      : 201973598-5
==================================================================================================
README
==================================================================================================

Laboratorio 2 SO:

-Se han entregado cuatro archivos: "makefile", "lab2.c", "funcs.c" y "funcs.h".

	-Modo de uso: Descargar los 4 archivos y dejarlos juntos en una misma carpeta,
	luego ejecutar el comando "make run" o "make" para que se compile y ejecute el programa.
	(Es necesario tener los archivos ".txt" correspondientes al laberinto para poder hacer uso
	de este comando)
	También es posible eliminar los programas con el comando "make clean"

	-Explicación: El programa lee múltiples archivos '.txt' los cuales deben tener el formato
	especificado en el laboratorio, luego busca el nombre del archivo "inicio.txt" EN la carpeta,
	el cual será el tablero inicial para poder continuar con el laberinto, luego iran por turnos 
	moviendose por las casillas que el jugador diga tratando de encontrar el tesoro correspondiente
	a cada uno. El juego termina cuando cada jugador encuentra SU tesoro o cuando se acaben los turnos.


  -Notas y Supuestos: 
	  -Los warnings que corresponden a los tp, son para ver cuantas fichas de tp existen. 
	   Lo mismo para el de cámaras.
      -Los comentarios de que hace cada función se encuentran en el header funcs.h
      -Se deja como supuesto que los archivos SIEMPRE tienen un formato correcto.
	  -El tp de los jugadores se activa al estar encima de este, y es hacia una casilla random.
      -Se que el jugador solo hará movimientos válidos.
	  -Los jugadores que tengan disponible buscar un tesoro u ocupar la carta acción lo harán
	   y no se moverán en su turno.

