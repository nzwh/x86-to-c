#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>

const int n20 = 1048576;    // 2^20
const int n24 = 16777216;   // 2^24
const int n27 = 134217728;  // 2^27

double dp_formula(int size, double* vector_a, double* vector_b) {
    double dot_product = 0.0;

    for (int i = 0; i < size; i++)
        dot_product += vector_a[i] * vector_b[i];

    return dot_product;
}

int main() {
    srand((unsigned int)time(NULL));

    int size;
    printf("Input a vector size: ");
    scanf_s("%d", &size);
    size = (int)pow(2, size);

    double* vector_a = (double*)malloc(size * sizeof(double));
    double* vector_b = (double*)malloc(size * sizeof(double));

    int runs = 30;
    double time_c = 0.0;
    double dot_product = 0;

    for (int i = 0; i < runs; i++) {
        for (int j = 0; j < size; j++) {
            vector_a[j] = (double)rand() / RAND_MAX;
            vector_b[j] = (double)rand() / RAND_MAX;
        }

        // Timing starts
        clock_t start = clock();

        dot_product = dp_formula(size, vector_a, vector_b);

        // Timing ends
        clock_t end = clock();

        // Calculate runtime
        double time_result_c = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("Dot product in C: %.2f\n", dot_product);
        printf("Runtime %d: %.6f seconds\n", i + 1, time_result_c);

        // Accumulate time
        time_c += time_result_c;
    }

    // Calculate average runtime
    double average_time_c = time_c / runs;
    printf("Average execution time in C: %.6f seconds\n", average_time_c);

    free(vector_a);
    free(vector_b);

    return 0;
}
