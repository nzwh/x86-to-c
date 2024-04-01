#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>

const int n20 = 1048576;    // 2^20
const int n24 = 16777216;   // 2^24
const int n27 = 134217728;  // 2^27

extern float dp_formula_asm(float vector_a, float vector_b);

float dp_formula(int size, float* vector_a, float* vector_b) {
  float dot_product = 0.0;

  for (int i = 0; i < size; i++)
    dot_product += vector_a[i] * vector_b[i];

  return dot_product;
}

int main() {
  srand((unsigned int)time(NULL));

  int cmp = 0;
  int size;
  printf("Input a vector size: ");
  scanf_s("%d", &size);
  size = (int)pow(2, size);

  float* vector_a = (float*)malloc(size * sizeof(float));
  float* vector_b = (float*)malloc(size * sizeof(float));

  int runs = 30;
  float time_c = 0.0;
  float time_asm = 0.0;
  float dot_product_c = 0.0;
  float dot_product_asm = 0.0;

  for (int i = 0; i < runs; i++) {
    for (int j = 0; j < size; j++) {
      vector_a[j] = (float)rand() / RAND_MAX;
      vector_b[j] = (float)rand() / RAND_MAX;
    }

    clock_t start = clock(); // Timing starts
    dot_product_c = dp_formula(size, vector_a, vector_b);
    clock_t end = clock(); // Timing ends

    float time_result_c = ((float)(end - start)) / CLOCKS_PER_SEC;

    float dp_asm_total = 0.0;

    // clock_t start2 = clock(); // Timing starts
    // for (int k = 0; k < size; k++) {
    //   dp_asm_total += dp_formula_asm(vector_a[k], vector_b[k]);
    // }
    // dot_product_asm = dp_asm_total
    // clock_t end2 = clock(); // Timing ends

    // float time_result_asm = ((float)(end2 - start2)) / CLOCKS_PER_SEC;

    printf("Dot product in C: %.2f\n", dot_product_c);
    // printf("Dot product in Assembly: %.2f\n", dot_product_asm);
    printf("Runtime %d: %.6f seconds\n", i + 1, time_result_c);
    // printf("Runtime %d: %.6f seconds\n", i + 1, time_result_asm);

    // if (dot_product_c != dot_product_asm) {
    //   cmp = 1;
    //   break;
    // }

    time_c += time_result_c;
    // time_asm += time_result_asm;
  }

  if (cmp == 1) {
    printf("Dot product not equal");
  }
  else {
    float average_time_c = time_c / runs; // Calculate average of C
    // float average_time_asm = time_asm / runs; // Calculate average of Assembly
    printf("Average execution time in C: %.6f seconds\n", average_time_c);
    // printf("Average execution time in Assembly: %.6f seconds\n", average_time_asm);
  }

  free(vector_a);
  free(vector_b);

  return 0;
}
