#include "Envelop.h"

#include <vector>
#include <iostream>
#include <string>

#include "BuildingModel.h"
#include "Footprint.h"
#include "Parcel.h"
#include "Triangle.h"

#include "create_wall.h"
#include "create_env_roof.h"
#include "poly_to_triangle.h"
#include "triangles_to_obj.h"

Envelop::Envelop()
{
    //ctor
}

Envelop::Envelop(Footprint* trace)// have to add an arg Footprint&Envelop pointers to get an envelop from it
{
    //ctor

    //calculating floor number
    double n_calc(( trace->get_parcel()->get_floorspace() )/( trace->get_geom()->OGRLineString::get_Area() ));
	this->n_floor = static_cast<int>(n_calc); //converting from double to int

    //setting the BuildingModel pointer for volume
    height =trace->get_parcel()->get_type()->get_height(n_floor);

    //setting the parcel pointer
    this->parcel = trace->get_parcel();

    //setting the footprint pointer
    this->footprint = trace;
}

Envelop::~Envelop()
{
    //dtor
}

vector<string> Envelop::to_obj(OGRPoint* centroid, int& index_offset)
{
    OGRPolygon poPolygon = OGRPolygon();
    OGRLinearRing* a = footprint->get_geom();
    poPolygon.addRing(a);
    vector<Triangle> li_triangles;
    poly_to_triangle(&poPolygon, li_triangles, FLOOR);
    create_env_roof(height, li_triangles);
    create_wall(&poPolygon, height, li_triangles);
    return triangles_to_obj(li_triangles, index_offset, centroid->getX(), centroid->getY());
}
