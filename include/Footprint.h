#ifndef FOOTPRINT_H
#define FOOTPRINT_H

class Envelop;
class Parcel;

#include "Parcel.h"
#include "ogrsf_frmts.h"

class Footprint
{
    /**
    *@class Footprint
    *contain the Footprint specs
    */
    public:
        Footprint(OGRLinearRing* linearRing, Parcel* parcel);
        /**
        *@fn Footprint::Footprint()
        *constructor Footprint()
        *@param[in] linearRing OGRLinearRing* : bounds of the parcel
        *@param[in] linearRing OGRLinearRing* : parcel object class
        */
        virtual ~Footprint();
        /**
        *@fn Footprint::~Footprint()
        *destructor ~Footprint()
        */

        Envelop create_envelop();
        /**
        *@fn Footprint::create_envelop()
        *create give an envelop on the parcel
        @return an Envelop object
        */
        // Getters
        OGRLinearRing* get_geom()const{return geom;};
        /**
        *@fn Footprint::get_geom()
        *give the parcel geometry
        *@return an OGRLinearRing object pointed
        */

        Parcel* get_parcel()const{return parcel;};
        /**
        *@fn Footprint::get_parcel()
        *give the parcel object
        *@return a Parcel object pointed
        */

    protected:
    private:
        OGRLinearRing* geom;
        Parcel* parcel;
};

#endif // FOOTPRINT_H
