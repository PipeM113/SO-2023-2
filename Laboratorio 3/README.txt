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

Laboratorio 3 SO:

-Se han entregado cuatro archivos: "makefile", "manifest.mf", "main.jar" y "Analisis.xlsx" y
2 carpetas: "build" y "src", las cuales son fundamentales para el funcionamiento del programa main. 

	-Modo de uso: Descargar los 4 archivos y las 2 carpetas mencionadas, dejarlas juntas en una misma carpeta,
	luego ejecutar el comando "make run" o "make" para que se compile y ejecute el programa.
	(Es necesario tener el archivo ".txt" correspondiente a la sopa de letras para poder hacer uso
	de este comando)
	También es posible eliminar los programas con el comando "make clean"

	-Explicación: El programa lee un archivo llamado 'sopa_de_letras.txt' el cual debe tener el formato
    especificado en el laboratorio, luego busca la palabra que está en la segunda linea del archivo '.txt'
    dentro de la matriz de sopa de letras utilizando un método lineal, un método con fork y un método con
    threads, informando para cada una la ubicación de la palabra dentro de la sopa de letras y el tiempo
    que demora el método correspondiente.



