#ifndef CREAT_WALL_H_INCLUDED
#define CREAT_WALL_H_INCLUDED

#include "ogrsf_frmts.h"
#include "Triangle.h"

void create_wall(OGRPolygon* poPolygon, double height, vector<Triangle>& li_tri);
/**
*@fn void create_wall(OGRPolygon* poPolygon, double height, vector<Triangle>& li_tri)
*Create walls from the building footprint
*@param[in] poPolygon OGRPolygon* : building footprint geometry
*@param[in] height double : building height
*@param[out] li_tri vector<Triangle>& : output list of WALL Triangle
*/

#endif // CREAT_WALL_H_INCLUDED
