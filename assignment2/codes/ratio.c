// ratio.c
#include "ratio.h"
#include <stdlib.h>
#include <math.h>

// Function to compute the greatest common divisor (GCD) using the Euclidean algorithm
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate the ratio m:n using section formula based on x-coordinates
void calculateRatio(float x1, float y1, float x2, float y2, float x3, float y3, int *m, int *n) {
    // Calculate absolute differences
    float dx1 = fabs(x2 - x1);
    float dx2 = fabs(x3 - x2);

    if (dx2 == 0) {
        // Handle case where x2 == x3
        *m = 0;
        *n = 0;
        return;
    }

    // Calculate the ratio m:n
    int m_int = round(dx1 * 1000);  // Scale for precision
    int n_int = round(dx2 * 1000);

    // Simplify the ratio
    int divisor = gcd(abs(m_int), abs(n_int));
    *m = m_int / divisor;
    *n = n_int / divisor;
}

