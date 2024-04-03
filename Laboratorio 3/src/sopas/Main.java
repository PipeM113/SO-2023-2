package sopas;

import java.io.*;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.TimeUnit;

public class Main {
    // Imprime la matriz
    public static void PrintMatrix(char[][] matriz) {
        for (int i = 0; i < matriz.length; i++) {
            System.out.println();
            for (int j = 0; j < matriz.length; j++) {
                System.out.print(matriz[i][j] + " ");
            }
        }
        System.out.println();
    }

    // Función main
    public static void main(String[] args) {
        // Creación de la matriz /////////////////////////////////////////////////
        File file = new File("sopa_de_letras.txt");
        char[][] matriz = null;
        String palabra = "";
        int n = 0;
        try {
            BufferedReader br = new BufferedReader(new FileReader(file));
            String line;
            line = br.readLine();
            n = Integer.parseInt(line);
            palabra = br.readLine();
            char aux;
            matriz = new char[n][n];
            for (int i = 0; i < n; i++) {
                line = br.readLine();
                String[] characters = line.split(" ");
                for (int j = 0; j < n; j++) {
                    aux = characters[j].charAt(0);
                    matriz[i][j] = aux;
                }
            }
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        ////////////////////////////////////////////////////////////////////////////////

        long startTime, endTime;
        // Tiempo de ejecución secuencial
        // ///////////////////////////////////////////////
        startTime = System.currentTimeMillis();
        Secuencial buscarSopa = new Secuencial(n, matriz, palabra.length(), 0, 0, palabra);
        buscarSopa.encontrarSolucion();
        endTime = System.currentTimeMillis();
        System.out.println("Tiempo de ejecución secuencial: " + (endTime - startTime) + " milisegundos");
        ///////////////////////////////////////////////////////////////////////////////

        // Tiempo de ejecución hebras
        // ///////////////////////////////////////////////////
        startTime = System.currentTimeMillis();
        RecursiveThread thread = new RecursiveThread(n, matriz, 0, 0, palabra);
        thread.start();
        try {
            thread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        endTime = System.currentTimeMillis();
        System.out.println("Tiempo de ejecución hebras: " + (endTime - startTime) + " milisegundos");
        ///////////////////////////////////////////////////////////////////////////////

        // Tiempo ejecución fork
        // ////////////////////////////////////////////////////////
        startTime = System.currentTimeMillis();
        Forks forks = new Forks(n, matriz, palabra.length(), 0, 0, palabra);
        ForkJoinPool pool = new ForkJoinPool();
        pool.execute(forks);
        pool.shutdown();
        try {
            pool.awaitTermination(1, TimeUnit.HOURS);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        endTime = System.currentTimeMillis();
        System.out.println("Tiempo de ejecución fork: " + (endTime - startTime) + " milisegundos");
        ///////////////////////////////////////////////////////////////////////////////
    }
}