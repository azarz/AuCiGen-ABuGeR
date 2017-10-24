#include <iostream>
#include "ogrsf_frmts.h"
#include "Road.h"
#include "catch.h"
#include <vector>
#include "Road.h"
#include <string>


OGRGeometry* get_linear_geometry(OGRPolygon* polygon)
{
    OGRGeometry* linearRing = polygon->getLinearGeometry();
    //OGRLinearRing* linearRing2 = (OGRLinearRing *) linearRing;
    return linearRing;
}

OGRLineString* get_intersection_road(OGRGeometry* parcelGeom, vector<Road> ROADS)
{
    int mini = 3;
    bool bo = true;
    OGRLineString* linearIntersection2;

    for (int i=0; i<ROADS.size()-1;++i)
    {
        Road road = ROADS.at(i);

        //OGRGeometry* road_bound = road.get_geom()->getBoundary();
        //OGRGeometry* parcel_bound = parcelGeom->getBoundary();

        if(road.get_geom()->Intersects(parcelGeom))
        {
            if(mini>road.get_type())
            {
                mini=road.get_type();

                OGRGeometry* linearIntersectionGeom = road.get_geom()->Intersection(parcelGeom);
                linearIntersection2 = (OGRLineString*)linearIntersectionGeom;
            }
            bo =false;
        }
    }
    if(bo)
    {
        OGRGeometry* linearRing = ((OGRPolygon*)parcelGeom)->getExteriorRing();
        OGRMultiLineString* linearRandomMulti = (OGRMultiLineString*) linearRing;
        OGRGeometry* linearRandomMultiGeom = linearRandomMulti->getGeometryRef(0);
        linearIntersection2 = (OGRLineString *) linearRandomMultiGeom;
    }

    return linearIntersection2;
}

OGRLineString* get_other_sides(OGRGeometry* parcelGeom, OGRGeometry* intersectionLine)
{
    OGRGeometry* parcel_boundary = parcelGeom->getBoundary();
    OGRGeometry* otherSidesGeom = parcel_boundary->Difference(intersectionLine);
    OGRLineString* otherSides = (OGRLineString *) otherSidesGeom;
    return otherSides;
}

/*
TEST_CASE("get_linear_geometry are computed", "[get_linear_geometry]")
{
    REQUIRE(get_linear_geometry(polygon)==linearRing)
}
*/
