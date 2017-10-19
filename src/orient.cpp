#include <iostream>
#include "ogrsf_frmts.h"

OGRGeometry* get_linear_geometry(OGRPolygon polygon)
{
    OGRGeometry* linearRing = polygon.getLinearGeometry();
    //OGRLinearRing* linearRing2 = (OGRLinearRing *) linearRing;
    return linearRing;
}

OGRLineString* get_intersection_road(OGRGeometry* linearRing, OGRPolygon* road)
{
    //don't forget to test if there is an intersection (choice a side if not)
//    OGRGeometry* linearRingGeom = (OGRGeometry*)linearRing;
    OGRGeometry* linearIntersection = linearRing->Intersection(road);
    OGRLineString* linearIntersection2 = (OGRLineString *) linearIntersection;
    return linearIntersection2;
}

OGRLineString* get_other_sides(OGRGeometry* linearRing, OGRGeometry* intersectionLine)
{
    OGRGeometry* otherSidesGeom = linearRing->Difference(intersectionLine);
    OGRLineString* otherSides = (OGRLineString *) otherSidesGeom;
    return otherSides;
}
