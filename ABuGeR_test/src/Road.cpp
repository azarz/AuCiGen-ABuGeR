#include "Road.h"
#include <iostream>
#include "ogrsf_frmts.h"
#include "poly_to_triangle.h"
#include "Triangle.h"
#include <string>
#include <fstream>
#include "triangles_to_obj.h"


Road::Road(OGRPolygon* poPolygon, int t_r)
{
    geom = poPolygon;
    type = t_r;
}

Road::~Road()
{
    //dtor
}

vector<string> Road::to_obj(OGRPoint* centroid, int& index_offset)
{
    // Converting the road polygons to triangles
    vector<Triangle> triangles;
    poly_to_triangle(geom,triangles,FLOOR);

    return triangles_to_obj(triangles, index_offset, centroid->getX(), centroid->getY());
}
