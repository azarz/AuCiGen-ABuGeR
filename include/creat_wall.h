#ifndef CREAT_WALL_H_INCLUDED
#define CREAT_WALL_H_INCLUDED

#include "ogrsf_frmts.h"
#include "Triangle.h"

void creat_wall(OGRPolygon* poPolygon, double height, vector<Triangle>& li_tri);

#endif // CREAT_WALL_H_INCLUDED
