#ifndef MATRIX_METHODS_H_INCLUDED
#define MATRIX_METHODS_H_INCLUDED


/** @file */

void invert_matrix(double mat[3][3],double M[3][3]);
/**
*@fn void invert_matrix (double mat[3][3],double M[3][3]);
*Invert a 3x3 matrix.
*@param[in] mat: The matrix.
*@param[out] M: The inverted matrix.
*/
void matrix_product(double MG[3][3],double MD[3][1], double MR[3][1]);
/**
*@fn void matrix_product (double MG[3][3],double MD[3][1], double MR[3][1]);
*Calculate the product of a 3x3 matrix with a 3x1 matrix.
*@param[in] MG: The 3x3 matrix.
*@param[in] MD: The 3x1 matrix.
*@param[out] MR: The new 3x1 matrix calculated.
*/
void matrix_translation(double T[3][1],double S[3][1],double St[3][1]);
/**
*@fn void matrix_translation (double T[3][1],double S[3][1],double St[3][1]);
*Calculate the translation of a matrix 3x1 by a vector 3x1.
*@param[in] T: The translation vector.
*@param[in] S: The matrix 3x1.
*@param[out] St: The new 3x1 matrix translated.
*/
#endif // MATRIX_METHODS_H_INCLUDED
