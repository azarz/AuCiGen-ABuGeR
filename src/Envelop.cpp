#include "Envelop.h"

Envelop::Envelop(Footprint* trace)// have to add an arg Footprint&Envelop pointers to get an envelop from it
{
    //ctor

    /*//setting the buildingmodel pointer for volume
    this->volume = buildingmodel?????;
    */

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
