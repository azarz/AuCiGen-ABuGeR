#ifndef GAUSS_INCLUDED
#define GAUSS_INCLUDED

/** @file */
/**
*@fn int gauss3P(double A[3][3], double B[3][1], double C[3][1])
*find if exist the solution of AC=B with 3 parameters
*@param[in] A double[3][3] : matrix 3*3
*@param[in] B double[3][1] : matrix 3*1
*@param[out] C double[3][1] : return matrix 3*1 for the result
*@return i int (0 no solution; 1 solution find; 2 no simple solution)
*/
int gauss3P(double A[3][3], double B[3][1], double C[3][1]);

/**
*@fn int gauss2P(double A[3][2], double B[3][1], double C[2][1])
*find if exist the solution of AC=B with 3 parameters
*@param[in] A double[3][2] : matrix 3*2
*@param[in] B double[3][1] : matrix 3*1
*@param[out] C double[2][1] : return matrix 2*1 for the result
*@return i int (0 no solution; 1 solution find; 2 no simple solution)
*/
int gauss2P(double A[3][2], double B[3][1], double C[2][1]);


#endif // GAUSS_INCLUDED
