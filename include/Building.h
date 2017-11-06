#ifndef BUILDING_H
#define BUILDING_H

#include "Parcel.h"
#include "BuildingModel.h"
#include <vector>

class Building
{
/**
*@class Building
*Contain the Building.
*/
    public:
        Building();
        /**
        *@fn Building::Building()
        *Constructor.
        */
        virtual ~Building();
        /**
        *@fn virtual Building::~Building()
        *Destructor.
        */

        void creat_roof(double roofAngle);
        /**
        *@fn BuildingModel Building::creat_roof(double roofAngle)
        *Creates a roof for a simple building depending of his roof angle.
        *@param[in] roofAngle: The roof angle.
        */

        void to_obj(OGRPoint* centroid);
        /**
        *@fn void Building::to_obj()
        *Converts the Building to Wavefront .obj format.
        *@param[in] an OGRPoint pointer corresponding to the centroid of the city
        **/

        // Getters
        Parcel* get_parcel()const{return parcel;};
        /**
        *@fn Parcel* Building::get_parcel() const
        *Gets the Parcel associated with the building.
        *@return parcel Parcel*
        */
        std::vector<BuildingModel> get_building_model()const{return building_model;};
        /**
        *@fn std::vector<BuildingModel> Building::get_building_model() const
        *Gets the list of BuildingModel associated to one house.
        *@return building_model std::vector<BuildingModel>
        */

    protected:
    private:
        Parcel* parcel;
        std::vector<BuildingModel> building_model;
};

#endif // BUILDING_H
