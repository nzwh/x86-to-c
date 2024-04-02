#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>

const int n20 = 1048576;    // 2^20
const int n24 = 16777216;   // 2^24
const int n27 = 134217728;  // 2^27

extern float dp_imp_asm(float vector_a, float vector_b);

void fill_values(int max_rand, int size, float* vector_a, float* vector_b) {
    for (int j = 0; j < size; j++) {
        vector_a[j] = (float)(rand() % (max_rand - 1)) + 1;
        vector_b[j] = (float)(rand() % (max_rand - 1)) + 1;
    }
}

float dp_formula_c(int size, float* vector_a, float* vector_b) {
    float dot_product = 0.0;
    for (int i = 0; i < size; i++)
        dot_product += vector_a[i] * vector_b[i];
    return dot_product;
}

float dp_formula_asm(int size, float* vector_a, float* vector_b) {
    float dot_product = 0.0;
    for (int k = 0; k < size; k++)
        dot_product += dp_imp_asm(vector_a[k], vector_b[k]);
    return dot_product;
}

int main() {
    srand((unsigned int)time(NULL));

    int size;
    int runs = 30;
    int max_rand = 100000;

    printf("Input a vector size n (2^n): ");
    scanf_s("%d", &size);
    size = (int)pow(2, size);

    float* vector_a = (float*)malloc(size * sizeof(float));
    float* vector_b = (float*)malloc(size * sizeof(float));

    float time_c = 0.0;
    float time_asm = 0.0;
    float dot_product_c = 0.0;
    float dot_product_asm = 0.0;
    
    for (int i = 0; i < runs; i++) {
        fill_values(max_rand, size, vector_a, vector_b);

        clock_t c_start = clock(); // Timing starts
        dot_product_c = dp_formula_c(size, vector_a, vector_b);
        clock_t c_end = clock(); // Timing ends
        float time_result_c = ((float)(c_end - c_start)) / CLOCKS_PER_SEC;

        clock_t asm_start = clock(); // Timing starts
        dot_product_asm = dp_formula_asm(size, vector_a, vector_b);
        clock_t asm_end = clock(); // Timing ends
        float time_result_asm = ((float)(asm_end - asm_start)) / CLOCKS_PER_SEC;

        printf("Dot product in C:    %.2f\n", dot_product_c);
        printf("Dot product in ASM:  %.2f\n", dot_product_asm);
        printf("Runtime %d: %.6f seconds\n", i + 1, time_result_c);
        printf("Runtime %d: %.6f seconds\n", i + 1, time_result_asm);

        time_c += time_result_c;
        time_asm += time_result_asm;
    }

    float average_time_c = time_c / runs;
    float average_time_asm = time_asm / runs;
    printf("Average execution time in C: %.6f seconds\n", average_time_c);
    printf("Average execution time in Assembly: %.6f seconds\n", average_time_asm);

    free(vector_a);
    free(vector_b);
    return 0;
}
