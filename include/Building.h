#ifndef BUILDING_H
#define BUILDING_H

#include "Parcel.h"
#include "BuildingModel.h"
#include <vector>

class Building
{
    public:
        Building();
        virtual ~Building();

        // Getters
        Parcel* get_parcel()const{return parcel;};
        std::vector<BuildingModel> get_building_model()const{return building_model;};

    protected:
    private:
        Parcel* parcel;
        std::vector<BuildingModel> building_model;
};

#endif // BUILDING_H
