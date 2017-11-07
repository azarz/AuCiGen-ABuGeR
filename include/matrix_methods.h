#ifndef MATRIX_METHODS_H_INCLUDED
#define MATRIX_METHODS_H_INCLUDED

void invert_matrix(double mat[3][3],double M[3][3]);

void matrix_product(double MG[3][3],double MD[3][1], double MR[3][1]);

void matrix_translation(double T[3][1],double S[3][1],double St[3][1]);

#endif // MATRIX_METHODS_H_INCLUDED
