#include "ABuGeR.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "Envelop.h"
#include "open_shp.h"
#include "Road.h"
#include "Parcel.h"
#include "orient.h"
#include "Footprint.h"
#include "poly_to_triangle.h"
#include "triangles_to_obj.h"
#include "Building.h"
#include "math.h"

using namespace std;

int ABuGeR(const char* file_path_Road, const char* layer_name_Road, const char* file_path_Parcel, const char* layer_name_Parcel)
{
    vector<Road> ROADS;
    vector<Parcel> PARCELS;
    OGRPoint* centroid;
    centroid = open_shp_roads(file_path_Road, ROADS, layer_name_Road);
    vector<double > angle_roof{0, M_PI/9,M_PI/6, M_PI/4};

    open_shp_parcels(file_path_Parcel, PARCELS, centroid, layer_name_Parcel);

    cout << "Converting the roads to .obj..." << endl;
    vector<string> roadOBJ{"","","",""};
    int offset_road(0);
    /*for(unsigned int i=0U; i<ROADS.size();++i)
    {
        cout << 100*i/ROADS.size() << "%\r";
        vector<string> roadOBJ_temp;
        roadOBJ_temp = ROADS.at(i).to_obj(centroid, offset_road);

        for (int k = 0; k<4; ++k)
        {
            roadOBJ.at(k)+=roadOBJ_temp.at(k);
        }
    }*/
    cout << "100%\r"<<endl;

    cout << "Converting the parcels and envelops to .obj..." << endl;
    vector<string> parcelOBJ{"","","",""};
    vector<string> envelopOBJ{"","","",""};
    vector<string> buildingOBJ{"","","",""};

    int offset_parcel(0);
    int offset_envelop(0);
    int offset_building(0);

    for(unsigned int i=0; i<500;i++)

    {
        Parcel parcel = PARCELS.at(i);
        cout << 100*i/PARCELS.size()<< "%\r";

        vector<string> envelopOBJ_temp{"","","",""};
        vector<string> buildingOBJ_temp{"","","",""};
        vector<string> parcelOBJ_temp{"","","",""};

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
            Building bui= Building(&envelop);
            bui.creat_roof(angle_roof.at( rand() %4));
            buildingOBJ_temp = bui.to_obj(centroid, offset_building);
        }

        parcelOBJ_temp = parcel.to_obj(centroid, offset_parcel);

        for (int k = 0; k<4; ++k)
        {
            envelopOBJ.at(k)+=envelopOBJ_temp.at(k);
            buildingOBJ.at(k)+=buildingOBJ_temp.at(k);
            parcelOBJ.at(k)+=parcelOBJ_temp.at(k);
        }
        delete linearIntersection;
        delete otherSides;
    }
    cout <<"100%\r"<<endl;

    //To have an output file
    ofstream out_road("2_models/roads.obj");
    out_road << "mtllib road.mtl\n";
    out_road << roadOBJ.at(0) << roadOBJ.at(1) << envelopOBJ.at(2) << roadOBJ.at(3);;
    out_road.close();

    ofstream out_parcel("2_models/parcels.obj");
    out_parcel << "mtllib parcel.mtl\n";
    out_parcel << parcelOBJ.at(0) << parcelOBJ.at(1) << parcelOBJ.at(2) << parcelOBJ.at(3);
    out_parcel.close();

    ofstream out_envelop("2_models/envelops.obj");
    out_envelop << "mtllib envelop.mtl\n";
    out_envelop << envelopOBJ.at(0) << envelopOBJ.at(1) << envelopOBJ.at(2) << envelopOBJ.at(3);
    out_envelop.close();

    ofstream out_building("2_models/building.obj");
    out_building << "mtllib building.mtl\n";
    out_building << buildingOBJ.at(0) << buildingOBJ.at(1) << buildingOBJ.at(2) << buildingOBJ.at(3);
    out_building.close();


    return 0;
}
