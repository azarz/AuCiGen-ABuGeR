#ifndef ENVELOP_H_INCLUDED
#define ENVELOP_H_INCLUDED

#include "BuildingModel.h"
#include "Footprint.h"
#include "Triangle.h"
#include <vector>

class Footprint;
class BuildingModel;

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
        vector<Triangle> get_volume()const{return volume;};
        /**
        *@fn Envelop::get_volume()
        *give the Envelop BuildingModel
        *@return an Triangle vector
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
        *@return the number of floors (int)
        */

        double get_height()const{return height;};
        /**
        *@fn Envelop::get_height()
        *give the height of the Envelop
        *@return the height (double)
        */

    protected:
    private:
        vector<Triangle> volume;
        Footprint* footprint;
        Parcel* parcel;
        int n_floor;
        double height;
};

#endif // ENVELOP_H_INCLUDED
