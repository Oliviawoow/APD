package multipleProducersMultipleConsumers;

import java.util.concurrent.ArrayBlockingQueue;
class Buffer {
	private final ArrayBlockingQueue<Integer> array = new ArrayBlockingQueue<Integer>(5,true);

	void put(int value) {
		try {
			array.put(value);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	int get() {
		int result = -1;
		try {
			result = array.take();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		return result;
	}
}
