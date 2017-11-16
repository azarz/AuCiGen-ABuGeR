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

/*! \file */

BuildingModel crossed_spine(Building bu, double roofAngle);
/**
*@fn BuildingModel crossed_spine(Building bu, double roofAngle)
*Manage a crossed roof skeleton.
*@param[in] bu : building whose roof is to create.
*@param[in] roofAngle : roof angle (Rad).
*@return building model with roof.
*/

BuildingModel linear_spine(Building bu, double roofAngle);
/**
*@fn BuildingModel linear_spine(Building bu, double roofAngle)
*Manage mono linear roof skeleton.
*@param[in] bu : building whose roof is to create.
*@param[in] roofAngle : roof angle (Rad).
*@return building model with roof.
*/

BuildingModel linear_cross_spine(Building bu, double roofAngle);
/**
*@fn BuildingModel linear_cross_spine(Building bu, double roofAngle)
*Manage linear roof skeleton linked to the four corners roof .
*@param[in] bu : building whose roof is to create.
*@param[in] roofAngle : roof angle (Rad).
*@return building model with roof.
*/

BuildingModel flat_roof(Building bu);
/**
*@fn BuildingModel flat_roof(Building bu)
*Manage mono linear roof skeleton.
*@param[in] bu : building whose roof is to create.
*@return building model with roof.
*/

#endif // SS_H_INCLUDED
