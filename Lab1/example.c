#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 5

void *f(void *arg) {
  	long id = (long)arg;
  	// EX 3:
  	// for (int i = 0; i < 100; ++i)
  	// 	printf("Hello World din thread-ul %ld!\n", id);
  	printf("Hello World din thread-ul %ld!\n", id);
  	pthread_exit(NULL);
}

void *f2(void *arg) {
  	long id = (long)arg;
  	printf("Buna din thread-ul %ld!\n", id);
  	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	// EX 2:
	long cores = sysconf(_SC_NPROCESSORS_CONF);
	pthread_t threads[NUM_THREADS];
  	int r;
  	long id;
  	void *status;

  // 	for (id = 0; id < NUM_THREADS; id++) {
		// r = pthread_create(&threads[id], NULL, f3, (void *)id);

		// if (r) {
	 //  		printf("Eroare la crearea thread-ului %ld\n", id);
	 //  		exit(-1);
		// }
  // 	}

  // 	for (id = 0; id < NUM_THREADS; id++) {
		// r = pthread_join(threads[id], &status);

		// if (r) {
	 //  		printf("Eroare la asteptarea thread-ului %ld\n", id);
	 //  		exit(-1);
		// }
  // 	}

  	// EX 4:
  	r = pthread_create(&threads[0], NULL, f, NULL);
  	r = pthread_create(&threads[1], NULL, f2, NULL);

  	r = pthread_join(threads[0], NULL);
  	r = pthread_join(threads[1], NULL);

  	pthread_exit(NULL);
}
