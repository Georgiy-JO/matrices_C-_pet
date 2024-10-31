#ifndef MATRIX
#define MATRIX
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

#define EPSILON (double)1e-7  // precision for comparing with zero

#define EQUAL 0
#define NOT_EQUAL 1

#define DOUBLE_ZERO (double)0

#define MATRIX_INIT \
  { NULL, 0, 0 }

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

enum Comperison { cmSMALLER = -1, cmEqual = EQUAL, cmBIGGER, COMP_ERR };
// INPUT_ERR - Error, incorrect matrix
// CALC_ERR -Calculation error (mismatched matrix sizes; matrix for which
// calculations cannot be performed, etc.)
enum ReturnCodes { SUCCESS_CALC, INPUT_ERR, CALC_ERR };

// Basic functions
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

// Service functions
int s21_the_matrix_sizer(int rows, int columns, matrix_t *result);

int s21_if_matrix_legit(const matrix_t *matr);
int s21_more_presice_check(const matrix_t *matr);
int s21_if_matrix_rows_legit(const matrix_t *matr);
int s21_if_matrix_legit_complex(const matrix_t *matr);

int s21_if_double_legit(double a);

int s21_double_compare(double a, double b);

int s21_matrix_size_compare(const matrix_t *A, const matrix_t *B);

int s21_recreate_matrix(int rows, int columns, matrix_t *result);
int s21_filling_matrix(matrix_t *mtrx, const double *array);
int s21_matrix_builder(int rows, int columns, matrix_t *result,
                       const double *array);
int s21_matrix_rebuilder(int rows, int columns, matrix_t *result,
                         const double *array);

double s21_determinant_recursive(matrix_t A);
int s21_minor_maker(matrix_t *A, int row, int column, matrix_t *result);
int s21_minor_maker_complex(matrix_t *A, int row, int column, matrix_t *result);

void s21_mult_matrix_waggon(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_calc_complements_waggon(matrix_t *A, matrix_t *result);

// Comperison function
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// Matrix operations functions
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Matrix nature functions
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

#endif