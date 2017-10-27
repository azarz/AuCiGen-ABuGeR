#ifndef TO_OBJ_H_INCLUDED
#define TO_OBJ_H_INCLUDED

#include <string>
#include <vector>
#include "Triangle.h"

/*! \file */

/**
* Returns 3 strings corresponding, in order to the vertices, the uv_coordinates and the faces
* of a vector of Triangle in Wavefront .obj format
* @param[in] triangles A vector containing the Triangles to convert
* @return A vector of 3 strings: 1-vertices 2-uv coordinates 3-faces
*/
vector<string> to_obj(vector<Triangle> triangles);


#endif // TO_OBJ_H_INCLUDED
