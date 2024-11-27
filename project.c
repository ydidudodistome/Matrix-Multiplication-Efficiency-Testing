#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef double* matrix;

void ver_ijk(matrix A, matrix B, matrix C, int n)
{
	int i, j, k;
	double sum;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			sum = 0.0;
			for (k = 0; k < n; k++)
				sum += A[i * n + k] * B[k * n + j];
			C[i * n + j] = sum;
		}
}
void ver_jik(matrix A, matrix B, matrix C, int n)
{
	int i, j, k;
	double sum;
	for (j = 0; j < n; j++)
		for (i = 0; i < n; i++) {
			sum = 0.0;
			for (k = 0; k < n; k++)
				sum += A[i * n + k] * B[k * n + j];
			C[i * n + j] = sum;
		}
}
void ver_ikj(matrix A, matrix B, matrix C, int n)
{
	int i, j, k;
	double temp;
	for (i = 0; i < n; i++)
		for (k = 0; k < n; k++) {
			temp = A[i * n + k];
			for (j = 0; j < n; j++)
				C[i * n + j] += temp * B[k * n + j];
		}
}
void ver_kij(matrix A, matrix B, matrix C, int n)
{
	int i, j, k;
	double temp;
	for (k = 0; k < n; k++)
		for (i = 0; i < n; i++) {
			temp = A[i * n + k];
			for (j = 0; j < n; j++)
				C[i * n + j] += temp * B[k * n + j];
		}
}

void ver_kji(matrix A, matrix B, matrix C, int n)
{
	int i, j, k;
	double temp;
	for (k = 0; k < n; k++) {
		for (j = 0; j < n; j++) {
			temp = B[k * n + j];
			for (i = 0; i < n; i++) {
				C[i * n + j] += temp * A[i * n + k];
			}
		}
	}
}
void ver_jki(matrix A, matrix B, matrix C, int n)
{
	int i, j, k;
	double temp;
	for (j = 0; j < n; j++)
		for (k = 0; k < n; k++) {
			temp = B[k * n + j];
			for (i = 0; i < n; i++)
				C[i * n + j] += temp * A[i * n + k];
		}
}


int main(int argc, char* argv[])
{

	if (argc != 3)
	{
		printf("Usage:time %s <functionname> <size>\n", argv[0]);

		return 1;
	}

	char* functionName = argv[1];
	int n = atoi(argv[2]);

	// Allocate the memories
	matrix A = (matrix)malloc(n * n * sizeof(double));
	matrix B = (matrix)malloc(n * n * sizeof(double));
	matrix C = (matrix)malloc(n * n * sizeof(double));


	if (A == NULL || B == NULL || C == NULL)
	{
		printf("Failed to allocate memory\n");
		return 1;
	}

	// Seed for rng based on time
	srand(time(0)); 
	for (int i = 0; i < n * n; i++) {
		A[i] = (double)(rand() % 10); // random value between 1-9
		B[i] = (double)(rand() % 10); // random value between 1-9
		C[i] = 0.0;
	}

	// Prompt user to start timing
	printf("Matrices are now filled. Press ENTER to start timing the multiplication process.\n");
	getchar();  

	// Prompt user
	if (strcmp(functionName, "ijk") == 0) 
	{
		ijk(A, B, C, n);
	}
	else if (strcmp(functionName, "jik") == 0)
	{
		jik(A, B, C, n);
	}
	else if (strcmp(functionName, "ikj") == 0)
	{
		ikj(A, B, C, n);
	}
	else if (strcmp(functionName, "kij") == 0) 
	{
		kij(A, B, C, n);
	}
	else if (strcmp(functionName, "kji") == 0) 
	{
		kji(A, B, C, n);
	}
	else if (strcmp(functionName, "jki") == 0)
	{
		jki(A, B, C, n);
	}
	else {
		printf("Invalid function name: %s\n", functionName);
		free(A); free(B); free(C);
		return 1;
	}

	// Free memory
	free(A); free(B); free(C);

	return 0;

}