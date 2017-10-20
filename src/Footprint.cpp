#include "Footprint.h"
#include "Envelop.h"
#include "Parcel.h"

Footprint::Footprint(OGRLinearRing* linearRing,Parcel* parcel)
{
    this->geom = linearRing;
    this->parcel = parcel;
}

Footprint::~Footprint()
{
    //dtor
}

Envelop Footprint::create_envelop()
{
    //_
}
