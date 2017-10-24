#ifndef OPEN_SHP_INCLUDED
#define OPEN_SHP_INCLUDED

#include <iostream>
#include "ogrsf_frmts.h"
#include "Road.h"
#include "Parcel.h"
#include <vector>

using namespace std;


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
           //printf("\nelement : %d\n", i);
           poFeature = poLayer ->GetNextFeature();
           OGRGeometry *poGeometry;
           poGeometry = poFeature ->GetGeometryRef();
           if ( poGeometry != NULL && wkbFlatten ( poGeometry ->getGeometryType() ) == wkbPolygon )
           {
                OGRPolygon* poPolygon = (OGRPolygon*)poGeometry;
                //OGRFeatureDefn* poFDefn = poLayer->GetLayerDefn();

                Parcel parcel = Parcel(poPolygon);
                liPolygon.push_back(parcel);
                //cout << liPolygon.size() << endl;
           }

       }
       //OGRFeature::DestroyFeature(poFeature);
    }
    //cout << liPolygon.size() << endl;
    GDALClose( poDS );
}



#endif // OPEN_SHP_INCLUDED
