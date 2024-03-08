#ifndef GAUSS_LIB_H
#define GAUSS_LIB_H

#include <stdio.h>
// -D__USE_MINGW_ANSI_STDIO
void gaussEliminationMainRow(size_t rowNum, size_t colNum, long double A[rowNum][colNum], size_t lable[rowNum]);
void gaussBackPropMainRow(size_t rowNum, size_t colNum, long double A[rowNum][colNum], long double *x, size_t lable[rowNum]);

void gaussElimination(size_t rowNum, size_t colNum, long double A[rowNum][colNum], size_t lable[rowNum], long double *x, void (*elim)(size_t, size_t, long double (*)[colNum], size_t *), void (*back)(size_t, size_t, long double (*)[colNum], long double *, size_t *));

#endif
