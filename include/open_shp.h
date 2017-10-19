#ifndef OPEN_SHP_INCLUDED
#define OPEN_SHP_INCLUDED

#include <iostream>
#include "ogrsf_frmts.h"

using namespace std;


void OpenShapeFile(string fill_directory, char layer_type)
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
    if (layer_type == "R")
    {poLayer = poDS->GetLayerByName( "Road" );}
    else
    {poLayer = poDS->GetLayerByName( "Parcel" );}



OGRwkbGeometryType LayerGeometryType = poLayer ->GetGeomType();
int NumberOfFeatures = poLayer ->GetFeatureCount(true);
poLayer ->ResetReading();

//Polygon Shapefile
if ( wkbFlatten ( LayerGeometryType ) == wkbPolygon )
{
   OGRFeature *poFeature;
   PolygonFeature Polygon;
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
           int iField =0;
            OGRFieldDefn *poFieldDefn = poFDefn->GetFieldDefn( iField );
            if (layer_type == "R")
            {
                if( poFieldDefn->GetType() == OFTString )
                {
                    Road road = new Road(poPolygon, poFeature->GetFieldAsString(iField));
                }
            }
            else
            {Parcel parcel = new Parcel(poPolygon);}


       }

   }
   OGRFeature::DestroyFeature(poFeature);
}

GDALClose( poDS );
}

int main()
{
    OpenShapeFile();
    cout << "Hello world!" << endl;
    return 0;
}


#endif // OPEN_SHP_INCLUDED

/*
int main()
{
    GDALAllRegister();

    GDALDataset       *poDS;
    //poDS = (GDALDataset*) GDALOpenEx( "data/geoflar-departementsLAM.shp", GDAL_OF_VECTOR, NULL, NULL, NULL );
    poDS = (GDALDataset*) GDALOpenEx( "data/test_shp/test_shpLAM.shp", GDAL_OF_VECTOR, NULL, NULL, NULL );
    if( poDS == NULL )
    {
        printf( "Open failed.\n" );
        exit( 1 );
    }
    OGRLayer  *poLayer;
    //poLayer = poDS->GetLayerByName( "geoflar-departementsLAM" );
    poLayer = poDS->GetLayerByName( "test_shpLAM" );
    OGRFeature *poFeature;
    poLayer->ResetReading();
    while( (poFeature = poLayer->GetNextFeature()) != NULL )
    {
        OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();
        int iField;
        //iField =0;
        for( iField = 0; iField < poFDefn->GetFieldCount(); iField++ )
        {
            //printf( "place : %d", iField );
            OGRFieldDefn *poFieldDefn = poFDefn->GetFieldDefn( iField );
            if( poFieldDefn->GetType() == OFTInteger )
                printf( "%d,", poFeature->GetFieldAsInteger( iField ) );
            else if( poFieldDefn->GetType() == OFTInteger64 )
                printf( CPL_FRMT_GIB ",", poFeature->GetFieldAsInteger64( iField ) );
            else if( poFieldDefn->GetType() == OFTReal )
                printf( "%.3f,", poFeature->GetFieldAsDouble(iField) );
            else if( poFieldDefn->GetType() == OFTString )
                printf( "%s,", poFeature->GetFieldAsString(iField) );
            else
                printf( "%s,", poFeature->GetFieldAsString(iField) );
        }
*/
