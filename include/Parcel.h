#ifndef PARCEL_H
#define PARCEL_H

#include "ogrsf_frmts.h"
#include "BuildingType.h"
#include "orient.h"

class Parcel
{
    public:
        Parcel(OGRPolygon* poPolygon);
        virtual ~Parcel();

        OGRLinearRing* create_footprint(OGRLineString* linearIntersection, OGRLineString* otherSides);
        void to_obj();

        // Getters
        OGRPolygon* get_geom()const{return geom;};
        BuildingType* get_type()const{return type;};
        double get_area()const{return area;};
        double get_area_price()const{return area_price;};
        double get_floorspace()const{return floorspace;};

    protected:
    private:
        OGRPolygon* geom;
        BuildingType* type;
        double area;
        double area_price;
        double floorspace;
};

#endif // PARCEL_H
