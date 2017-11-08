#ifndef GET_MAX_RECTANGLE_H_INCLUDED
#define GET_MAX_RECTANGLE_H_INCLUDED

#include <iostream>
#include <vector>
#include "ogrsf_frmts.h"
using namespace std;

int larger_rectangle_included(vector<int> b, int N, int M, std::vector<int>& lim, int best_area);
int area(int llx, int lly, int urx, int ury);
int areaL(int llx, int lly, int urx, int ury, vector<int> b, int M, vector<int>& not_lim);
bool all_ones(int llx, int lly, int urx, int ury, vector<int> b, int M);
bool L_ones(int llx, int lly, int urx, int ury, vector<int> b, int M, vector<int>& lim, vector<int>& not_lim);
vector<double> rotate_p(OGRPoint ptTemp, double centerx, double centery, double A);
int larger_L_included (vector<int> b, int N, int M, vector<int>& lim, int best_area);
#endif // GET_MAX_RECTANGLE_H_INCLUDED
