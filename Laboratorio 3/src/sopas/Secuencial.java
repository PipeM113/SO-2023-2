package sopas;

public class Secuencial {
    private int N;
    private char[][] matrix;
    private int tam;
    private String palabra;

    public Secuencial(int N, char[][] matrix, int tam, int x, int y, String palabra) {
        this.N = N;
        this.matrix = matrix;
        this.tam = tam;
        this.palabra = palabra;
    }

    public void encontrarSolucion() {
        int index = 0;
        int col = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (matrix[i][j] == palabra.charAt(index)) {
                    if (index == 0) {
                        col = j;
                    }
                    index++;
                    if (index == tam) {
                        System.out.println("Encontrada en fila " + i + " y columna " + col);
                        return;
                    }
                } else {
                    index = 0;
                }
            }

            index = 0;

        }

        index = 0;
        col = 0;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (matrix[j][i] == palabra.charAt(index)) {
                    if (index == 0) {
                        col = j;
                    }
                    index++;
                    if (index == tam) {
                        System.out.println("Encontrada en fila " + col + " y columna " + i);
                        return;
                    }
                } else {
                    index = 0;
                }
            }
            index = 0;
        }

    }
}
