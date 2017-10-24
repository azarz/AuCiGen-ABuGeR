#include "Footprint.h"
#include "Envelop.h"
#include "Parcel.h"
#include "catch.h"

Footprint::Footprint(OGRLinearRing* linearRing, Parcel* parcel)
{
    this->geom = linearRing;
    this->parcel = parcel;
}

Footprint::~Footprint()
{
    //dtor
}


Envelop Footprint::create_envelop()
{
    // return an object envelop instancied by Envelop class from here
    Envelop envelop(this);
    return envelop;

}


/*
TEST_CASE("footprint is created and its attributes ","[Foorprint]")
{

    vector<Road> ROADS;
    vector<Parcel> PARCELS;
    char* fill_directory ="1_data/test/road_test.shp";
    char layer_type ='R';
    OpenShapeFile_roads(fill_directory, ROADS);
    fill_directory ="1_data/test/test_parcel.shp";
    layer_type ='P';
    OpenShapeFile_parcels(fill_directory, PARCELS);

    OGRGeometry* v1 = PARCELS.at(35).get_geom();
    cout << v1->getGeometryName()<< endl;

    OGRLineString* v2 = get_intersection_road(v1,ROADS);
    cout << v2->getGeometryName()<< endl;
    cout << v2->OGRSimpleCurve::getNumPoints()<< endl;

    OGRLineString* v3 = get_other_sides(v1,v2);
    cout << v3->getGeometryName()<< endl;
    cout << v3->OGRSimpleCurve::getNumPoints()<< endl;

    Footprint v4 = PARCELS.at(35).create_footprint(v2,v3);
    cout << v4.get_geom()<< v4.get_parcel()<<endl;
}


TEST_CASE("envelop is created","[create_envelop]")
{
    vector<Road> ROADS;
    vector<Parcel> PARCELS;
    char* fill_directory ="1_data/test/road_test.shp";
    char layer_type ='R';
    OpenShapeFile_roads(fill_directory, ROADS);
    fill_directory ="1_data/test/test_parcel.shp";
    layer_type ='P';
    OpenShapeFile_parcels(fill_directory, PARCELS);

    OGRGeometry* v1 = PARCELS.at(35).get_geom();
    cout << v1->getGeometryName()<< endl;

    OGRLineString* v2 = get_intersection_road(v1,ROADS);
    cout << v2->getGeometryName()<< endl;
    cout << v2->OGRSimpleCurve::getNumPoints()<< endl;

    OGRLineString* v3 = get_other_sides(v1,v2);
    cout << v3->getGeometryName()<< endl;
    cout << v3->OGRSimpleCurve::getNumPoints()<< endl;

    Footprint v4 = PARCELS.at(35).create_footprint(v2,v3);
    Envelop env = v4.create_envelop();
}

*/
