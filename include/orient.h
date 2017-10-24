#ifndef ORIENT_H_INCLUDED
#define ORIENT_H_INCLUDED

#include <vector>
#include "ogrsf_frmts.h"
#include "Road.h"

/**
* This function allows us to extract the linear geometry from a OGRPolygon.
* @param[in] polygon It's the polygon of the parcel.
* @return The linear geometry of the polygon.
*/
OGRGeometry* get_linear_geometry(OGRPolygon* polygon);

/**
* This function allows us to get the intersection line between a linear ring and the road polygons.
* @param[in] parcelGeom The parcel geometry
* @param[in] road Vector containing all the roads
* @return The side in front of the largest road.
*/
OGRLineString* get_intersection_road(OGRGeometry* parcelGeom, vector<Road> road);

/**
* Get the other sides of the parcel contour
* @param[in] parcelGeom Geometry of the parcel
* @param[in] intersectionLine It's the side in front of the largest road.
* @return The other sides of the parcel (without the side in front of the largest road).
*/
OGRLineString* get_other_sides(OGRGeometry* parcelGeom, OGRGeometry* intersectionLine);

#endif // ORIENT_H_INCLUDED
