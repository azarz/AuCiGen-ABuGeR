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
    *Contain the 3D envelop specs.
    */
    public:
        Envelop();
        /**
        *@fn Envelop::Envelop()
        *Constructor.
        */
        Envelop(Footprint* trace);
        /**
        *@fn Envelop::Envelop(Footprint* trace)
        *Constructor.
        *@param[in] trace Footprint*: The footprint object class.
        */
        virtual ~Envelop();
        /**
        *@fn virtual Envelop::~Envelop()
        *Destructor.
        */
        vector<string> to_obj(OGRPoint* centroid, int& index_offset);
        /**
        *@fn vector<string> to_obj(OGRPoint* centroid, int& index_offset)
        *Converts the Envelop volume to Wavefront .obj format.
        *@param[in] an OGRPoint pointer corresponding to the centroid of the city
        *@param[in] the index offset
        **/

        // Getters
        Footprint* get_footprint()const{return footprint;};
        /**
        *@fn Footprint* Envelop::get_footprint() const
        *Gets the Envelop's footprint.
        *@return a Footprint object pointed.
        */

        Parcel* get_parcel()const{return parcel;};
        /**
        *@fn Parcel* Envelop::get_parcel() const
        *Gets the Envelop's parcel.
        *@return a parcel object pointed within the footprint.
        */

        int get_n_floor()const{return n_floor;};
        /**
        *@fn int Envelop::get_n_floor() const
        *Gets the number of floors in the Envelop.
        *@return the floors number of the envelop.
        */

        double get_height()const{return height;};
        /**
        *@fn double Envelop::get_height() const
        *Gets the height of the Envelop.
        *@return the height of the envelop.
        */

    protected:
    private:
        Footprint* footprint;
        Parcel* parcel;
        int n_floor;
        double height;
};

#endif // ENVELOP_H_INCLUDED
