#include "s21_matrix.h"

// Basic functions --------------------------------------------------
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows <= 0 || columns <= 0) return INPUT_ERR;
  int flag = SUCCESS_CALC;
  if (result != NULL)
    flag = (s21_the_matrix_sizer(rows, columns, result)) ? SUCCESS_CALC
                                                         : INPUT_ERR;
  else
    flag = INPUT_ERR;
  return flag;
}

// (ノ ◑‿◑)ノ (I'm filling the sizes of the matrix and allocating place)
// never been checked independently
int s21_the_matrix_sizer(int rows, int columns, matrix_t *result) {
  int flag = SUCCESS;
  result->columns = columns;
  result->rows = rows;
  result->matrix = (double **)calloc(rows, sizeof(double *));
  if (result->matrix == NULL) flag = FAILURE;
  for (int i = 0; flag != FAILURE && i < rows; i++) {
    result->matrix[i] = (double *)calloc(columns, sizeof(double));
    if (result->matrix[i] == NULL) {
      flag = FAILURE;
      result->rows = i;
      s21_remove_matrix(result);
    }
  }
  return flag;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    if (A->matrix != NULL) {
      for (int i = 0; i < (A->rows); i++) {
        if (A->matrix[i] != NULL) free(A->matrix[i]);
      }
      free(A->matrix);
      A->matrix = NULL;
    }
    A->columns = 0;
    A->rows = 0;
  }
}

// Service functions ------------------------------------------------
// (ノ ◑‿◑)ノ (I'm checking if the matrix is alright. I'm not too precise.)
int s21_if_matrix_legit(const matrix_t *matr) {
  return (matr == NULL || matr->rows <= 0 || matr->columns <= 0 ||
          matr->matrix == NULL)
             ? FAILURE
             : SUCCESS;
}

// (ノ ◑‿◑)ノ (I'm checking if all the matrix's elements are alright)
// never been checked independently
int s21_more_presice_check(const matrix_t *matr) {
  int flag = SUCCESS;
  for (int i = 0; flag == SUCCESS && i < matr->rows; i++) {
    if (matr->matrix[i] == NULL) flag = FAILURE;
    for (int j = 0; flag == SUCCESS && j < matr->columns; j++) {
      if (!s21_if_double_legit(matr->matrix[i][j])) flag = FAILURE;
    }
  }
  return flag;
}

// (ノ ◑‿◑)ノ (I'm checking if the matrix's rows is alright.)
// never been checked independently
int s21_if_matrix_rows_legit(const matrix_t *matr) {
  for (int i = 0; i < (matr->rows); i++) {
    if (matr->matrix[i] == NULL) return FAILURE;
  }
  return SUCCESS;
}

// (ノ ◑‿◑)ノ (I'm checking if the matrix is alright with great  precision)
int s21_if_matrix_legit_complex(const matrix_t *matr) {
  return (!s21_if_matrix_legit(matr) || !s21_more_presice_check(matr))
             ? FAILURE
             : SUCCESS;
}

// (ノ ◑‿◑)ノ (I'm checking if a double is alright)
int s21_if_double_legit(double a) {
  return (isnan(a) || isinf(a)) ? FAILURE : SUCCESS;
}

// (ノ ◑‿◑)ノ (I'm comparing 2 doubles)
int s21_double_compare(double a, double b) {
  if (isnan(a) || isnan(b) ||
      (isinf(a) && isinf(b) &&
       ((a < DOUBLE_ZERO && b < DOUBLE_ZERO) ||
        (a > DOUBLE_ZERO && b > DOUBLE_ZERO))))
    return COMP_ERR;
  int flag = (a >= b) ? 1 : -1;
  return (fabs(a - b) < EPSILON) ? EQUAL : NOT_EQUAL * flag;
}

// (ノ ◑‿◑)ノ (I'm checking if two matrices are same size)
int s21_matrix_size_compare(const matrix_t *A, const matrix_t *B) {
  return (A->rows == B->rows && A->columns == B->columns) ? SUCCESS : FAILURE;
}

// (ノ ◑‿◑)ノ (I'm removing the current matrix and creating a new one)
// never been checked independently
int s21_recreate_matrix(int rows, int columns, matrix_t *result) {
  if (!s21_if_matrix_legit(result) || rows <= 0 || columns <= 0)
    return INPUT_ERR;
  s21_remove_matrix(result);
  int flag = s21_create_matrix(rows, columns, result);
  return flag;
}

// (ノ ◑‿◑)ノ (I'm filling the matrix with elements from the array (row by row,
// from left to right))
// never been checked independently
int s21_filling_matrix(matrix_t *mtrx, const double *array) {
  if (!s21_if_matrix_legit(mtrx) || !s21_if_matrix_rows_legit(mtrx) ||
      array == NULL)
    return INPUT_ERR;
  for (int i = 0, k = 0; i < mtrx->rows; i++) {
    for (int j = 0; j < mtrx->columns; j++, k++) {
      mtrx->matrix[i][j] = array[k];
    }
  }
  return SUCCESS_CALC;
}

