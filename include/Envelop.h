#ifndef ENVELOP_H_INCLUDED
#define ENVELOP_H_INCLUDED

#include "BuildingModel.h"
#include "Footprint.h"

class Envelop
{
    public:
        Envelop(Footprint* trace);
        virtual ~Envelop();

        // Getters
        BuildingModel* get_volume()const{return volume;};
        Footprint* get_footprint()const{return footprint;};
        Parcel* get_parcel()const{return parcel;};
        int get_n_floor()const{return n_floor;};
    protected:
    private:
        BuildingModel* volume;
        Footprint* footprint;
        Parcel* parcel;
        int n_floor;
};

#endif // ENVELOP_H_INCLUDED
