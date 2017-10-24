#include <iostream>
#include <vector>
//#include "Parcel.h"
//#include "Envelop.h"
#include "open_shp.h"
#include <vector>
#include "Road.h"
#include "Parcel.h"
#include "orient.h"
#include "Footprint.h"

using namespace std;


vector<Road> ROADS;
vector<Parcel> PARCELS;


int main()
{
    //Parcel();
    char* fill_directory ="1_data/test/road_test.shp";
    char layer_type ='R';
    OpenShapeFile_roads(fill_directory, ROADS);
    fill_directory ="1_data/test/test_parcel.shp";
    layer_type ='P';
    OpenShapeFile_parcels(fill_directory, PARCELS);
    //OGRGeometry* v12 = PARCELS.at(0).get_geom();
    //ROADS.pop_back();
    cout << PARCELS.size() << endl;
    cout << "rest:" << PARCELS.at(0).get_geom()->getExteriorRing()->OGRSimpleCurve::getNumPoints() << endl;
    PARCELS.at(0).print();

    OGRGeometry* v1 = PARCELS.at(0).get_geom()->getExteriorRing();
    cout << v1->getGeometryName()<< endl;
    OGRLineString* v2 = get_intersection_road(v1,ROADS);
    OGRLineString* v3 = get_other_sides(v1,v2);
    OGRLinearRing* v4 = PARCELS.at(0).create_footprint(v2,v3);
    int v5=0;
    int v6=0;
    int v7=0;
    int v8=0;

    Footprint* footprint2 = new Footprint(v4,&PARCELS.at(0));

    cout << "Test Antoine " << footprint2->get_parcel()->get_area() << endl;
    cout << "Hello world!" << endl;
    return 0;
}
