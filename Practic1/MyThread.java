import java.util.concurrent.BrokenBarrierException;

public class MyThread implements Runnable {
    private int id;
    public MyThread(int id){
        this.id = id;
    }

    public void run() {
        int start = (int) (id * (double) Main.N / Main.P);
        int end = (int)Math.min((id + 1) * (double) Main.N / Main.P, Main.N);
        for (int i = start; i < end; i++) {
            Main.value.getAndAdd(Main.v[i]);
        }

        try {
            Main.barrier.await();
        } catch (InterruptedException | BrokenBarrierException e) {
            e.printStackTrace();
        }

        if(id == 0){
            System.out.println(Main.value.get());
        }
    }
}