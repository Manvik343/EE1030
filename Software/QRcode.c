#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define MAX_ITER 5000
#define TOLERANCE 1e-14

// Matrix structure
typedef struct {
    int n;              // Matrix dimension
    double **elements;  // 2D array for matrix elements
} Matrix;

// Function to create a matrix
Matrix* createMatrix(int n) {
    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
    matrix->n = n;
    matrix->elements = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        matrix->elements[i] = (double*)malloc(n * sizeof(double));
    }
    return matrix;
}

// Function to free a matrix
void freeMatrix(Matrix* matrix) {
    for (int i = 0; i < matrix->n; i++) {
        free(matrix->elements[i]);
    }
    free(matrix->elements);
    free(matrix);
}

// Function to copy a matrix
void copyMatrix(Matrix* src, Matrix* dest) {
    for (int i = 0; i < src->n; i++) {
        for (int j = 0; j < src->n; j++) {
            dest->elements[i][j] = src->elements[i][j];
        }
    }
}

// Function to transpose a matrix
void transposeMatrix(Matrix* matrix) {
    int n = matrix->n;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double temp = matrix->elements[i][j];
            matrix->elements[i][j] = matrix->elements[j][i];
            matrix->elements[j][i] = temp;
        }
    }
}

// Function to multiply matrices
void multiplyMatrices(Matrix* A, Matrix* B, Matrix* C) {
    int n = A->n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C->elements[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C->elements[i][j] += A->elements[i][k] * B->elements[k][j];
            }
        }
    }
}

// Function to perform Householder transformation
void householder(Matrix* A, Matrix* Q, Matrix* R) {
    int n = A->n;
    copyMatrix(A, R);

    // Initialize Q as the identity matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Q->elements[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    for (int k = 0; k < n - 1; k++) {
        double* x = (double*)calloc(n, sizeof(double));
        double norm = 0;

        // Get column vector below diagonal
        for (int i = k; i < n; i++) {
            x[i] = R->elements[i][k];
            norm += x[i] * x[i];
        }
        norm = sqrt(norm);

        if (fabs(norm) > TOLERANCE) {
            // Compute Householder vector
            double alpha = (x[k] >= 0) ? -norm : norm;
            x[k] -= alpha;
            double beta = 0;
            for (int i = k; i < n; i++) {
                beta += x[i] * x[i];
            }
            beta = sqrt(beta);

            if (fabs(beta) > TOLERANCE) {
                for (int i = k; i < n; i++) {
                    x[i] /= beta;
                }

                // Form Householder matrix K = I - 2 * v * v^T
                Matrix* K = createMatrix(n);
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        K->elements[i][j] = (i == j) ? 1.0 : 0.0;
                    }
                }
                for (int i = k; i < n; i++) {
                    for (int j = k; j < n; j++) {
                        K->elements[i][j] -= 2.0 * x[i] * x[j];
                    }
                }

                // Update R = K * R
                Matrix* tempR = createMatrix(n);
                multiplyMatrices(K, R, tempR);
                copyMatrix(tempR, R);
                freeMatrix(tempR);

                // Update Q = Q * K^T
                transposeMatrix(K);
                Matrix* tempQ = createMatrix(n);
                multiplyMatrices(Q, K, tempQ);
                copyMatrix(tempQ, Q);
                freeMatrix(tempQ);

                freeMatrix(K);
            }
        }
        free(x);
    }
}

// Function to check if matrix is essentially upper triangular
int isUpperTriangular(Matrix* A) {
    int n = A->n;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (fabs(A->elements[i][j]) > TOLERANCE) {
                return 0;
            }
        }
    }
    return 1;
}

// Function to solve 2x2 eigenvalues using quadratic formula
void solve2x2(double a11, double a12, double a21, double a22,
              double complex* eig1, double complex* eig2) {
    double tr = a11 + a22;
    double det = a11 * a22 - a12 * a21;
    double complex disc = csqrt(tr * tr - 4.0 * det);
    *eig1 = (tr + disc) / 2.0;
    *eig2 = (tr - disc) / 2.0;
}

// Main function to compute eigenvalues using QR algorithm
void computeEigenvalues(Matrix* A, double complex* eigenvalues) {
    int n = A->n;
    Matrix* H = createMatrix(n);
    Matrix* Q = createMatrix(n);
    Matrix* R = createMatrix(n);
    Matrix* temp = createMatrix(n);

    copyMatrix(A, H);

    int iter = 0;
    while (!isUpperTriangular(H) && iter < MAX_ITER) {
        // QR decomposition
        householder(H, Q, R);
        
        // Multiply R*Q for next iteration
        multiplyMatrices(R, Q, temp);
        copyMatrix(temp, H);

        iter++;
    }

    // Extract eigenvalues
    for (int i = 0; i < n; i++) {
        if (i < n - 1 && fabs(H->elements[i + 1][i]) > TOLERANCE) {
            // Solve 2x2 block
            solve2x2(H->elements[i][i], H->elements[i][i + 1],
                     H->elements[i + 1][i], H->elements[i + 1][i + 1],
                     &eigenvalues[i], &eigenvalues[i + 1]);
            i++; // Skip next element
        } else {
            eigenvalues[i] = H->elements[i][i];
        }
    }

    freeMatrix(H);
    freeMatrix(Q);
    freeMatrix(R);
    freeMatrix(temp);
}

// Function to read matrix from user input
Matrix* readMatrix() {
    int n;
    printf("Enter matrix dimension (n): ");
    scanf("%d", &n);

    Matrix* matrix = createMatrix(n);
    printf("Enter matrix elements (real only):\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("A[%d][%d] = ", i, j);
            scanf("%lf", &matrix->elements[i][j]);
        }
    }

    return matrix;
}

int main() {
    // Read matrix from user
    Matrix* A = readMatrix();
    int n = A->n;

    // Allocate array for eigenvalues
    double complex* eigenvalues = (double complex*)malloc(n * sizeof(double complex));

    // Compute eigenvalues
    computeEigenvalues(A, eigenvalues);

    // Print results
    printf("\nEigenvalues:\n");
    for (int i = 0; i < n; i++) {
        printf("%d: %.6f + %.6fi\n", i + 1, creal(eigenvalues[i]), cimag(eigenvalues[i]));
    }

    // Free memory
    freeMatrix(A);
    free(eigenvalues);

    return 0;
}

