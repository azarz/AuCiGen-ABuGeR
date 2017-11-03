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
        *@param[in] linearRing : It's the bounds of the parcel.
        *@param[in] parcel OGRLinearRing* : It's the parcel object class.
        */
        virtual ~Footprint();
        /**
        *@fn virtual Footprint::~Footprint()
        *destructor ~Footprint()
        */

        Envelop create_envelop();
        /**
        *@fn Envelop Footprint::create_envelop()
        *This function allows us to create give an envelop on the parcel.
        @return an Envelop object.
        */
        // Getters
        OGRLinearRing* get_geom()const{return geom;};
        /**
        *@fn OGRLinearRing* Footprint::get_geom() const
        *This function allows us to give the parcel geometry.
        *@return an OGRLinearRing object pointed.
        */

        Parcel* get_parcel()const{return parcel;};
        /**
        *@fn Parcel* Footprint::get_parcel() const
        *This function allows us to give the parcel object.
        *@return a Parcel object pointed.
        */

    protected:
    private:
        OGRLinearRing* geom;
        Parcel* parcel;
};

#endif // FOOTPRINT_H