// (ノ ◑‿◑)ノ (I'm creating and filling a matrix)
int s21_matrix_builder(int rows, int columns, matrix_t *result,
                       const double *array) {
  if (s21_create_matrix(rows, columns, result)) return INPUT_ERR;
  return s21_filling_matrix(result, array);
}

// (ノ ◑‿◑)ノ (I'm recreating and filling the matrix)
int s21_matrix_rebuilder(int rows, int columns, matrix_t *result,
                         const double *array) {
  if (s21_recreate_matrix(rows, columns, result)) return INPUT_ERR;
  return s21_filling_matrix(result, array);
}

// (ノ ◑‿◑)ノ (I'm calculating determinant with recursion)
double s21_determinant_recursive(matrix_t A) {
  double det = 0;
  if (A.columns == 1)
    det = A.matrix[0][0];
  else {
    double det_min = 0;
    for (int j = 0; !isnan(det) && j < A.columns; j++) {
      matrix_t minor;
      if (s21_minor_maker_complex(&A, 0, j, &minor)) {
        det = NAN;
        continue;
      }
      det_min = s21_determinant_recursive(minor);
      s21_remove_matrix(&minor);
      if (isnan(det_min)) {
        det = NAN;
        continue;
      }
      det += (pow(-1, j) * A.matrix[0][j] * det_min);
    }
  }
  return det;
}

// (ノ ◑‿◑)ノ (I'm creating minors with given row and column that need to be
// removed from the input matrix)
int s21_minor_maker(matrix_t *A, int row, int column, matrix_t *result) {
  if (!s21_if_matrix_legit(A) || !s21_if_matrix_rows_legit(A) ||
      !s21_if_matrix_legit(result) || !s21_if_matrix_rows_legit(result) ||
      row < 0 || column < 0)
    return INPUT_ERR;
  int flag = (row < A->rows && column < A->columns) ? SUCCESS_CALC : CALC_ERR;
  flag = (!flag && result->rows == A->rows - 1 &&
          result->columns == A->columns - 1)
             ? SUCCESS_CALC
             : CALC_ERR;
  if (!flag) {
    for (int i = 0, k = 0; k < result->rows; i++, k++) {
      if (i == row) i++;
      for (int j = 0, l = 0; l < result->columns; j++, l++) {
        if (j == column) j++;
        result->matrix[k][l] = A->matrix[i][j];
      }
    }
  }
  return flag;
}

// (ノ ◑‿◑)ノ (I'm creating a minor and allocating place for it)
int s21_minor_maker_complex(matrix_t *A, int row, int column,
                            matrix_t *result) {
  if (A == NULL || s21_create_matrix(A->rows - 1, A->columns - 1, result))
    return INPUT_ERR;
  int flag = s21_minor_maker(A, row, column, result);
  if (flag) s21_remove_matrix(result);
  return flag;
}

// (ノ ◑‿◑)ノ (I'm part of the s21_mult_matrix function)
// never been checked independently
void s21_mult_matrix_waggon(matrix_t *A, matrix_t *B, matrix_t *result) {
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      result->matrix[i][j] = 0;
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += ((A->matrix[i][k]) * (B->matrix[k][j]));
      }
    }
  }
}

// (ノ ◑‿◑)ノ (I'm part of the s21_calc_complements)
// never been checked independently
int s21_calc_complements_waggon(matrix_t *A, matrix_t *result) {
  int flag = 0;
  if (A->rows == 1) {
    result->matrix[0][0] = 1;
  } else {
    double det;
    for (int i = 0; !flag && i < A->rows; i++) {
      for (int j = 0; !flag && j < A->columns; j++) {
        matrix_t temp;
        det = 0;
        flag = s21_minor_maker_complex(A, i, j, &temp);
        if (!flag) {
          flag = s21_determinant(&temp, &det);
          s21_remove_matrix(&temp);
        }
        if (!flag) result->matrix[i][j] = pow(-1, i + j) * det;
      }
    }
  }
  return flag;
}

// Comperison function ----------------------------------------------
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (!s21_if_matrix_legit(A) || !s21_if_matrix_legit(B) ||
      !s21_if_matrix_rows_legit(A) || !s21_if_matrix_rows_legit(B))
    return FAILURE;

  int flag = s21_matrix_size_compare(A, B);
  for (int i = 0; flag != FAILURE && i < (A->rows); i++) {
    for (int j = 0; flag != FAILURE && j < (A->columns); j++) {
      if (s21_double_compare(A->matrix[i][j], B->matrix[i][j]) != 0)
        flag = FAILURE;
    }
  }
  return flag;
}

