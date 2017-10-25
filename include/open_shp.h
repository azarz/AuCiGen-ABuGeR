#ifndef OPEN_SHP_INCLUDED
#define OPEN_SHP_INCLUDED

#include "Road.h"
#include "Parcel.h"
#include <vector>

/** @file */
/**
*@fn void OpenShapeFile_roads(char* fill_directory, vector<Road>& liPolygon)
*open the SHP of roads and create the road object associated
*@param[in] fill_directory char* : Road SHP fil directory
*@param[out] vector<Road>& liPolygon : empty vector that will be filled with created roads objects
*/
void OpenShapeFile_roads(char* fill_directory, vector<Road>& liPolygon);

/**
*@fn void OpenShapeFile_parcels(char* fill_directory, vector<Parcel>& liPolygon)
*open the SHP of parcels and create the Parcel object associated
*@param[in] fill_directory char* : Parcel SHP fil directory
*@param[out] vector<Road>& liPolygon : empty vector that will be filled with created parcels objects
*/

void OpenShapeFile_parcels(char* fill_directory, vector<Parcel>& liPolygon);

#endif // OPEN_SHP_INCLUDED
