#ifndef FOOTPRINT_H
#define FOOTPRINT_H

class Envelop;
class Parcel;

#include "Parcel.h"
#include "ogrsf_frmts.h"

class Footprint
{
    public:
        Footprint(OGRLinearRing* linearRing, Parcel* parcel);
        virtual ~Footprint();

        Envelop create_envelop();

        // Getters
        OGRLinearRing* get_geom()const{return geom;};
        Parcel* get_parcel()const{return parcel;};
    protected:
    private:
        OGRLinearRing* geom;
        Parcel* parcel;
};

#endif // FOOTPRINT_H
