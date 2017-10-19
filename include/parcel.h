#ifndef PARCEL_H
#define PARCEL_H

#include "ogrsf_frmts.h"
#include "BuildingType.h"
#include "orient.h"

class Parcel
{
    public:
        Parcel();
        virtual ~Parcel();

        OGRLinearRing create_footprint(OGRLineString linearIntersection, OGRLineString otherSides);
        void to_obj();

        OGRPolygon geom;
        BuildingType type;
        double area;
        double area_price;
        double floorspace;

    protected:
    private:
};

#endif // PARCEL_H
