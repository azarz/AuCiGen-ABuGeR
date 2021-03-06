#ifndef OPEN_SHP_INCLUDED
#define OPEN_SHP_INCLUDED

#include "Road.h"
#include "Parcel.h"
#include <vector>

/** @file */
OGRPoint* open_shp_roads(const char* file_path, vector<Road>& liPolygon, const char* layer_name);
/**
*@fn void OpenShapeFile_roads(char* fill_directory, vector<Road>& liPolygon)
*Opens the SHP of roads and creates the road object associated, along with calculating the centroid of the roads
*@param[in] file_path string: Road SHP file path
*@param[out] vector<Road>& liPolygon: empty vector that will be filled with created roads objects
*@return an OGRPoint* corresponding to the centroid of the layer
*/

void open_shp_parcels(const char* file_path, vector<Parcel>& liPolygon, OGRPoint* centroid, const char* layer_name);
/**
*@fn void OpenShapeFile_parcels(char* fill_directory, vector<Parcel>& liPolygon)
*Opens the SHP of parcels and create the Parcel object associated.
*@param[in] file_path string: Parcel SHP file path.
*@param[out] vector<Road>& liPolygon  empty vector that will be filled with created parcels objects.
*/


#endif // OPEN_SHP_INCLUDED
