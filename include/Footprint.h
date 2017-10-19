#ifndef FOOTPRINT_H
#define FOOTPRINT_H

class Envelop;

#include "Parcel.h"
#include "ogrsf_frmts.h"

class Footprint
{
    public:
        Footprint();
        virtual ~Footprint();

        Envelop create_envelop();

        // Getters
        OGRPolygon get_geom()const{return geom;};
        Parcel* get_parcel()const{return parcel;};
    protected:
    private:
        OGRPolygon geom;
        Parcel* parcel;
};

#endif // FOOTPRINT_H
