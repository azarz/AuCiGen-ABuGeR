#include <iostream>
#include "ogrsf_frmts.h"

OGRLinearRing get_linear_geometry(OGRPolygon polygon)
{
    OGRLinearRing linearRing = polygon.getLinearGeometry();
    return linearRing;
}

OGRLineString get_intersection_road(OGRLinearRing linearRing, OGRPolygon road)
{
    //don't forget to test if there is an intersection (choice a side if not)
    OGRLineString linearIntersection = linearRing.Intersection(road);
    return linearIntersection;
}

OGRLineString get_other_sides(OGRLinearRing linearRing, OGRLineString intersectionLine)
{
    OGRLineString otherSides = linearRing.Difference(intersectionLine);
    return otherSides;
}
