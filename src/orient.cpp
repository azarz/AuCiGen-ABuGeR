#include <iostream>
#include "ogrsf_frmts.h"
#include "Road.h"
#include "catch.h"
#include <vector>


OGRLineString* get_intersection_road(OGRGeometry* parcelGeom, vector<Road> ROADS)
{
    // Integer used to determine
    int mini = 3;
    // This boolean is used to determine an orientation when no roads are found around the parcel
    bool no_road = true;
    // This is the result of the function, the linear intersection between the parcel and the main road
    OGRLineString* linearIntersection = new OGRLineString();
    // Going through all the loaded roads (except the last one which cases a Segmentation fault for unknown reasons
    for (int i=0; i<ROADS.size();++i)
    {
        // Getting the ith road int the vector
        Road road = ROADS.at(i);

        // If the road intersects the parcel
        if(road.get_geom()->Intersects(parcelGeom))
        {
            // If the current road type is lesser than mini (which means its more important)
            if(road.get_type()<mini)
            {
                // Updating mini
                mini=road.get_type();

                // Getting the intersection and converting it to a LineString
                OGRGeometry* linearIntersectionGeom = road.get_geom()->Intersection(parcelGeom);
                linearIntersection = (OGRLineString*)linearIntersectionGeom;
            }
            // There is a road
            no_road = false;
        }
    }

    // If no road was found
    if(no_road)
    {
        // Getting a random (the 1st in the index) line in the polygon boundary as the intersection
        OGRPolygon* parcelGeom2 = (OGRPolygon*)parcelGeom;
        OGRLineString* linearRing = parcelGeom2->getExteriorRing();
        OGRPoint* point1 = new OGRPoint();
        OGRPoint* point2 = new OGRPoint();
        linearRing->getPoint(0,point1);
        linearRing->getPoint(1,point2);
        linearIntersection->addPoint(point1);
        linearIntersection->addPoint(point2);
        delete point1;
        delete point2;
    }
    return linearIntersection;
}



OGRLineString* get_other_sides(OGRGeometry* parcelGeom, OGRGeometry* intersectionLine)
{
    OGRGeometry* parcel_boundary = parcelGeom->Boundary();
    // Getting the difference between the intersection with the road and the full parcel contour to
    // determine the other sides
    OGRGeometry* otherSidesGeom = parcel_boundary->Difference(intersectionLine);
    OGRLineString* otherSides = (OGRLineString *) otherSidesGeom;
    return otherSides;
}


/*
TEST_CASE("get_intersection_road computed", "[get_intersection_road]")
{
    char* wkt ="POLYGON ((55.4683455250644 -21.3282187046573,55.4683460303297 -21.3282180820721,55.4685788303297 -21.3279358820721,55.4685905503442 -21.3279255206688,55.46860489859 -21.3279192880722,55.468620470561 -21.3279177943725,55.468635741964 -21.3279211857833,55.4686492179279 -21.3279291303297,55.4686595793312 -21.3279408503442,55.4686658119277 -21.32795519859,55.4686673056275 -21.327970770561,55.4686639142167 -21.327986041964,55.4686559696703 -21.3279995179279,55.4684234247991 -21.3282814086609,55.4681532749356 -21.3286197953427,55.4681417225811 -21.3286303433531,55.4681274761246 -21.3286368052333,55.4681119301085 -21.3286385484493,55.4680966062852 -21.3286354023632,55.4680830046573 -21.3286276749356,55.4680724566469 -21.3286161225811,55.4680659947667 -21.3286018761245,55.4680642515507 -21.3285863301085,55.4680673976368 -21.3285710062852,55.4680751250644 -21.3285574046573,55.4683455250644 -21.3282187046573))";
    OGRPolygon* poGeom = new OGRPolygon();
    poGeom->OGRPolygon::importFromWkt(&wkt);

    Road r(poGeom,1);
    vector<Road> ROADS;
    ROADS.push_back(r);
    ROADS.push_back(r);

    OGRLineString* result;

    result = get_intersection_road(poGeom, ROADS);

    REQUIRE(result->getGeometryName()=="LINESTRING");
}

TEST_CASE("get_other_sides computed", "[get_other_sides]")
{
    char* wkt ="POLYGON ((55.4683455250644 -21.3282187046573,55.4683460303297 -21.3282180820721,55.4685788303297 -21.3279358820721,55.4685905503442 -21.3279255206688,55.46860489859 -21.3279192880722,55.468620470561 -21.3279177943725,55.468635741964 -21.3279211857833,55.4686492179279 -21.3279291303297,55.4686595793312 -21.3279408503442,55.4686658119277 -21.32795519859,55.4686673056275 -21.327970770561,55.4686639142167 -21.327986041964,55.4686559696703 -21.3279995179279,55.4684234247991 -21.3282814086609,55.4681532749356 -21.3286197953427,55.4681417225811 -21.3286303433531,55.4681274761246 -21.3286368052333,55.4681119301085 -21.3286385484493,55.4680966062852 -21.3286354023632,55.4680830046573 -21.3286276749356,55.4680724566469 -21.3286161225811,55.4680659947667 -21.3286018761245,55.4680642515507 -21.3285863301085,55.4680673976368 -21.3285710062852,55.4680751250644 -21.3285574046573,55.4683455250644 -21.3282187046573))";
    GRGeometry* poGeom = new OGRGeometry();
    poGeom->OGRPolygon::importFromWkt(&wkt);

    char* wkt2 ="LINESTRING ((55.4683455250644 -21.3282187046573,55.4683460303297 -21.3282180820721)

    GRGeometry* intersection = new OGRGeometry();
    intersection->OGRLineString::importFromWkt(&wkt2);

    OGRLineString* result;

    result = get_other_sides(poGeom, intersection)

    REQUIRE(result->getDimension()==2);
}
*/
