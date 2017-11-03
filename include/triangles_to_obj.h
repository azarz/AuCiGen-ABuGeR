#ifndef TO_OBJ_H_INCLUDED
#define TO_OBJ_H_INCLUDED

#include <string>
#include <vector>
#include "Triangle.h"

/*! \file */
vector<string> triangles_to_obj(vector<Triangle> triangles, double x_centroid = 0, double y_centroid = 0);
/**
*@fn vector<string> triangles_to_obj(vector<Triangle> triangles)
*Converts a list of triangles into Wavefront .obj format.
*Returns 3 strings corresponding respectively to the vertices, the uv_coordinates and the faces
*of a vector of Triangle in Wavefront .obj format.
*@param[in] triangles: It's a vector containing the Triangles to convert.
*@param[in] x_centroid: The X coordinate of the centroid. Default 0.
*@param[in] y_centroid: The Y coordinate of the centroid. Default 0.
*@return A vector of 3 strings: 1-vertices 2-uv coordinates 3-faces
*/


#endif // TO_OBJ_H_INCLUDED
