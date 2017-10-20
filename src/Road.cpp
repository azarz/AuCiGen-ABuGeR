#include "Road.h"
#include <iostream>
#include "ogrsf_frmts.h"

Road::Road(OGRPolygon* poPolygon, std::string t_r)
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

