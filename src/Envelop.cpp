#include "Envelop.h"

Envelop::Envelop()// have to add an arg Footprint&Envelop pointers to get an envelop from it
{
    //ctor

    /*//setting the footprint pointer
    Footprint* m_footprint = footprint;
    */

    /*//setting the parcel pointer
    Parcel* m_parcel = footprint->parcel;
    */

    /*//setting the the buildingmodel pointer for volume
    BuildingModel* m_volume = buildingmodel;
    */

    /*//calculating floor number
	double n_calc(( parcel->get_floorspace() )/( footprint->get_geom()->OGRCurvePolygon::get_Area() ));
	int n_floor = static_cast<int>(n_calc); //converting from double to int
    */
}

Envelop::~Envelop()
{
    //dtor
}
