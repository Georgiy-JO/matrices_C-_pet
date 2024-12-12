
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
