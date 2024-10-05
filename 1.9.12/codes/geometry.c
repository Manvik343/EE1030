#include <math.h>

// Function to calculate the distance between two points
double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// Function to calculate the midpoint between two points
void midpoint(double x1, double y1, double x2, double y2, double* mx, double* my) {
    *mx = (x1 + x2) / 2.0;
    *my = (y1 + y2) / 2.0;
}

