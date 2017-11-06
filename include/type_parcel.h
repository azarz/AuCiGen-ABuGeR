#ifndef TYPE_PARCEL_H_INCLUDED
#define TYPE_PARCEL_H_INCLUDED

#include "BuildingType.h"
#include "ogrsf_frmts.h"
/*! \file */

BuildingType* type_parcel(OGRPoint* centroid);
/**
*@fn BuildingType* type_parcel()
*Determines the type of the parcel.
*@return a BuildingType.
*/
#endif // TYPE_PARCEL_H_INCLUDED
