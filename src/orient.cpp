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

OGRLineString* get_intersection_road(OGRGeometry* linearRing, vector<Road> ROADS)
{
    int maxi = 0;
    bool bo = true;
    OGRLineString* linearIntersection2;

    for (int i=0; i<ROADS.size();++i)
    {
        Road road = ROADS.at(i);

        OGRGeometry* road_ring = (OGRGeometry*)road.get_geom()->getExteriorRing();

        if(road_ring->Touches(linearRing))
        {
            if(maxi<road.get_type())
            {
                maxi=road.get_type();
                OGRGeometry* linearIntersectionGeom = road_ring->Intersection(linearRing);
                linearIntersection2 = (OGRLineString *) linearIntersectionGeom;
            }
            bo =false;
        }
    }
    if(bo)
    {
        OGRMultiLineString* linearRandomMulti = (OGRMultiLineString*) linearRing;
        OGRGeometry* linearRandomMultiGeom = linearRandomMulti->getGeometryRef(0);
        linearIntersection2 = (OGRLineString *) linearRandomMultiGeom;
    }

    return linearIntersection2;
}

OGRLineString* get_other_sides(OGRGeometry* linearRing, OGRGeometry* intersectionLine)
{
    cout << linearRing->Contains(intersectionLine) << endl;
    OGRGeometry* otherSidesGeom = linearRing->Difference(intersectionLine);
    OGRLineString* otherSides = (OGRLineString *) otherSidesGeom;
    return otherSides;
}

/*
TEST_CASE("get_linear_geometry are computed", "[get_linear_geometry]")
{
    REQUIRE(get_linear_geometry(polygon)==linearRing)
}
*/
