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

        Parcel *parcel;
        std::vector<BuildingModel> building_model;

    protected:
    private:
};

#endif // BUILDING_H
