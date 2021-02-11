package multipleProducersMultipleConsumersNBuffer;

import java.util.Queue;
import java.util.concurrent.Semaphore;

/**
 * @author Gabriel Gutu <gabriel.gutu at upb.ro>
 *
 */
public class Buffer {

    Queue queue;

    int a;
    Semaphore empty = new Semaphore(1);
    Semaphore full = new Semaphore(0);

    public Buffer(int size) {
        queue = new LimitedQueue(size);
    }

    void put(int value) {
        try {
            empty.acquire();
            a = value;
            full.release();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    int get() {
        int aux = 0;
        try {
            full.acquire();
            aux = this.a;
            empty.release();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        return aux;
    }
}
