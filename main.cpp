#include <iostream>
#include <vector>
//#include "Envelop.h"
#include "open_shp.h"
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

  //  cout << PARCELS.size() << endl;
   // cout << "rest:" << PARCELS.at(35).get_geom()->getExteriorRing()->OGRSimpleCurve::getNumPoints() << endl;
 //   PARCELS.at(35).print();

    OGRGeometry* v1 = PARCELS.at(35).get_geom();
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

    cout << "Test Amaury " << endl;
    ROADS.at(25).to_obj();
    PARCELS.at(25).to_obj();
    return 0;
}

