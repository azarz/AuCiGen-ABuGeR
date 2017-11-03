#ifndef CREAT_WALL_H_INCLUDED
#define CREAT_WALL_H_INCLUDED

#include "ogrsf_frmts.h"
#include "Triangle.h"

/** @file */
void create_wall(OGRPolygon* poPolygon, double height, vector<Triangle>& li_tri);
/**
*@fn void create_wall(OGRPolygon* poPolygon, double height, vector<Triangle>& li_tri)
*This function allows us to create walls from the building footprint.
*@param[in] poPolygon OGRPolygon* : It's the building footprint geometry.
*@param[in] height double : It's the building height.
*@param[out] li_tri vector<Triangle>& : It's the output list of WALL Triangle.
*/

#endif // CREAT_WALL_H_INCLUDED
