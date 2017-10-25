#include "Envelop.h"
#include "BuildingModel.h"
#include "poly_to_triangle.h"
#include "Triangle.h"
#include "creat_wall.h"

Envelop::Envelop(Footprint* trace)// have to add an arg Footprint&Envelop pointers to get an envelop from it
{
    //ctor

    //setting the buildingmodel pointer for volume
    OGRPolygon poPolygon;
    OGRLinearRing a= (OGRLinearRing)trace->get_geom();
    poPolygon.addRing(&a);
    vector<Triangle> li_vector;
    poly_to_triangle(&poPolygon, li_vector, FLOOR);
    creat_wall(&poPolygon, 4, li_vector);


    this->volume= new BuildingModel ( li_vector,  trace->get_parcel());
    cout << "aire envelop : "<<volume->get_parcel()->get_area() <<endl;
    cout << " x : "<<volume->get_li_triangle().at(0).get_p1().get_x() <<endl;
    //setting the footprint pointer
    this->footprint = trace;

    //setting the parcel pointer
    this->parcel = trace->get_parcel();

    //calculating floor number
	double n_calc(( trace->get_parcel()->get_floorspace() )/( trace->get_geom()->OGRLineString::get_Area() ));
	this->n_floor = static_cast<int>(n_calc); //converting from double to int
}

Envelop::~Envelop()
{
    //dtor
}
