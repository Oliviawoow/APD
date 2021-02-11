import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.atomic.AtomicInteger;

public class Main {
    public static final int N = 100;
    public static final int P = Runtime.getRuntime().availableProcessors();
    public static int[] v;

    static AtomicInteger value = new AtomicInteger(0);
    public static CyclicBarrier barrier = new CyclicBarrier(P);

    public static void main(String[] args) {
        v = new int[N];
        for (int i = 0; i < N; i++) {
            v[i] = i + 5;
        }

        Thread[] t = new Thread[P];
        for (int i = 0; i < P; ++i) {
            t[i] = new Thread(new MyThread(i));
            t[i].start();
        }

        for (int i = 0; i < P; ++i) {
            try {
                t[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}