#ifndef ENVELOP_H_INCLUDED
#define ENVELOP_H_INCLUDED

#include "BuildingModel.h"
#include "Footprint.h"

class Envelop
{
  /**
    *@class Envelop
    *contain the 3D envelop specs
    */
    public:
        Envelop(Footprint* trace);
        /**
        *@fn Envelop::Envelop()
        *constructor Envelop()
        *@param[in] trace Footprint* : Footprint object class
        */
        virtual ~Envelop();
        /**
        *@fn Envelop::~Envelop()
        *destructor ~Envelop()
        */

        // Getters
        BuildingModel* get_volume()const{return volume;};
        /**
        *@fn Envelop::get_volume()
        *give the Envelop BuildingModel
        *@return an BuildingModel object pointed
        */

        Footprint* get_footprint()const{return footprint;};
        /**
        *@fn Envelop::get_footprint()
        *give the Envelop footprint
        *@return a Footprint object pointed
        */

        Parcel* get_parcel()const{return parcel;};
        /**
        *@fn Envelop::get_parcel()
        *give the Envelop parcel
        *@return a parcel object pointed within the footprint
        */

        int get_n_floor()const{return n_floor;};
        /**
        *@fn Envelop::get_n_floor()
        *give the number of floor in the Envelop
        *@return a parcel object pointed within the footprint
        */

    protected:
    private:
        BuildingModel* volume;
        Footprint* footprint;
        Parcel* parcel;
        int n_floor;
};

#endif // ENVELOP_H_INCLUDED
