#ifndef SS_H_INCLUDED
#define SS_H_INCLUDED

#include "ogrsf_frmts.h"
#include <ogr_geometry.h>
#include <vector>
#include <string>
#include "Point.h"
#include "Footprint.h"
#include "Envelop.h"
#include "Building.h"
#include "math.h"
/*#include <boost/shared_ptr.hpp>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Straight_skeleton_2.h>*/

/*! \file */
OGRPolygon Straight_Skeleton(BuildingModel bu);
/**
*@fn
*Manage a straight skeleton for the roof.
*@param[in] .
*@return .
*/


BuildingModel crossed_spine(Building b, double roofAngle);
/**
*@fn
*Manage a crossed roof skeleton.
*@param[in] .
*@return .
*/

BuildingModel linear_spine(Building b, double roofAngle);
/**
*@fn
*Manage mono linear roof skeleton.
*@param[in] .
*@return .
*/
BuildingModel linear_cross_spine(Building b, double roofAngle);
/**
*@fn
*Manage linear roof skeleton linked to the four corners roof .
*@param[in] .
*@return .
*/

BuildingModel flat_roof(Building bu);
/**
*@fn BuildingModel flat_roof(Building bu)
*Manage mono linear roof skeleton.
*@param[in] bu : building whose roof is to create.
*@return building model with roof.
*/
#endif // SS_H_INCLUDED
