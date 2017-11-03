#ifndef CREAT_WALL_H_INCLUDED
#define CREAT_WALL_H_INCLUDED

#include "ogrsf_frmts.h"
#include "Triangle.h"

/** @file */
void create_wall(OGRPolygon* poPolygon, double height, vector<Triangle>& li_tri);
/**
*@fn void create_wall(OGRPolygon* poPolygon, double height, vector<Triangle>& li_tri)
*Creates walls from the building footprint.
*@param[in] poPolygon OGRPolygon*: The building footprint geometry.
*@param[in] height double: The building height.
*@param[out] li_tri vector<Triangle>&: The output list of WALL Triangle.
*/

#endif // CREAT_WALL_H_INCLUDED
