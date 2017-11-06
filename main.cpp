#include <iostream>
#include <vector>
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
    cout << PARCELS.at(1).get_type()->get_type() << endl;
    cout << "Test Amaury " << endl;


    vector<Triangle> roadTriangles;
    for(unsigned int i=0U; i< ROADS.size();++i)
    {
        // NE MARCHE PAS AVEC LA ROUTE 0 ET 32 ET SUREMENT D'AUTRES APRES
        ROADS.at(i).to_obj(centroid);
        cout << i << endl;

        poly_to_triangle(ROADS.at(i).get_geom(), roadTriangles, FLOOR);
    }

    triangles_to_obj(roadTriangles, centroid->getX(), centroid->getY());

    PARCELS.at(25).to_obj(centroid);
    return 0;
}
/* */
