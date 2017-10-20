#ifndef OPEN_SHP_INCLUDED
#define OPEN_SHP_INCLUDED

#include <iostream>
#include "ogrsf_frmts.h"
#include "Road.h"
#include "Parcel.h"

using namespace std;


void OpenShapeFile(char* fill_directory, char layer_type)
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
    if (layer_type == 'R')
    {poLayer = poDS->GetLayerByName( "shp_R");}//"Road" );}
    else
    {poLayer = poDS->GetLayerByName( "shp_P" );}



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

            if (layer_type == 'R')
            {
                int iField =1;
                OGRFieldDefn *poFieldDefn = poFDefn->GetFieldDefn( iField );
                if( poFieldDefn->GetType() == OFTString )
                {

                    Road* road = new Road(poPolygon, poFeature->GetFieldAsString(iField));
                    //printf("%s\n", road->type);
                    cout << road->get_type() << endl;
                }
            }
            else
            {Parcel* parcel = new Parcel(poPolygon);}


       }

   }
   OGRFeature::DestroyFeature(poFeature);
}

GDALClose( poDS );
}

/*int main()
{
    OpenShapeFile();
    cout << "Hello world!" << endl;
    return 0;
}*/


#endif // OPEN_SHP_INCLUDED
