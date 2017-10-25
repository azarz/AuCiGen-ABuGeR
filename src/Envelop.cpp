#include "Envelop.h"
#include "catch.h"
#include "typeinfo"
#include "Footprint.h"
#include "Envelop.h"
#include "Parcel.h"
//#include "open_shp.h"


Envelop::Envelop(Footprint* trace)// have to add an arg Footprint&Envelop pointers to get an envelop from it
{
    //ctor

    /*//setting the buildingmodel pointer for volume
    this->volume = buildingmodel?????;
    */

    //setting the footprint pointer
    this->footprint = trace;

    //setting the parcel pointer
    this->parcel = trace->get_parcel();

    //calculating floor number
	double n_calc(( trace->get_parcel()->get_floorspace() )/( trace->get_geom()->OGRLineString::get_Area() ));
	this->n_floor = static_cast<int>(n_calc); //converting from double to int
}

Envelop::~Envelop()
{
    //dtor
}
/*

TEST_CASE("Envelop is created and its attributes ","[Envelop]")
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

    REQUIRE(env.get_n_floor() > 0);
    REQUIRE(env.get_parcel()->get_geom()->getGeometryType() == 3);
    REQUIRE(env.get_footprint()->get_geom()->getGeometryType() == 2);
    //REQUIRE(env.get_volume());
}
*/