// Matrix operations functions --------------------------------------
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!s21_if_matrix_legit_complex(A) || !s21_if_matrix_legit_complex(B) ||
      result == NULL)
    return INPUT_ERR;
  int flag = (s21_matrix_size_compare(A, B)) ? SUCCESS_CALC : CALC_ERR;
  flag = (!flag && !s21_create_matrix(A->rows, A->columns, result))
             ? SUCCESS_CALC
             : CALC_ERR;

  if (!flag) {
    for (int i = 0; i < (A->rows); i++) {
      for (int j = 0; j < (A->columns); j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return flag;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!s21_if_matrix_legit_complex(A) || !s21_if_matrix_legit_complex(B) ||
      result == NULL)
    return INPUT_ERR;
  int flag = (s21_matrix_size_compare(A, B)) ? SUCCESS_CALC : CALC_ERR;
  flag = (!flag && !s21_create_matrix(A->rows, A->columns, result))
             ? SUCCESS_CALC
             : CALC_ERR;

  if (!flag) {
    for (int i = 0; i < (A->rows); i++) {
      for (int j = 0; j < (A->columns); j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return flag;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (!s21_if_matrix_legit_complex(A) || result == NULL) return INPUT_ERR;
  int flag = (s21_if_double_legit(number)) ? SUCCESS_CALC : INPUT_ERR;
  if (!flag)
    flag = (!s21_create_matrix(A->rows, A->columns, result)) ? SUCCESS_CALC
                                                             : CALC_ERR;

  if (!flag) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return flag;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!s21_if_matrix_legit_complex(A) || !s21_if_matrix_legit_complex(B) ||
      result == NULL)
    return INPUT_ERR;
  int flag = (B->rows == A->columns) ? SUCCESS_CALC : CALC_ERR;
  flag = (!flag && !s21_create_matrix(A->rows, B->columns, result))
             ? SUCCESS_CALC
             : CALC_ERR;

  if (!flag) {
    s21_mult_matrix_waggon(A, B, result);
  }
  return flag;
}

// Matrix nature functions-------------------------------------------
int s21_transpose(matrix_t *A, matrix_t *result) {
  if (!s21_if_matrix_legit(A) || !s21_if_matrix_rows_legit(A) || result == NULL)
    return INPUT_ERR;
  int flag = (!s21_create_matrix(A->columns, A->rows, result)) ? SUCCESS_CALC
                                                               : CALC_ERR;

  if (!flag) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return flag;
}

int s21_determinant(matrix_t *A, double *result) {
  if (!s21_if_matrix_legit_complex(A) || result == NULL) return INPUT_ERR;
  int flag = (A->rows == A->columns) ? SUCCESS_CALC : CALC_ERR;

  if (!flag) *result = s21_determinant_recursive(*A);
  if (isnan(*result)) {
    flag = CALC_ERR;
    *result = 0;
  }
  return flag;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (!s21_if_matrix_legit_complex(A) || result == NULL) return INPUT_ERR;
  int flag = (A->rows == A->columns) ? SUCCESS_CALC : CALC_ERR;
  flag = (!flag && !s21_create_matrix(A->rows, A->columns, result))
             ? SUCCESS_CALC
             : CALC_ERR;

  if (!flag) {
    flag = s21_calc_complements_waggon(A, result);
    if (flag) s21_remove_matrix(result);
  }
  return flag;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (!s21_if_matrix_legit_complex(A) || result == NULL) return INPUT_ERR;
  int flag = (A->rows == A->columns) ? SUCCESS_CALC : CALC_ERR;
  double det = 0;
  flag = (!flag && !s21_determinant(A, &det) && det != 0) ? SUCCESS_CALC
                                                          : CALC_ERR;

  if (!flag) {
    matrix_t temp_1;
    flag = s21_calc_complements(A, &temp_1);
    if (!flag) {
      matrix_t temp_2;
      flag = (!s21_transpose(&temp_1, &temp_2)) ? SUCCESS_CALC : CALC_ERR;
      s21_remove_matrix(&temp_1);
      if (!flag) {
        det = 1 / det;
        flag =
            (!s21_mult_number(&temp_2, det, result)) ? SUCCESS_CALC : CALC_ERR;
        s21_remove_matrix(&temp_2);
      }
    }
  }
  return flag;
}

/* Extra functions:
  // (ノ ◑‿◑)ノ (I'm filling the matrix with elements from the array and I won't
  fill "+/-nan" and "+/-inf") int filling_matrix_safer(matrix_t *mtrx, double*
  array){ if(!s21_if_matrix_legit(mtrx)|| !s21_if_matrix_rows_legit(mtrx) ||
  array==NULL) return INPUT_ERR; int flag=SUCCESS_CALC; for(int
  i=0,k=0;flag==SUCCESS_CALC && i<mtrx->rows;i++){ for(int
  j=0;flag==SUCCESS_CALC
  && j<mtrx->columns;j++,k++){ if(s21_if_double_legit(array[k]))
          mtrx->matrix[i][j]=array[k];
        else
          flag=INPUT_ERR;
      }
    }
    return flag;
  }
*/