#ifndef ORIENT_H_INCLUDED
#define ORIENT_H_INCLUDED

#include <vector>
#include "ogrsf_frmts.h"
#include "Road.h"

/*! \file */
OGRLineString* get_intersection_road(OGRGeometry* parcelGeom, vector<Road> road);
/**
*@fn OGRLineString* get_intersection_road(OGRGeometry* parcelGeom, vector<Road> road)
*This function allows us to get the intersection line between a linear ring and the road polygons.
*@param[in] parcelGeom : It's The parcel geometry.
*@param[in] road Vector : It's containing all the roads.
*@return The side in front of the largest road.
*/

OGRLineString* get_other_sides(OGRGeometry* parcelGeom, OGRGeometry* intersectionLine);
/**
*@fn OGRLineString* get_intersection_road(OGRGeometry* parcelGeom, vector<Road> road)
*Get the other sides of the parcel bounds.
*@param[in] parcelGeom : It' Geometry of the parcel.
*@param[in] intersectionLine : It's the side in front of the largest road.
*@return The other sides of the parcel (without the side in front of the largest road).
*/

#endif // ORIENT_H_INCLUDED
