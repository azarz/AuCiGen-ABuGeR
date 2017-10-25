#ifndef BUILDING_H
#define BUILDING_H

#include "Parcel.h"
#include "BuildingModel.h"
#include <vector>

class Building
{
    public:
        Building();
        /**
        *@fn Building::Building()
        *Constructor
        */
        virtual ~Building();
        /**
        *@fn virtual Building::~Building()
        *Destructor
        */

        // Getters
        Parcel* get_parcel()const{return parcel;};
        /**
        *@fn Parcel* get_parcel()
        *Get the Parcel associated with the building
        *@return parcel Parcel*
        */
        std::vector<BuildingModel> get_building_model()const{return building_model;};
        /**
        *@fn std::vector<BuildingModel> get_building_model()
        *Get the list of BuildingModel associated to one house
        *@return building_model std::vector<BuildingModel>
        */

    protected:
    private:
        Parcel* parcel;
        std::vector<BuildingModel> building_model;
};

#endif // BUILDING_H
