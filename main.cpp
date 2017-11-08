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
    const char* fill_directory ="1_data/test/road_test.shp";
    centroid = open_shp_roads(fill_directory, ROADS);
    fill_directory ="1_data/test/test_parcel.shp";
    open_shp_parcels(fill_directory, PARCELS, centroid);

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
    for(unsigned int i=0U; i< PARCELS.size();++i)
    {
        Parcel parcel = PARCELS.at(i);
        poly_to_triangle(parcel.get_geom(), parcelTriangles, FLOOR);
        OGRLineString linearIntersection = *get_intersection_road(parcel.get_geom(), ROADS);
        OGRLineString otherSides = *get_other_sides(parcel.get_geom(), &linearIntersection);

        Footprint footprint = PARCELS.at(i).create_footprint(&linearIntersection, &otherSides);
        Envelop envelop = footprint.create_envelop();
        envelop.to_obj(centroid);
    }

    vector<string> result_roads = triangles_to_obj(roadTriangles,
                                                   centroid->getX(), centroid->getY());
    vector<string> result_parcels = triangles_to_obj(parcelTriangles,
                                                     centroid->getX(), centroid->getY());

    //To have an output file
    ofstream out_road("roads.obj");
    out_road << result_roads.at(0) << result_roads.at(1) << result_roads.at(2);
    out_road.close();

    ofstream out_parcel("parcels.obj");
    out_parcel << result_parcels.at(0) << result_parcels.at(1) << result_parcels.at(2);
    out_parcel.close();

    return 0;
}
