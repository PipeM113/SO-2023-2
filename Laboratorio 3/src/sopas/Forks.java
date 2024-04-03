package sopas;

import java.util.concurrent.RecursiveAction;

public class Forks extends RecursiveAction {
    public static volatile boolean found = false;
    private int N;
    private char[][] matrix;
    private int tam;
    private int x;
    private int y;
    private String palabra;

    // Datos para el fork
    public Forks(int N, char[][] matrix, int tam, int x, int y, String palabra) {
        this.N = N;
        this.matrix = matrix;
        this.tam = tam;
        this.x = x;
        this.y = y;
        this.palabra = palabra;
    }

    // Creación de los forks
    @Override
    protected void compute() {
        if (N != tam) {
            Forks f1 = new Forks(N / 2, matrix, tam, x, y, palabra);
            Forks f2 = new Forks(N / 2, matrix, tam, x + N / 2, y, palabra);
            Forks f3 = new Forks(N / 2, matrix, tam, x, y + N / 2, palabra);
            Forks f4 = new Forks(N / 2, matrix, tam, x + N / 2, y + N / 2, palabra);
            invokeAll(f1, f2, f3, f4);
        } else {
            encontrarSolucion();
            return;
        }
    }

    // Función que encuentra la posición en la que parte la palabra
    private void encontrarSolucion() {
        int index = 0;
        for (int i = x; i < x + N; i++) {
            if (found) {
                return;
            }
            for (int j = y; j < y + N; j++) {
                if (matrix[i][j] == palabra.charAt(index)) {
                    index++;
                } else {
                    index = 0;
                }
            }
            if (index == tam) {
                System.out.println("Encontrada en fila " + i + " y columna " + y);
                found = true;
                return;
            } else {
                index = 0;
            }
        }
        index = 0;
        for (int i = y; i < y + N; i++) {
            if (found) {
                return;
            }
            for (int j = x; j < x + N; j++) {
                if (matrix[j][i] == palabra.charAt(index)) {
                    index++;
                } else {
                    index = 0;
                }
            }
            if (index == tam) {
                System.out.println("Encontrada en fila " + x + " y columna " + i);
                found = true;
                return;
            } else {
                index = 0;
            }
        }
    }
}
