#include "Envelop.h"
#include "typeinfo"
#include "Footprint.h"
#include "Parcel.h"
#include "BuildingModel.h"
#include "poly_to_triangle.h"
#include "Triangle.h"
#include "create_wall.h"
#include "triangles_to_obj.h"

Envelop::Envelop(Footprint* trace)// have to add an arg Footprint&Envelop pointers to get an envelop from it
{
    //ctor

    //calculating floor number
    double n_calc(( trace->get_parcel()->get_floorspace() )/( trace->get_geom()->OGRLineString::get_Area() ));
	this->n_floor = static_cast<int>(n_calc); //converting from double to int

    //setting the buildingmodel pointer for volume
    height =trace->get_parcel()->get_type()->get_height(n_floor);
    /*OGRPolygon poPolygon;
    OGRLinearRing a= (OGRLinearRing)trace->get_geom();
    poPolygon.addRing(&a);
    vector<Triangle> li_vector;
    poly_to_triangle(&poPolygon, li_vector, FLOOR);
    create_wall(&poPolygon, height, li_vector);
    this->volume= li_vector;*/
    //setting the parcel pointer
    this->parcel = trace->get_parcel();

    //setting the footprint pointer
    this->footprint = trace;
}

Envelop::~Envelop()
{
    //dtor
}

vector<string> Envelop::to_obj(OGRPoint* centroid)
{
    OGRPolygon poPolygon = OGRPolygon();
    OGRLinearRing* a = footprint->get_geom();
    poPolygon.addRing(a);
    vector<Triangle> li_vector;
    poly_to_triangle(&poPolygon, li_vector, FLOOR);
    create_wall(&poPolygon, height, li_vector);
    return triangles_to_obj(li_vector, centroid->getX(), centroid->getY());
}

/*
#include "catch.h"
#include "open_shp.h"
TEST_CASE("Envelop is created and its attributes ","[Envelop]")
{
    vector<Road> ROADS;
    vector<Parcel> PARCELS;
    OGRPoint* centroid;
    //Parcel();
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

    REQUIRE(env.get_n_floor() > 0);
    REQUIRE(env.get_parcel()->get_geom()->getGeometryType() == 3);
    REQUIRE(env.get_footprint()->get_geom()->getGeometryType() == 2);
    REQUIRE(env.get_height() > 0);
}
*/
