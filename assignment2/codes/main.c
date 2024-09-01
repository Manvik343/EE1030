// main.c
#include <stdio.h>
#include "ratio.h"

int main() {
    // Define the coordinates of the points
    float x1 = -6, y1 = 10;
    float x2 = -4, y2 = 6;
    float x3 = 3, y3 = -8;

    // Calculate the ratio in which B divides AC
    int m, n;
    calculateRatio(x1, y1, x2, y2, x3, y3, &m, &n);

    if (m == 0 && n == 0) {
        printf("The ratio is undefined (division by zero).\n");
    } else {
        printf("Ratio m:n = %d:%d\n", m, n);
    }

    return 0;
}



