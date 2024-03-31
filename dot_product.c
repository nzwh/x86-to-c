#include <stdio.h>
#include <math.h>

const int n20 = 1048576;    // 2^20
const int n24 = 16777216;   // 2^24
const int n27 = 134217728;  // 2^27

int dot_product(int size, double a, double b) {
  double *vector_a = (double *)malloc(size * sizeof(double));
  double *vector_b = (double *)malloc(size * sizeof(double));
  double dot_product = 0.0;

  for (int i = 0; i < size; i++) {
    vector_a[i] = a;
    vector_b[i] = b;
  }

  for (int i = 0; i < size; i++)
    dot_product += vector_a[i] * vector_b[i];

  return dot_product;
}

int main() {
  double result = dot_product(n27, 2.0, 4.0);
  printf("The dot product of the two vectors is: %.2f\n", result);
}