#include "Footprint.h"
#include "Envelop.h"
#include "Parcel.h"

#include "typeinfo"

using namespace std;

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
    Envelop a = Envelop(this);
    return a;

}

/*
#include "catch.h"
#include "open_shp.h"
TEST_CASE("footprint is created and its attributes ","[Foorprint]")
{
    vector<Road> ROADS;
    vector<Parcel> PARCELS;
    OGRPoint* centroid;
    const char* file_path ="1_data/test/road_test.shp";
    const char* layer_name ="road_test";
    centroid = open_shp_roads(file_path, ROADS, layer_name);
    file_path ="1_data/test/test_parcel.shp";
    layer_name ="test_parcel";
    open_shp_parcels(file_path, PARCELS, centroid, layer_name);

    OGRGeometry* v1 = PARCELS.at(35).get_geom();
    cout << v1->getGeometryName()<< endl;

    OGRLineString* v2 = get_intersection_road(v1,ROADS);
    cout << v2->getGeometryName()<< endl;
    cout << v2->OGRSimpleCurve::getNumPoints()<< endl;

    OGRLineString* v3 = get_other_sides(v1,v2);
    cout << v3->getGeometryName()<< endl;
    cout << v3->OGRSimpleCurve::getNumPoints()<< endl;

    Footprint v4 = PARCELS.at(35).create_footprint(v2,v3);
    cout<<v4.get_parcel()->get_geom()->getGeometryType()<<endl;
    REQUIRE(v4.get_geom()->getGeometryType() == 2);
    REQUIRE(v4.get_parcel()->get_geom()->getGeometryType()== 3);
}


TEST_CASE("envelop is created","[create_envelop]")
{
    vector<Road> ROADS;
    vector<Parcel> PARCELS;
    OGRPoint* centroid;
    const char* file_path ="1_data/test/road_test.shp";
    const char* layer_name ="road_test";
    centroid = open_shp_roads(file_path, ROADS, layer_name);
    file_path ="1_data/test/test_parcel.shp";
    layer_name ="test_parcel";
    open_shp_parcels(file_path, PARCELS, centroid, layer_name);

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
    //cout << typeid(env).name();
    cout <<"n-floor "<<env.get_n_floor()<<endl;
    REQUIRE(env.get_n_floor() > 0);
    REQUIRE(env.get_parcel()->get_geom()->getGeometryType() == 3);
    REQUIRE(env.get_footprint()->get_geom()->getGeometryType() == 2);
    //REQUIRE(env.get_volume());
}
/**/
