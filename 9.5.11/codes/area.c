#include <stdio.h>
#include <math.h>

// Function for the first curve y = x^2 / 4
double func1(double x) {
    return x * x / 4;
}

// Function for the second curve x = y^2 / 4 (inverse)
double func2(double y) {
    return y * y / 4;
}

// Function to compute the area between the curve y = x^2/4 and x-axis
double computeAreaUnderCurve1(double a, double b, int n) {
    double delta_x = (b - a) / n; // Step size
    double area = 0.0;
    for (int i = 0; i < n; i++) {
        double x = a + i * delta_x;
        double y = func1(x);  // Get y = x^2 / 4
        area += y * delta_x;  // Add the area of each slice
    }
    return area;
}

// Function to compute the area between the curve x = y^2 / 4 and y-axis
double computeAreaUnderCurve2(double a, double b, int n) {
    double delta_y = (b - a) / n; // Step size
    double area = 0.0;
    for (int i = 0; i < n; i++) {
        double y = a + i * delta_y;
        double x = func2(y);  // Get x = y^2 / 4
        area += x * delta_y;  // Add the area of each slice
    }
    return area;
}

// Function to compute the area between two curves using numerical integration
double computeAreaBetweenCurves(double a, double b, int n) {
    double delta_x = (b - a) / n; // Step size
    double area = 0.0;
    for (int i = 0; i < n; i++) {
        double x = a + i * delta_x;
        double y1 = func1(x); // First curve: y = x^2 / 4
        double y2 = sqrt(4 * x); // Second curve: y = sqrt(4x), rearranged from y^2 = 4x
        area += (y2 - y1) * delta_x; // Add the area of each slice
    }
    return area;
}

int main() {
    double a = 0.0;  // Lower limit of integration
    double b = 4.0;  // Upper limit of integration
    int n = 1000;    // Number of slices (higher value for better accuracy)

    // Compute the areas
    double areaBetweenCurves = computeAreaBetweenCurves(a, b, n);
    double areaUnderFunc1 = computeAreaUnderCurve1(a, b, n); // Area between y = x^2 / 4 and x-axis
    double areaUnderFunc2 = computeAreaUnderCurve2(0.0, sqrt(4 * b), n); // Area between x = y^2 / 4 and y-axis

    // Open a file to write the output
    FILE *file = fopen("area.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write the results to the file
    fprintf(file, "The area between the curves is: %lf\n", areaBetweenCurves);
    fprintf(file, "The area between the curve y = x^2 / 4 and the x-axis is: %lf\n", areaUnderFunc1);
    fprintf(file, "The area between the curve x = y^2 / 4 and the y-axis is: %lf\n", areaUnderFunc2);

    // Close the file
    fclose(file);

    // Print message indicating success
    printf("Output has been written to output.txt\n");

    return 0;
}

