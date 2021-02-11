#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

int P;
int width_Julia, height_Julia, width_Mandelbrot, height_Mandelbrot;
int **result_Julia, **result_Mandelbrot;
pthread_barrier_t barrier;

char *in_filename_julia;
char *in_filename_mandelbrot;
char *out_filename_julia;
char *out_filename_mandelbrot;

// structura pentru un numar complex
typedef struct _complex {
	double a;
	double b;
} complex;

// structura pentru parametrii unei rulari
typedef struct _params {
	int is_julia, iterations;
	double x_min, x_max, y_min, y_max, resolution;
	complex c_julia;
} params;

params par_Julia;
params par_Mandelbrot;

// Calculeaza minimul
int minim(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

// citeste argumentele programului
void get_args(int argc, char **argv)
{
	if (argc < 6) {
		printf("Numar insuficient de parametri:\n\t"
				"./tema1 fisier_intrare_julia fisier_iesire_julia "
				"fisier_intrare_mandelbrot fisier_iesire_mandelbrot\n"
				"P\n");
		exit(1);
	}

	in_filename_julia = argv[1];
	out_filename_julia = argv[2];
	in_filename_mandelbrot = argv[3];
	out_filename_mandelbrot = argv[4];
	P = atoi(argv[5]);
}

// citeste fisierul de intrare
void read_input_file(char *in_filename, params* par)
{
	FILE *file = fopen(in_filename, "r");
	if (file == NULL) {
		printf("Eroare la deschiderea fisierului de intrare!\n");
		exit(1);
	}

	fscanf(file, "%d", &par->is_julia);
	fscanf(file, "%lf %lf %lf %lf",
			&par->x_min, &par->x_max, &par->y_min, &par->y_max);
	fscanf(file, "%lf", &par->resolution);
	fscanf(file, "%d", &par->iterations);

	if (par->is_julia) {
		fscanf(file, "%lf %lf", &par->c_julia.a, &par->c_julia.b);
	}

	fclose(file);
}

// scrie rezultatul in fisierul de iesire
void write_output_file(char *out_filename, int **result, int width, int height)
{
	int i, j;

	FILE *file = fopen(out_filename, "w");
	if (file == NULL) {
		printf("Eroare la deschiderea fisierului de iesire!\n");
		return;
	}

	fprintf(file, "P2\n%d %d\n255\n", width, height);
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			fprintf(file, "%d ", result[i][j]);
		}
		fprintf(file, "\n");
	}

	fclose(file);
}

// aloca memorie pentru rezultat
int **allocate_memory(int width, int height)
{
	int **result;
	int i;

	result = malloc(height * sizeof(int*));
	if (result == NULL) {
		printf("Eroare la malloc!\n");
		exit(1);
	}

	for (i = 0; i < height; i++) {
		result[i] = malloc(width * sizeof(int));
		if (result[i] == NULL) {
			printf("Eroare la malloc!\n");
			exit(1);
		}
	}

	return result;
}

// elibereaza memoria alocata
void free_memory(int **result, int height)
{
	int i;

	for (i = 0; i < height; i++) {
		free(result[i]);
	}
	free(result);
}

// ruleaza algoritmul Julia
void run_julia(params *par, int **result, int width, int height, int start, int end)
{
	int w, h;

	for (w = 0; w < width; w++) {
		for (h = start; h < end; h++) {
			int step = 0;
			complex z = { .a = w * par->resolution + par->x_min,
							.b = h * par->resolution + par->y_min };

			while (sqrt(z.a * z.a + z.b * z.b) < 2.0 && step < par->iterations) {
				complex z_aux = { .a = z.a, .b = z.b };

				z.a = pow(z_aux.a, 2.0) - pow(z_aux.b, 2.0) + par->c_julia.a;
				z.b = 2 * z_aux.a * z_aux.b + par->c_julia.b;

				step++;
			}

			result[h][w] = step % 256;
		}
	}
}

