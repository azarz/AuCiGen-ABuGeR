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
    for (unsigned int i=0U; i<ROADS.size();++i)
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
