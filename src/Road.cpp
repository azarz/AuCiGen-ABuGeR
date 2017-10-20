#include "Road.h"
#include <iostream>
#include "ogrsf_frmts.h"

Road::Road(OGRPolygon* poPolygon, int t_r)
{
    geom= poPolygon;
    type= t_r;
}

Road::~Road()
{
    //dtor
}

void Road::to_obj()
{
    //convert to .obj
}

