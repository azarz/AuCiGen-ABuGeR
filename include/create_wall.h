#ifndef CREATE_WALL_H_INCLUDED
#define CREATE_WALL_H_INCLUDED

#include "ogrsf_frmts.h"
#include "Triangle.h"

/** @file */
void create_wall(OGRPolygon* poPolygon, double height, vector<Triangle>& li_tri);
/**
*@fn void create_wall(OGRPolygon* poPolygon, double height, vector<Triangle>& li_tri)
*Creates walls from the building footprint.
*@param[in] poPolygon: The building footprint geometry.
*@param[in] height: The building height.
*@param[in/out] li_tri: The output list of WALL Triangle.
*/

#endif // CREAT_WALL_H_INCLUDED
