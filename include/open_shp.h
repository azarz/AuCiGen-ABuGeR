#ifndef OPEN_SHP_INCLUDED
#define OPEN_SHP_INCLUDED

#include "Road.h"
#include "Parcel.h"
#include <vector>

/** @file */
OGRPoint* open_shp_roads(const char* file_path, vector<Road>& liPolygon, const char* layer_name);
/**
*@fn OGRPoint* open_shp_roads(const char* file_path, vector<Road>& liPolygon, const char* layer_name);
*Opens the SHP of roads and creates the road object associated, along with calculating the centroid of the roads
*@param[in] file_path: Road SHP file path
*@param[out] liPolygon: empty vector that will be filled with created roads objects
*@param[in] layer_name: Road SHP file name
*@return an OGRPoint* corresponding to the centroid of the layer
*/

void open_shp_parcels(const char* file_path, vector<Parcel>& liPolygon, OGRPoint* centroid, const char* layer_name);
/**
*@fn void open_shp_parcels(const char* file_path, vector<Parcel>& liPolygon, OGRPoint* centroid, const char* layer_name);
*Opens the SHP of parcels and create the Parcel object associated.
*@param[in] file_path: Parcel SHP file path.
*@param[out] liPolygon:  empty vector that will be filled with created parcels objects.
*@param[in] layer_name: Parcel SHP file name
*/


#endif // OPEN_SHP_INCLUDED
