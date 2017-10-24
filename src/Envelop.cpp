#include "Envelop.h"

Envelop::Envelop(Footprint* trace)// have to add an arg Footprint&Envelop pointers to get an envelop from it
{
    //ctor

    /*  //setting the footprint pointer
    this->footprint = trace;
    */

    /*  //setting the parcel pointer
    this->parcel = trace->parcel;
    */

    /*  //setting the the buildingmodel pointer for volume
    this->volume = buildingmodel?????;
    */

    /*  //calculating floor number
	double n_calc(( trace->parcel->get_floorspace() )/( footprint->get_geom()->OGRCurvePolygon::get_Area() ));
	this->floor = static_cast<int>(n_calc); //converting from double to int
    */
}

Envelop::~Envelop()
{
    //dtor
}
