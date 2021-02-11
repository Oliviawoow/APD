package ex1;

public class MyThread extends Thread {
    private int id;
    private int result;

    public MyThread(int id) {
        this.id = id;
    }

    public void run() {
        System.out.println("Hello from thread #" + id);
    }

    public int getResult() {
        return result;
    }
}
