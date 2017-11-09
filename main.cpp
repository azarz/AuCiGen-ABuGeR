#include <iostream>
#include <vector>
#include <fstream>
#include "Envelop.h"
#include "open_shp.h"
#include "Road.h"
#include "Parcel.h"
#include "orient.h"
#include "Footprint.h"
#include "catch.h"
#include "poly_to_triangle.h"
#include "triangles_to_obj.h"


using namespace std;


vector<Road> ROADS;
vector<Parcel> PARCELS;


int main()
{
    OGRPoint* centroid;

    const char* file_path ="1_data/paris_test/route_secondaire_buffer.shp";
    const char* layer_name ="route_secondaire_buffer";
    centroid = open_shp_roads(file_path, ROADS, layer_name);
    file_path ="1_data/paris_test/test_paris_seuil.shp";
    layer_name ="test_paris_seuil";
    open_shp_parcels(file_path, PARCELS, centroid, layer_name);

    cout << "Converting the roads to .obj..." << endl;
    vector<string> roadOBJ{"","",""};
    int offset_road(0);

    for(unsigned int i=0U; i<ROADS.size();++i)
    {
        cout << 100*i/ROADS.size() << "%\r";
        vector<string> roadOBJ_temp;
        roadOBJ_temp = ROADS.at(i).to_obj(centroid, offset_road);

        for (int k = 0; k<3; ++k)
        {
            roadOBJ.at(k)+=roadOBJ_temp.at(k);
        }
    }
    cout << endl;

    cout << "Converting the parcels and envelops to .obj..." << endl;
    vector<string> parcelOBJ{"","",""};
    vector<string> envelopOBJ{"","",""};

    int offset_parcel(0);
    int offset_envelop(0);

    for(unsigned int i=0U; i<PARCELS.size();++i)
    {
        cout << 100*i/PARCELS.size() << "%\r";
        Parcel parcel = PARCELS.at(i);

        vector<string> envelopOBJ_temp{"","",""};
        vector<string> parcelOBJ_temp{"","",""};
        OGRLineString* linearIntersection = get_intersection_road(parcel.get_geom(), ROADS);
        OGRLineString* otherSides = get_other_sides(parcel.get_geom(), linearIntersection);

        Footprint footprint = parcel.create_footprint(linearIntersection, otherSides);

        OGRPolygon poPolygon = OGRPolygon();
        OGRLinearRing* a = footprint.get_geom();
        poPolygon.addRing(a);
        if (poPolygon.OGRCurvePolygon::get_Area() > 50)
        {
            Envelop envelop = footprint.create_envelop();
            envelopOBJ_temp = envelop.to_obj(centroid, offset_envelop);
        }

        parcelOBJ_temp = parcel.to_obj(centroid, offset_parcel);

        for (int k = 0; k<3; ++k)
        {
            envelopOBJ.at(k)+=envelopOBJ_temp.at(k);
            parcelOBJ.at(k)+=parcelOBJ_temp.at(k);
        }
        delete linearIntersection;
        delete otherSides;
    }
    cout << endl;

    //To have an output file
    ofstream out_road("2_models/roads.obj");
    out_road << roadOBJ.at(0) << roadOBJ.at(1) << roadOBJ.at(2);
    out_road.close();

    ofstream out_parcel("2_models/parcels.obj");
    out_road << "mtllib parcel.mtl \n";
    out_parcel << parcelOBJ.at(0) << parcelOBJ.at(1);
    out_parcel << "usemtl Parcel\ns 1";
    out_parcel << parcelOBJ.at(2);
    out_parcel.close();

    ofstream out_envelop("2_models/envelops.obj");
    out_envelop << envelopOBJ.at(0) << envelopOBJ.at(1) << envelopOBJ.at(2);
    out_envelop.close();

    return 0;
}
