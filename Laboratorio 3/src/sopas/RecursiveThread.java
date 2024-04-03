package sopas;

public class RecursiveThread extends Thread {
    private static volatile boolean found = false;
    private int N;
    private static char[][] matrix;
    private static int tam;
    private int x;
    private int y;
    private static String palabra;

    // Datos para los Threads
    public RecursiveThread(int N, char[][] matrix, int x, int y, String palabra) {
        this.N = N;
        RecursiveThread.matrix = matrix;
        RecursiveThread.palabra = palabra;
        RecursiveThread.tam = palabra.length();
        this.x = x;
        this.y = y;
    }

    public RecursiveThread(int N, int x, int y) {
        this.N = N;
        this.x = x;
        this.y = y;
    }

    // Creación de los Threads
    @Override
    public void run() {
        if (N != tam) {
            int newN = N / 2;
            RecursiveThread thread1 = new RecursiveThread(newN, x, y);
            thread1.start();
            RecursiveThread thread2 = new RecursiveThread(newN, x + newN, y);
            thread2.start();
            RecursiveThread thread3 = new RecursiveThread(newN, x, y + newN);
            thread3.start();
            RecursiveThread thread4 = new RecursiveThread(newN, x + newN, y + newN);
            thread4.start();
            try {
                thread1.join();
                if (found) {
                    return;
                }
                thread2.join();
                if (found) {
                    return;
                }
                thread3.join();
                if (found) {
                    return;
                }
                thread4.join();
                return;
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            return;
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
                    if (index == tam) {
                        System.out.println("Encontrada en fila " + i + " y columna " + y);
                        found = true;
                        return;
                    }
                } else {
                    index = 0;
                }
            }
            index = 0;
        }
        index = 0;
        for (int i = y; i < y + N; i++) {
            if (found) {
                return;
            }
            for (int j = x; j < x + N; j++) {
                if (matrix[j][i] == palabra.charAt(index)) {
                    index++;
                    if (index == tam) {
                        System.out.println("Encontrada en fila " + i + " y columna " + y);
                        found = true;
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