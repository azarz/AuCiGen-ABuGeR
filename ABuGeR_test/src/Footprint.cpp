#include "Footprint.h"

#include "Envelop.h"
#include "Parcel.h"

using namespace std;

Footprint::Footprint()
{
    //ctor
}

Footprint::Footprint(OGRLinearRing* linearRing, Parcel* parcel)
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
    // return an object envelop instancied by Envelop class from here
    Envelop a = Envelop(this);
    return a;
}

