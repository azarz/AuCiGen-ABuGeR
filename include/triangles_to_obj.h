#ifndef TO_OBJ_H_INCLUDED
#define TO_OBJ_H_INCLUDED

#include <string>
#include <vector>
#include "Triangle.h"

/*! \file */
vector<string> triangles_to_obj(vector<Triangle> triangles);
/**
*@fn vector<string> triangles_to_obj(vector<Triangle> triangles)
*This function allows us to convert our triangle into .obj.
*Returns 3 strings corresponding, in order to the vertices, the uv_coordinates and the faces
*of a vector of Triangle in Wavefront .obj format.
*@param[in] triangles : It's a vector containing the Triangles to convert.
*@return A vector of 3 strings: 1-vertices 2-uv coordinates 3-faces
*/


#endif // TO_OBJ_H_INCLUDED
