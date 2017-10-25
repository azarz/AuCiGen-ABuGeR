#ifndef OPEN_SHP_INCLUDED
#define OPEN_SHP_INCLUDED

#include <iostream>
#include "ogrsf_frmts.h"
#include "Road.h"
#include "Parcel.h"
#include <vector>
#include "catch.h"
using namespace std;

/** @file */
/**
*@fn void OpenShapeFile_roads(char* fill_directory, vector<Road>& liPolygon)
*open the SHP of roads and create the road object associated
*@param[in] fill_directory char* : Road SHP fil directory
*@param[out] vector<Road>& liPolygon : empty vector that will be filled with created roads objects
*/
void OpenShapeFile_roads(char* fill_directory, vector<Road>& liPolygon)
{
    OGRErr error;
    GDALAllRegister();
    GDALDataset       *poDS;
    poDS = (GDALDataset*) GDALOpenEx( fill_directory, GDAL_OF_VECTOR, NULL, NULL, NULL );
    if( poDS == NULL )
    {
        printf( "Open failed.\n" );
        exit( 1 );
    }
    OGRLayer  *poLayer;
    poLayer = poDS->GetLayerByName( "road_test");

    OGRwkbGeometryType LayerGeometryType = poLayer ->GetGeomType();
    int NumberOfFeatures = poLayer ->GetFeatureCount(true);
    poLayer ->ResetReading();

    //Polygon Shapefile
    if ( wkbFlatten ( LayerGeometryType ) == wkbPolygon )
    {
       OGRFeature *poFeature;
       OGRPoint ptTemp;
       for ( int i = 0; i < NumberOfFeatures; i++ )
       {
           //printf("\nelement : %d\n", i);
           poFeature = poLayer ->GetNextFeature();
           OGRGeometry *poGeometry;
           poGeometry = poFeature ->GetGeometryRef();
           if ( poGeometry != NULL && wkbFlatten ( poGeometry->getGeometryType() ) == wkbPolygon )
           {
                OGRPolygon *poPolygon = ( OGRPolygon * )poGeometry;
                /*OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();
                int iField =1;
                OGRFieldDefn *poFieldDefn = poFDefn->GetFieldDefn( iField );
                if( poFieldDefn->GetType() == OFTInteger )
                {*/
                    Road road = Road(poPolygon,1);// poFeature->GetFieldAsInteger(iField));
                    //printf("%s\n", road->type);
                    liPolygon.push_back(road);
                    //cout << road.get_type() << endl;
                //}
           }

       }
       OGRFeature::DestroyFeature(poFeature);
    }

    GDALClose( poDS );
}



/**
*@fn void OpenShapeFile_parcels(char* fill_directory, vector<Parcel>& liPolygon)
*open the SHP of parcels and create the Parcel object associated
*@param[in] fill_directory char* : Parcel SHP fil directory
*@param[out] vector<Road>& liPolygon : empty vector that will be filled with created parcels objects
*/

void OpenShapeFile_parcels(char* fill_directory, vector<Parcel>& liPolygon)

{
    OGRErr error;
    GDALAllRegister();
    GDALDataset       *poDS;
    poDS = (GDALDataset*) GDALOpenEx( fill_directory, GDAL_OF_VECTOR, NULL, NULL, NULL );
    if( poDS == NULL )
    {
        printf( "Open failed.\n" );
        exit( 1 );
    }
    OGRLayer  *poLayer;
    poLayer = poDS->GetLayerByName( "test_parcel" );


    OGRwkbGeometryType LayerGeometryType = poLayer ->GetGeomType();
    int NumberOfFeatures = poLayer ->GetFeatureCount(true);
    poLayer ->ResetReading();

    //Polygon Shapefile
    if ( wkbFlatten ( LayerGeometryType ) == wkbPolygon )
    {
       OGRFeature *poFeature;
       OGRPoint ptTemp;
       for ( int i = 0; i < NumberOfFeatures; i++ )
       {
           poFeature = poLayer->GetNextFeature();
           OGRGeometry* poGeometry;
           poGeometry = poFeature->GetGeometryRef();
           if ( poGeometry != NULL && wkbFlatten ( poGeometry ->getGeometryType() ) == wkbPolygon )
           {
                OGRPolygon* poPolygon = (OGRPolygon*)poGeometry;

                Parcel parcel = Parcel(poPolygon);
                liPolygon.push_back(parcel);
           }

       }
       OGRFeature::DestroyFeature(poFeature);
    }
    GDALClose( poDS );
}





/*
TEST_CASE("OpenShapeFile_roads are computed","[OpenShapeFile_roads]")
{
    vector<Road> ROADS;
    char* fill_directory ="1_data/test/road_test.shp";
    OpenShapeFile_roads(fill_directory, ROADS);
    REQUIRE(ROADS.size()==1193);
    REQUIRE(ROADS.at(0).get_type()==1);
    REQUIRE(ROADS.at(0).get_geom()->getExteriorRing()->OGRSimpleCurve::getNumPoints()==55);
    REQUIRE(ROADS.at(0).get_geom()->getGeometryType()==3);
}

TEST_CASE("OpenShapeFile_parcels are computed","[OpenShapeFile_parcels]")
{
    vector<Parcel> PARCELS;
    char* fill_directory ="1_data/test/test_parcel.shp";
    OpenShapeFile_parcels(fill_directory, PARCELS);
    REQUIRE(PARCELS.size()==594);
    REQUIRE(PARCELS.at(0).get_area()==PARCELS.at(0).get_geom()->OGRCurvePolygon::get_Area());
    REQUIRE(PARCELS.at(0).get_geom()->getExteriorRing()->OGRSimpleCurve::getNumPoints()==4);
    REQUIRE(PARCELS.at(0).get_geom()->getGeometryType()==3);
}*/


#endif // OPEN_SHP_INCLUDED