// ruleaza algoritmul Mandelbrot
void run_mandelbrot(params *par, int **result, int width, int height, int start, int end)
{
	int w, h;

	for (w = 0; w < width; w++) {
		for (h = start; h < end; h++) {
			complex c = { .a = w * par->resolution + par->x_min,
							.b = h * par->resolution + par->y_min };
			complex z = { .a = 0, .b = 0 };
			int step = 0;

			while (sqrt(z.a * z.a + z.b * z.b) < 2.0 && step < par->iterations) {
				complex z_aux = { .a = z.a, .b = z.b };

				z.a = pow(z_aux.a, 2.0) - pow(z_aux.b, 2.0) + c.a;
				z.b = 2.0 * z_aux.a * z_aux.b + c.b;

				step++;
			}

			result[h][w] = step % 256;
		}
	}
}

void *thread_function(void *arg) {
	int thread_id = *(int *)arg;

	int start = thread_id * (double)height_Julia / P;
    int end = minim((thread_id + 1) * (double)height_Julia / P, height_Julia);
	run_julia(&par_Julia, result_Julia, width_Julia, height_Julia, start, end);
	pthread_barrier_wait(&barrier);
	
	start = thread_id * (double)height_Mandelbrot / P;
    end = minim((thread_id + 1) * (double)height_Mandelbrot / P, height_Mandelbrot);
	run_mandelbrot(&par_Mandelbrot, result_Mandelbrot, width_Mandelbrot, height_Mandelbrot, start, end);
	pthread_barrier_wait(&barrier);

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	// se citesc argumentele programului
	get_args(argc, argv);

	int i;
	pthread_t threads[P];
	int thread_id[P];
	pthread_barrier_init(&barrier, NULL, P);
	
	// Julia:
	read_input_file(in_filename_julia, &par_Julia);
	width_Julia = (par_Julia.x_max - par_Julia.x_min) / par_Julia.resolution;
	height_Julia = (par_Julia.y_max - par_Julia.y_min) / par_Julia.resolution;
	result_Julia = allocate_memory(width_Julia, height_Julia);

	// Mandelbrot:
	read_input_file(in_filename_mandelbrot, &par_Mandelbrot);
	width_Mandelbrot = (par_Mandelbrot.x_max - par_Mandelbrot.x_min) / par_Mandelbrot.resolution;
	height_Mandelbrot = (par_Mandelbrot.y_max - par_Mandelbrot.y_min) / par_Mandelbrot.resolution;
	result_Mandelbrot = allocate_memory(width_Mandelbrot, height_Mandelbrot);

	// se creeaza thread-urile
	for (i = 0; i < P; i++) {
		thread_id[i] = i;
		pthread_create(&threads[i], NULL, thread_function, &thread_id[i]);
	}

	// se asteapta thread-urile
	for (i = 0; i < P; i++) {
		pthread_join(threads[i], NULL);
	}

	// transforma rezultatul din coordonate matematice in coordonate ecran
	for (i = 0; i < height_Julia / 2; i++) {
		int *aux = result_Julia[i];
		result_Julia[i] = result_Julia[height_Julia - i - 1];
		result_Julia[height_Julia - i - 1] = aux;
	}

	for (i = 0; i < height_Mandelbrot / 2; i++) {
		int *aux = result_Mandelbrot[i];
		result_Mandelbrot[i] = result_Mandelbrot[height_Mandelbrot - i - 1];
		result_Mandelbrot[height_Mandelbrot - i - 1] = aux;
	}

	write_output_file(out_filename_julia, result_Julia, width_Julia, height_Julia);
	write_output_file(out_filename_mandelbrot, result_Mandelbrot, width_Mandelbrot, height_Mandelbrot);
	free_memory(result_Julia, height_Julia);
	free_memory(result_Mandelbrot, height_Mandelbrot);

	pthread_barrier_destroy(&barrier);
	return 0;
}
