package doubleVectorElements;

public class MyThread implements Runnable {
    private int id;
    public MyThread(int id){
        this.id = id;
    }

    public void run() {
        int start = (int) (id * (double) Main.N / Main.P);
        int end = (int)Math.min((id + 1) * (double) Main.N / Main.P, Main.N);
        for (int i = start; i < end; i++) {
            Main.v[i] = Main.v[i] * 2;
        }
    }
}
