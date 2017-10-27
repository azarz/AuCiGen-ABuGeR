#ifndef POLY_TO_TRIANGLE_H_INCLUDED
#define POLY_TO_TRIANGLE_H_INCLUDED


#include <vector>
#include "Triangle.h"
#include "ogrsf_frmts.h"
#include <ogr_geometry.h>

/** @file */
void poly_to_triangle(OGRPolygon* poPolygon, vector<Triangle>& li_vector, TriangleType T_t);
/**
*@fn void poly_to_triangle(OGRPolygon* poPolygon, vector<Triangle>& li_vector , TriangleType T_t)
*create the triangulated surface of a polygon
*@param[in] OGRPolygon* poPolygon : polygon greometry to triangulate
*@param[out] vector<Triangle>& li_vector : empty vector that will be filled with created Triangle objects
*/

#endif // POLY_TO_TRIANGLE_H_INCLUDED
