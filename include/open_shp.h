#ifndef OPEN_SHP_INCLUDED
#define OPEN_SHP_INCLUDED

#include <iostream>
#include "ogrsf_frmts.h"
#include "Road.h"
#include "Parcel.h"
#include <vector>

using namespace std;


vector<Road> OpenShapeFile_roads(char* fill_directory)
{
    OGRErr error;
    GDALAllRegister();
    vector<Road> liPolygon;
    GDALDataset       *poDS;
    poDS = (GDALDataset*) GDALOpenEx( fill_directory, GDAL_OF_VECTOR, NULL, NULL, NULL );
    if( poDS == NULL )
    {
        printf( "Open failed.\n" );
        exit( 1 );
    }
    OGRLayer  *poLayer;
    poLayer = poDS->GetLayerByName( "shp_R");

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
       printf("\nelement : %d\n", i);
       poFeature = poLayer ->GetNextFeature();
       OGRGeometry *poGeometry;
       poGeometry = poFeature ->GetGeometryRef();
       if ( poGeometry != NULL && wkbFlatten ( poGeometry ->getGeometryType() ) == wkbPolygon )
       {
           OGRPolygon *poPolygon = ( OGRPolygon * )poGeometry;
           OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();
                int iField =1;
                OGRFieldDefn *poFieldDefn = poFDefn->GetFieldDefn( iField );
                if( poFieldDefn->GetType() == OFTString )
                {
                    Road* road = new Road(poPolygon, poFeature->GetFieldAsInteger(iField));
                    //printf("%s\n", road->type);
                    liPolygon.push_back(*road);
                    cout << road->get_type() << endl;
                }
       }

   }
   OGRFeature::DestroyFeature(poFeature);
}

GDALClose( poDS );
return liPolygon;
}

vector<Parcel> OpenShapeFile_parcels(char* fill_directory)
{
    OGRErr error;
    GDALAllRegister();
    vector<Parcel> liPolygon;
    GDALDataset       *poDS;
    poDS = (GDALDataset*) GDALOpenEx( fill_directory, GDAL_OF_VECTOR, NULL, NULL, NULL );
    if( poDS == NULL )
    {
        printf( "Open failed.\n" );
        exit( 1 );
    }
    OGRLayer  *poLayer;
    poLayer = poDS->GetLayerByName( "shp_P" );



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
       printf("\nelement : %d\n", i);
       poFeature = poLayer ->GetNextFeature();
       OGRGeometry *poGeometry;
       poGeometry = poFeature ->GetGeometryRef();
       if ( poGeometry != NULL && wkbFlatten ( poGeometry ->getGeometryType() ) == wkbPolygon )
       {
           OGRPolygon *poPolygon = ( OGRPolygon * )poGeometry;
           OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();

            Parcel* parcel = new Parcel(poPolygon);
            liPolygon.push_back(*parcel);
       }

   }
   //OGRFeature::DestroyFeature(poFeature);
}

GDALClose( poDS );
return liPolygon;
}



#endif // OPEN_SHP_INCLUDED
