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
    *Contain the Footprint specs.
    */
    public:
        Footprint(OGRLinearRing* linearRing, Parcel* parcel);
        /**
        *@fn Footprint::Footprint(OGRLinearRing* linearRing, Parcel* parcel)
        *Constructor Footprint()
        *@param[in] linearRing: The bounds of the parcel.
        *@param[in] parcel: The parcel object on which the Footprint is calculated.
        */
        virtual ~Footprint();
        /**
        *@fn virtual Footprint::~Footprint()
        *destructor ~Footprint()
        */

        Envelop create_envelop();
        /**
        *@fn Envelop Footprint::create_envelop()
        *Creates the Envelop of the Footprint.
        @return an Envelop object.
        */
        // Getters
        OGRLinearRing* get_geom()const{return geom;};
        /**
        *@fn OGRLinearRing* Footprint::get_geom() const
        *Gets the footprint geometry.
        *@return an OGRLinearRing object pointed.
        */

        Parcel* get_parcel()const{return parcel;};
        /**
        *@fn Parcel* Footprint::get_parcel() const
        *Gets the parcel object associated with the footprint.
        *@return a Parcel object pointed.
        */

    protected:
    private:
        OGRLinearRing* geom;
        Parcel* parcel;
};

#endif // FOOTPRINT_H
