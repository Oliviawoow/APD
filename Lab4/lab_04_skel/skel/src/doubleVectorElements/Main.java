package doubleVectorElements;
/**
 * @author cristian.chilipirea
 *
 */
public class Main {
	public static final int N = 100000013;
	public static int[] v;
	static int P = Runtime.getRuntime().availableProcessors();

	public static void main(String[] args) {
		v = new int[N];
		for (int i = 0; i < N; i++) {
			v[i] = i;
		}

		Thread[] t = new Thread[P];
		for(int i = 0; i < N; i++) {
			v[i] = i;
		}

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

		for (int i = 0; i < N; i++) {
			if(v[i] != i * 2) {
				System.out.println("Wrong answer");
				System.exit(1);
			}
		}
		System.out.println("Correct");
	}
}
