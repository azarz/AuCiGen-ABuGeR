#include "open_shp.h"
#include <iostream>
#include "ogrsf_frmts.h"
#include "Road.h"
#include "Parcel.h"
#include <vector>
using namespace std;


OGRPoint* open_shp_roads(const char* file_path, vector<Road>& liPolygon, const char* layer_name)
{

    OGRErr error;
    GDALAllRegister();
    GDALDataset       *poDS;
    poDS = (GDALDataset*) GDALOpenEx( file_path, GDAL_OF_VECTOR, NULL, NULL, NULL );
    if( poDS == NULL )
    {
        printf( "Open failed.\n" );
        exit( 1 );
    }
    OGRLayer  *poLayer;
    poLayer = poDS->GetLayerByName(layer_name);

    OGRwkbGeometryType LayerGeometryType = poLayer->GetGeomType();
    int NumberOfFeatures = poLayer->GetFeatureCount(true);
    poLayer ->ResetReading();

    OGRGeometryCollection* road_collection = new OGRGeometryCollection();
    OGRPoint* centroid = new OGRPoint();

    //Polygon Shapefile
    if (wkbFlatten(LayerGeometryType) == wkbPolygon )
    {
       OGRFeature* poFeature;
       OGRPoint ptTemp;
       for (int i = 0; i < NumberOfFeatures; i++)
       {
           poFeature = poLayer->GetNextFeature();
           OGRGeometry* poGeometry;
           poGeometry = poFeature->GetGeometryRef();
           if ( poGeometry != NULL && wkbFlatten ( poGeometry->getGeometryType() ) == wkbPolygon )
           {
                OGRPolygon* poPolygon = (OGRPolygon*)poGeometry;
                poPolygon->closeRings();
                road_collection->addGeometry(poPolygon);
                /*OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();
                int iField =1;
                OGRFieldDefn* poFieldDefn = poFDefn->GetFieldDefn( iField );
                if( poFieldDefn->GetType() == OFTInteger )
                {*/
                    Road road = Road(poPolygon,1);// poFeature->GetFieldAsInteger(iField));
                    liPolygon.push_back(road);
                //}
           }
       }
       road_collection->Centroid(centroid);
    }
    GDALClose( poDS );
    return centroid;
}


void open_shp_parcels(const char* file_path, vector<Parcel>& liPolygon, OGRPoint* centroid, const char* layer_name)
{

    OGRErr error;
    GDALAllRegister();
    GDALDataset       *poDS;
    poDS = (GDALDataset*) GDALOpenEx( file_path, GDAL_OF_VECTOR, NULL, NULL, NULL );
    if( poDS == NULL )
    {
        printf( "Open failed.\n" );
        exit( 1 );
    }
    OGRLayer  *poLayer;
    poLayer = poDS->GetLayerByName(layer_name);


    OGRwkbGeometryType LayerGeometryType = poLayer ->GetGeomType();
    int NumberOfFeatures = poLayer ->GetFeatureCount(true);
    poLayer ->ResetReading();
    //Polygon Shapefile
    if ( wkbFlatten ( LayerGeometryType ) == wkbPolygon )
    {
       OGRFeature *poFeature;
       for ( int i = 0; i < NumberOfFeatures; i++ )
       {
           poFeature = poLayer->GetNextFeature();
           OGRGeometry* poGeometry;
           poGeometry = poFeature->GetGeometryRef();
           if ( poGeometry != NULL && wkbFlatten ( poGeometry ->getGeometryType() ) == wkbPolygon )
           {
                OGRPolygon* poPolygon = (OGRPolygon*)poGeometry;
                poPolygon->OGRPolygon::closeRings ();
                Parcel parcel = Parcel(poPolygon, centroid);
                liPolygon.push_back(parcel);
           }
       }
    }
    GDALClose( poDS );
}
