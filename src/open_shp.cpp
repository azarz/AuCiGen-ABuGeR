#include "open_shp.h"
#include <iostream>
#include "ogrsf_frmts.h"
#include "Road.h"
#include "Parcel.h"
#include <vector>
#include "catch.h"
using namespace std;

vector<double> OpenShapeFile_roads(char* fill_directory, vector<Road>& liPolygon)
{
    vector<double> centroid_xy;
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

    OGRwkbGeometryType LayerGeometryType = poLayer->GetGeomType();
    int NumberOfFeatures = poLayer ->GetFeatureCount(true);
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
           //printf("\nelement : %d\n", i);
           poFeature = poLayer ->GetNextFeature();
           OGRGeometry* poGeometry;
           poGeometry = poFeature->GetGeometryRef();
           if ( poGeometry != NULL && wkbFlatten ( poGeometry->getGeometryType() ) == wkbPolygon )
           {
                OGRPolygon* poPolygon = (OGRPolygon*)poGeometry;
                road_collection->addGeometry(poPolygon);
                /*OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();
                int iField =1;
                OGRFieldDefn* poFieldDefn = poFDefn->GetFieldDefn( iField );
                if( poFieldDefn->GetType() == OFTInteger )
                {*/
                    Road road = Road(poPolygon,1);// poFeature->GetFieldAsInteger(iField));
                    //printf("%s\n", road->type);
                    liPolygon.push_back(road);
                    //cout << road.get_type() << endl;
                //}
           }

       }
       road_collection->Centroid(centroid);
       centroid_xy.push_back(centroid->getX());
       centroid_xy.push_back(centroid->getY());
       OGRFeature::DestroyFeature(poFeature);
    }

    GDALClose( poDS );
    return centroid_xy;
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

