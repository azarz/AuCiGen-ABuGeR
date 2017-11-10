#ifndef GET_MAX_RECTANGLE_H_INCLUDED
#define GET_MAX_RECTANGLE_H_INCLUDED

#include <iostream>
#include <vector>
#include "ogrsf_frmts.h"
using namespace std;

int larger_rectangle_included(vector<int> b, int N, int M, std::vector<int>& lim, int best_area);
/**
*@fn int larger_rectangle_included(vector<int> b, int N, int M, std::vector<int>& lim, int best_area)
*Find the larger 1 rectangle on a matrix composed of 1 and 0.
*return the best area find.
*@param[in] b: 'matrix' composed of 0 and 1; size N * M ; value(i, j=b(i*M+j).
*@param[in] N: The matrix's line number.
*@param[in] M: The matrix's column number.
*@param[out] lim: The coordinates of the best rectangle found; (p0x, p0y, p1x, p2y, ... p0x, p0y).
*@param[in] best_area: The previous best area for calculation reference.
*@return best_area int
*/
int area(int llx, int lly, int urx, int ury);
/**
*@fn area(int llx, int lly, int urx, int ury)
*Calculates the area of the rectangle.
*@param[in] llx: start x point.
*@param[in] lly: start y point.
*@param[in] urx: end x point.
*@param[in] ury: end y point.
*@return area int
*/
int areaL(int llx, int lly, int urx, int ury, vector<int> b, int M, vector<int>& not_lim);
/**
*@fn areaL(int llx, int lly, int urx, int ury, vector<int> b, int M, vector<int>& not_lim);
*Calculates the area of an L shape on submatrix.
*@param[in] llx: start x point.
*@param[in] lly: start y point.
*@param[in] urx: end x point.
*@param[in] ury: end y point.
*@param[in] b: 'matrix' composed of 0 and 1; M comumn.
*@param[in] M: The matrix's column number.
*@param[in] not_lim: zone not on L shape (xmin, ymin, xmax, ymax).
*@return area int
*/
int sum(int llx, int lly, int urx, int ury, vector<int> b, int M);
/**
*@fn int sum(int llx, int lly, int urx, int ury, vector<int> b, int M)
*Calculates the sum of 1 on submatrix.
*@param[in] llx: start x point.
*@param[in] lly: start y point.
*@param[in] urx: end x point.
*@param[in] ury: end y point.
*@param[in] b: 'matrix' composed of 0 and 1; M comumn.
*@param[in] M: The matrix's column number.
*@return sum int
*/
bool all_ones(int llx, int lly, int urx, int ury, vector<int> b, int M);
/**
*@fn areaL(int llx, int lly, int urx, int ury, vector<int> b, int M, vector<int>& not_lim);
*Test if the submatrix is composed only of 1.
*@param[in] llx: start x point of submatrix.
*@param[in] lly: start y point of submatrix.
*@param[in] urx: end x point of submatrix.
*@param[in] ury: end y point of submatrix.
*@param[in] b: 'matrix' composed of 0 and 1; M comumn.
*@param[in] M: The matrix's column number.
*@return all_ones bool
*/
bool L_ones(int llx, int lly, int urx, int ury, vector<int> b, int M, vector<int>& lim, vector<int>& not_lim);
/**
*@fn L_ones(int llx, int lly, int urx, int ury, vector<int> b, int M, vector<int>& lim, vector<int>& not_lim);
*Test if the submatrix have a L shape composed only of 1.
*@param[in] llx: start x point of submatrix.
*@param[in] lly: start y point of submatrix.
*@param[in] urx: end x point of submatrix.
*@param[in] ury: end y point of submatrix.
*@param[in] b: 'matrix' composed of 0 and 1; M comumn.
*@param[in] M: The matrix's column number.
*@param[out] not_lim: zone not on L shape (xmin, ymin, xmax, ymax).
*@return L_ones bool
*/
vector<double> rotate_p(OGRPoint ptTemp, double centerx, double centery, double A);
/**
*@fn vector<double> rotate_p(OGRPoint ptTemp, double centerx, double centery, double A);
*Rotation of a point around a point.
*@param[in] ptTemp: point to turn.
*@param[in] lly: start y point of submatrix.
*@param[in] centerx: coordinat x of the center of rotation.
*@param[in] centery: coordinat y of the center of rotation.
*@param[in] A: angle (rad)
*@return rotated_point vector<double> : (x, y)
*/
int larger_L_included (vector<int> b, int N, int M, vector<int>& lim, int best_area);
/**
*@fn int larger_L_included (vector<int> b, int N, int M, vector<int>& lim, int best_area);
*Find the larger L shape on a matrix composed of 1 and 0.
*@param[in] b: 'matrix' composed of 0 and 1; size N * M ; value(i, j=b(i*M+j).
*@param[in] N: The matrix's line number.
*@param[in] M: The matrix's column number.
*@param[out] lim: The coordinates of the best rectangle found; (p0x, p0y, p1x, p2y, ... p0x, p0y).
*@param[in] best_area: The previous best area for calculation reference.
*@return best_area int
*/

double angle_calcul(double Xb, double Yb);
#endif // GET_MAX_RECTANGLE_H_INCLUDED
