#include <stdio.h>
#include <math.h>

int main() {
    FILE *file;
    file = fopen("parabola_points.txt", "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Generate points for the parabola x^2 = 4y
    float x, y;
    float step = 0.1;  // Step size for x and y
    float x_max = 5;   // Maximum value of x (for both parabolas)

    fprintf(file, "# Points for x^2 = 4y\n");
    for (x = -x_max; x <= x_max; x += step) {
        y = (x * x) / 4.0;
        fprintf(file, "%f %f\n", x, y);
    }

    // Generate points for the parabola y^2 = 4x
    float y_max = 5;  // Maximum value of y

    fprintf(file, "\n# Points for y^2 = 4x\n");
    for (y = -y_max; y <= y_max; y += step) {
        x = (y * y) / 4.0;
        fprintf(file, "%f %f\n", x, y);
    }

    fclose(file);
    printf("Points for both parabolas have been written to parabola_points.txt\n");
    return 0;
}

