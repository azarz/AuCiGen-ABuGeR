#ifndef BUILDINGMODEL_H
#define BUILDINGMODEL_H

#include "Triangle.h"
#include "Parcel.h"
#include <vector>

class BuildingModel
{
    public:
        BuildingModel();
        virtual ~BuildingModel();

        void translate();
        void rotate();
        //BuildingModel join();
        //BuildingModel creat_roof();
        void size();
        void split();
        void repeat();
        void scope();
        void to_obj();

        // Getters
        std::vector<Triangle> get_li_triangle()const{return li_triangle;};
        Parcel* get_parcel()const{return parcel;};

    protected:
    private:
        std::vector<Triangle> li_triangle;
        Parcel* parcel;
};

#endif // BUILDINGMODEL_H
