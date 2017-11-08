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
    //Parcel();
    const char* file_path ="1_data/paris_test/route_secondaire_buffer.shp";
    const char* layer_name ="route_secondaire_buffer";
    centroid = open_shp_roads(file_path, ROADS, layer_name);
    file_path ="1_data/paris_test/test_paris_seuil.shp";
    layer_name ="test_paris_seuil";
    open_shp_parcels(file_path, PARCELS, centroid, layer_name);

  //  cout << PARCELS.size() << endl;
   // cout << "rest:" << PARCELS.at(35).get_geom()->getExteriorRing()->OGRSimpleCurve::getNumPoints() << endl;
 //   PARCELS.at(35).print();


    OGRGeometry* v1 = PARCELS.at(35).get_geom();
    OGRGeometry* v12 = ROADS.at(ROADS.size()-1).get_geom();
    cout << v1->Distance(centroid) << endl;
   // cout << v1->getGeometryName()<< endl;

    OGRLineString* v2 = get_intersection_road(v1,ROADS);
   // cout << v2->getGeometryName()<< endl;
   // cout << v2->OGRSimpleCurve::getNumPoints()<< endl;

    OGRLineString* v3 = get_other_sides(v1,v2);
   // cout << v3->getGeometryName()<< endl;
    //cout << v3->OGRSimpleCurve::getNumPoints()<< endl;

    Footprint footprint2 = PARCELS.at(35).create_footprint(v2,v3);

  //  cout << "Test Antoine " << footprint2.get_parcel()->get_area() << endl;
    cout << "Hello world!" << endl;
    cout << PARCELS.at(35).get_type()->get_type() << endl;
    cout << PARCELS.at(580).get_type()->get_type() << endl;
    cout << "Test Amaury " << endl;


    vector<Triangle> roadTriangles;
    for(unsigned int i=0U; i< ROADS.size();++i)
    {
        poly_to_triangle(ROADS.at(i).get_geom(), roadTriangles, FLOOR);
    }

    vector<Triangle> parcelTriangles;

    vector<string> envelopObj;
    envelopObj.push_back("");
    envelopObj.push_back("");
    envelopObj.push_back("");

    for(unsigned int i=0U; i<PARCELS.size();++i)
    {
        cout << i << endl;
        Parcel parcel = PARCELS.at(i);
        vector<string> envelopObj_temp;
        poly_to_triangle(parcel.get_geom(), parcelTriangles, FLOOR);

        OGRLineString* linearIntersection = get_intersection_road(parcel.get_geom(), ROADS);
        OGRLineString* otherSides = get_other_sides(parcel.get_geom(), linearIntersection);

        Footprint footprint = parcel.create_footprint(linearIntersection, otherSides);
        cout << footprint.get_geom()->getGeometryName() << endl;

        Envelop envelop = footprint.create_envelop();
        envelopObj_temp = envelop.to_obj(centroid);
        for (int k = 0; k<3; ++k)
        {
            envelopObj.at(k)+=envelopObj_temp.at(k);
        }
        delete linearIntersection;
        delete otherSides;
    }

    vector<string> result_roads = triangles_to_obj(roadTriangles,
                                                   centroid->getX(), centroid->getY());
    vector<string> result_parcels = triangles_to_obj(parcelTriangles,
                                                     centroid->getX(), centroid->getY());

    //To have an output file
    ofstream out_road("2_models/roads.obj");
    out_road << result_roads.at(0) << result_roads.at(1) << result_roads.at(2);
    out_road.close();

    ofstream out_parcel("2_models/parcels.obj");
    out_parcel << result_parcels.at(0) << result_parcels.at(1) << result_parcels.at(2);
    out_parcel.close();

    ofstream out_envelop("2_models/envelops.obj");
    out_envelop << envelopObj.at(0) << envelopObj.at(1) << envelopObj.at(2);
    out_envelop.close();

    return 0;
}
