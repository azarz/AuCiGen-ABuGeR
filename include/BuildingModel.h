#ifndef BUILDINGMODEL_H
#define BUILDINGMODEL_H

#include "Triangle.h"
#include "parcel.h"
#include <vector>

class BuildingModel
{
    public:
        BuildingModel();
        virtual ~BuildingModel();

        void translate();
        void rotate();
        BuildingModel join();
        BuildingModel creat_roof();
        void size();
        void split();
        void repeat();
        void scope();
        void to_obj();

        std::vector<Triangle> li_triangle;
        Parcel *parcel;
    protected:
    private:
};

#endif // BUILDINGMODEL_H
