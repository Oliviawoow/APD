package bug2;
/**
 * @author cristian.chilipirea
 * 
 *         Why does this code not block? We took the same lock twice!
 *
 *         este inutil sa sincronizezi de 2 ori o data ce deja detii acel obiect
 */
public class MyThread implements Runnable {
	static int i;

	@Override
	public void run() {
		synchronized (this) {
			//synchronized (this) {
				i++;
			//}
		}
	}
}
