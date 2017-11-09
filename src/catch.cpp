//#define CATCH_CONFIG_MAIN
#include "catch.h"

#include <iostream>
#include <vector>

//classes
#include "Building.h"
#include "BuildingModel.h"
#include "BuildingType.h"
#include "Envelop.h"
#include "Footprint.h"
#include "Parcel.h"
#include "Point.h"
#include "Road.h"
#include "Triangle.h"

//functions
#include "create_wall.h"
#include "get_max_rectangle.h"
#include "matrix_methods.h"
#include "open_shp.h"
#include "orient.h"
#include "poly_to_triangle.h"

//////////// Building //////////////



////////////////////////////////////

////////// BuildingModel ///////////
/*
TEST_CASE("BuildingModel and Getters are computed", "[BuildingModel]")
{
    Point p1(1,1,0);
    Point p2(2,1,0);
    Point p3(1,2,0);

    Triangle tri(p1,p2,p3,WALL);
    vector<Triangle> ltri;
    ltri.push_back(tri);

    Parcel par;
    BuildingModel test = BuildingModel(ltri,&par);

    REQUIRE(test.get_li_triangle()[0].is_equal(tri));
    //REQUIRE(test.get_parcel() ==)
}

TEST_CASE("translate BuildingModel", "[translate]")
{
    Point a =  Point(2,5,6);
    Point b =  Point(3,9,7);
    Point c =  Point(5,6,8);

    Triangle d = Triangle(a,b,c,WALL);

    double vec[3];
    vec[0] = 1;
    vec[1] = 2;
    vec[2] = 3;

    Point e =  Point(3,7,9);
    Point f =  Point(4,11,10);
    Point g =  Point(6,8,11);

    Triangle h = Triangle(e,f,g,FLOOR);

    vector<Triangle> ltri;
    ltri.push_back(d);
    ltri.push_back(h);

    Parcel par;
    BuildingModel test = BuildingModel(ltri,&par);

    test.translate(vec,WALL);

    REQUIRE(test.get_li_triangle()[0].is_equal(test.get_li_triangle()[1]));
}

TEST_CASE("rotate BuildingModel", "[rotate]")
{

}

TEST_CASE("size BuildingModel", "[size]")
{

}

TEST_CASE("split BuildingModel are computed", "[spli]")
{
    // simple intersection

    Point p1(1,1,0);
    Point p2(2,1,0);
    Point p3(1,2,0);

    Triangle tri(p1,p2,p3,WALL);

    Point origin(0,0,0);
    double axis[3][1];
    axis[0][0] = 1;
    axis[1][0] = 1;
    axis[2][0] = 0;

    vector<Triangle> ltri;
    ltri.push_back(tri);

    Parcel par;
    BuildingModel test = BuildingModel(ltri,&par);

    test.split(*axis,origin,WALL,ROOF);

    Point iZ(1.5,1.5,0);

    REQUIRE(test.get_li_triangle().size()==2);
    REQUIRE(test.get_li_triangle()[0].get_type()==ROOF);
    REQUIRE(test.get_li_triangle()[0].get_p1()==p1);
    REQUIRE(test.get_li_triangle()[0].get_p2()==p2);
    REQUIRE(test.get_li_triangle()[0].get_p3()==iZ);
    REQUIRE(test.get_li_triangle()[1].get_p3()==p3);

    // double intersection (d)

    Point dp1(1,1,0);
    Point dp2(2,1,0);
    Point dp3(1,2,0);

    Triangle dtri(dp1,dp2,dp3,WALL);

    Point dorigin(0,2.5,0);
    double daxis[3][1];
    daxis[0][0] = 1;
    daxis[1][0] = -1;
    daxis[2][0] = 8;

    vector<Triangle> dltri;
    dltri.push_back(dtri);

    Parcel dpar;
    BuildingModel dtest = BuildingModel(dltri,&dpar);

    dtest.split(*daxis,dorigin,WALL,ROOF);

    Point diX(1.5,1,0);
    Point diY(1,1.5,0);

    REQUIRE(dtest.get_li_triangle().size()==3);
    REQUIRE(dtest.get_li_triangle()[0].get_type()==ROOF);
    REQUIRE(dtest.get_li_triangle()[0].get_p1()==dp1);
    REQUIRE(dtest.get_li_triangle()[0].get_p2()==diX);
    REQUIRE(dtest.get_li_triangle()[0].get_p3()==diY);
    REQUIRE(dtest.get_li_triangle()[2].get_p1()==dp2);
    REQUIRE(dtest.get_li_triangle()[1].get_p1()==dp3);

    // no intersection

    Point np1(1,1,0);
    Point np2(2,1,0);
    Point np3(1,2,0);

    Triangle ntri(np1,np2,np3,WALL);

    Point norigin(0,0,0);
    double naxis[3][1];
    naxis[0][0] = 1;
    naxis[1][0] = -1;
    naxis[2][0] = 8;

    vector<Triangle> nltri;
    nltri.push_back(ntri);

    Parcel npar;
    BuildingModel ntest = BuildingModel(nltri,&npar);

    ntest.split(*naxis,norigin,WALL,ROOF);

    REQUIRE(ntest.get_li_triangle().size()==1);
    REQUIRE(ntest.get_li_triangle()[0].get_type()==WALL);
    REQUIRE(ntest.get_li_triangle()[0].get_p1()==np1);
    REQUIRE(ntest.get_li_triangle()[0].get_p2()==np2);
    REQUIRE(ntest.get_li_triangle()[0].get_p3()==np3);

    // ux issue

    Point xp1(1,1,0);
    Point xp2(2,1,0);
    Point xp3(1,2,0);

    Triangle xtri(xp1,xp2,xp3,WALL);

    Point xorigin(0,1.5,0);
    double xaxis[3][1];
    xaxis[0][0] = 1;
    xaxis[1][0] = 0;
    xaxis[2][0] = 8;

    vector<Triangle> xltri;
    xltri.push_back(xtri);

    Parcel xpar;
    BuildingModel xtest = BuildingModel(xltri,&xpar);

    xtest.split(*xaxis,xorigin,WALL,ROOF);

    Point xiY(1,1.5,0);
    Point xiZ(1.5,1.5,0);

    REQUIRE(xtest.get_li_triangle().size()==3);
    REQUIRE(xtest.get_li_triangle()[0].get_type()==ROOF);
    REQUIRE(xtest.get_li_triangle()[0].get_p1()==xp1);
    REQUIRE(xtest.get_li_triangle()[0].get_p2()==xiZ);
    REQUIRE(xtest.get_li_triangle()[0].get_p3()==xiY);
    REQUIRE(xtest.get_li_triangle()[1].get_p1()==xp2);
    REQUIRE(xtest.get_li_triangle()[2].get_p1()==xp3);

    // uy issue

    Point yp1(1,1,0);
    Point yp2(2,1,0);
    Point yp3(1,2,0);

    Triangle ytri(yp1,yp2,yp3,WALL);

    Point yorigin(1.5,0,0);
    double yaxis[3][1];
    yaxis[0][0] = 0;
    yaxis[1][0] = 1;
    yaxis[2][0] = 0;

    vector<Triangle> yltri;
    yltri.push_back(ytri);

    Parcel ypar;
    BuildingModel ytest = BuildingModel(yltri,&ypar);

    ytest.split(*yaxis,yorigin,WALL,ROOF);

    Point yiX(1.5,1,0);
    Point yiZ(1.5,1.5,0);

    REQUIRE(ytest.get_li_triangle().size()==3);
    REQUIRE(ytest.get_li_triangle()[0].get_type()==ROOF);
    REQUIRE(ytest.get_li_triangle()[0].get_p1()==yp1);
    REQUIRE(ytest.get_li_triangle()[0].get_p2()==yiX);
    REQUIRE(ytest.get_li_triangle()[0].get_p3()==yp2);
    REQUIRE(ytest.get_li_triangle()[2].get_p3()==yiZ);
    REQUIRE(ytest.get_li_triangle()[2].get_p1()==yp3);
}

////////////////////////////////////

////////// BuildingType ////////////

TEST_CASE("Industry are computed", "[Industry]")
{
    Industry I;
    REQUIRE(I.get_floor() ==1);
    REQUIRE(I.get_floor_height() ==3);
    REQUIRE(I.get_gap() ==15);
    REQUIRE(I.get_height(1) ==3);
    REQUIRE(I.get_height(2) ==21);
    REQUIRE(I.get_height(3) ==24);
    double tmp[] = { 2, 3 };
    std::vector<double> margin( tmp, tmp+2 );
    REQUIRE(I.get_margin() ==margin);
    REQUIRE(I.get_margin_parcel() ==2);
    REQUIRE(I.get_margin_road() ==3);
    REQUIRE(I.get_profitability() ==2);
    REQUIRE(I.get_roof() ==1);
    REQUIRE(I.get_wall() ==1);
}
TEST_CASE("Office are computed", "[Office]")
{
    Office I;
    REQUIRE(I.get_floor() ==1);
    REQUIRE(I.get_floor_height() ==3);
    REQUIRE(I.get_gap() ==5);
    REQUIRE(I.get_height(1) ==3);
    REQUIRE(I.get_height(2) ==11);
    REQUIRE(I.get_height(3) ==14);
    double tmp[] = { 0.001, 0.001 };
    std::vector<double> margin( tmp, tmp+2 );
    REQUIRE(I.get_margin() ==margin);
    REQUIRE(I.get_margin_parcel() ==0.001);
    REQUIRE(I.get_margin_road() ==0.001);
    REQUIRE(I.get_profitability() ==12);
    REQUIRE(I.get_roof() ==1);
    REQUIRE(I.get_wall() ==1);
}
TEST_CASE("ApartmentBuilding are computed", "[ApartmentBuilding]")
{
    ApartmentBuilding I;
    REQUIRE(I.get_floor() ==1);
    REQUIRE(I.get_floor_height() ==3);
    REQUIRE(I.get_gap() ==5);
    REQUIRE(I.get_height(1) ==3);
    REQUIRE(I.get_height(2) ==11);
    REQUIRE(I.get_height(3) ==14);
    double tmp[] = { 0.001, 0.05 };
    std::vector<double> margin( tmp, tmp+2 );
    REQUIRE(I.get_margin() ==margin);
    REQUIRE(I.get_margin_parcel() ==0.001);
    REQUIRE(I.get_margin_road() ==0.05);
    REQUIRE(I.get_profitability() ==6);
    REQUIRE(I.get_roof() ==1);
    REQUIRE(I.get_wall() ==1);
}
TEST_CASE(" Villa are computed", "[Villa]")
{
    Villa I;
    REQUIRE(I.get_floor() ==1);
    REQUIRE(I.get_floor_height() ==3);
    REQUIRE(I.get_gap() ==3);
    REQUIRE(I.get_height(1) ==3);
    REQUIRE(I.get_height(2) ==9);
    REQUIRE(I.get_height(3) ==12);
    double tmp[] = { 0.1, 0.1 };
    std::vector<double> margin( tmp, tmp+2 );
    REQUIRE(I.get_margin() ==margin);
    REQUIRE(I.get_margin_parcel() ==0.1);
    REQUIRE(I.get_margin_road() ==0.1);
    REQUIRE(I.get_profitability() ==1);
    REQUIRE(I.get_roof() ==1);
    REQUIRE(I.get_wall() ==1);
}
TEST_CASE("Townhouse are computed", "[Townhouse]")
{
    Townhouse I;
    REQUIRE(I.get_floor() ==1);
    REQUIRE(I.get_floor_height() ==1);
    REQUIRE(I.get_gap() ==1);
    REQUIRE(I.get_height(1) ==1);
    REQUIRE(I.get_height(2) ==3);
    REQUIRE(I.get_height(3) ==4);
    double tmp[] = { 0.001, 0.05};
    std::vector<double> margin( tmp, tmp+2 );
    REQUIRE(I.get_margin() ==margin);
    REQUIRE(I.get_margin_parcel() ==0.001);
    REQUIRE(I.get_margin_road() ==0.05);
    REQUIRE(I.get_profitability() ==1);
    REQUIRE(I.get_roof() ==1);
    REQUIRE(I.get_wall() ==1);
}

////////////////////////////////////

//////////// Envelop //////////////

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
    //cout << v1->getGeometryName()<< endl;

    OGRLineString* v2 = get_intersection_road(v1,ROADS);
    //cout << v2->getGeometryName()<< endl;
    //cout << v2->OGRSimpleCurve::getNumPoints()<< endl;

    OGRLineString* v3 = get_other_sides(v1,v2);
    //cout << v3->getGeometryName()<< endl;
    //cout << v3->OGRSimpleCurve::getNumPoints()<< endl;

    Footprint v4 = PARCELS.at(35).create_footprint(v2,v3);
    Envelop env = v4.create_envelop();

    REQUIRE(env.get_n_floor() > 0);
    REQUIRE(env.get_parcel()->get_geom()->getGeometryType() == 3);
    REQUIRE(env.get_footprint()->get_geom()->getGeometryType() == 2);
    REQUIRE(env.get_height() > 0);
}

////////////////////////////////////

//////////// Footprint /////////////

TEST_CASE("Footprint is created and its attributes ","[Footprint]")
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
    //cout << v1->getGeometryName()<< endl;

    OGRLineString* v2 = get_intersection_road(v1,ROADS);
    //cout << v2->getGeometryName()<< endl;
    //cout << v2->OGRSimpleCurve::getNumPoints()<< endl;

    OGRLineString* v3 = get_other_sides(v1,v2);
    //cout << v3->getGeometryName()<< endl;
    //cout << v3->OGRSimpleCurve::getNumPoints()<< endl;

    Footprint v4 = PARCELS.at(35).create_footprint(v2,v3);
    //cout<<v4.get_parcel()->get_geom()->getGeometryType()<<endl;
    REQUIRE(v4.get_geom()->getGeometryType() == 2);
    REQUIRE(v4.get_parcel()->get_geom()->getGeometryType()== 3);
}

TEST_CASE("Envelop is created","[create_envelop]")
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
    //cout << v1->getGeometryName()<< endl;

    OGRLineString* v2 = get_intersection_road(v1,ROADS);
    //cout << v2->getGeometryName()<< endl;
    //cout << v2->OGRSimpleCurve::getNumPoints()<< endl;

    OGRLineString* v3 = get_other_sides(v1,v2);
    //cout << v3->getGeometryName()<< endl;
    //cout << v3->OGRSimpleCurve::getNumPoints()<< endl;

    Footprint v4 = PARCELS.at(35).create_footprint(v2,v3);
    Envelop env = v4.create_envelop();
    //cout << typeid(env).name();
    //cout <<"n-floor "<<env.get_n_floor()<<endl;
    REQUIRE(env.get_n_floor() > 0);
    REQUIRE(env.get_parcel()->get_geom()->getGeometryType() == 3);
    REQUIRE(env.get_footprint()->get_geom()->getGeometryType() == 2);
    //REQUIRE(env.get_volume());
}
*/
////////////////////////////////////

///////////// Parcel ///////////////
/*
TEST_CASE("Parcel are computed","[Parcel]")
{
    char* wkt ="POLYGON ((55.4683455250644 -21.3282187046573,55.4683460303297 -21.3282180820721,55.4685788303297 -21.3279358820721,55.4685905503442 -21.3279255206688,55.46860489859 -21.3279192880722,55.468620470561 -21.3279177943725,55.468635741964 -21.3279211857833,55.4686492179279 -21.3279291303297,55.4686595793312 -21.3279408503442,55.4686658119277 -21.32795519859,55.4686673056275 -21.327970770561,55.4686639142167 -21.327986041964,55.4686559696703 -21.3279995179279,55.4684234247991 -21.3282814086609,55.4681532749356 -21.3286197953427,55.4681417225811 -21.3286303433531,55.4681274761246 -21.3286368052333,55.4681119301085 -21.3286385484493,55.4680966062852 -21.3286354023632,55.4680830046573 -21.3286276749356,55.4680724566469 -21.3286161225811,55.4680659947667 -21.3286018761245,55.4680642515507 -21.3285863301085,55.4680673976368 -21.3285710062852,55.4680751250644 -21.3285574046573,55.4683455250644 -21.3282187046573))";
    OGRPolygon poPolygon= OGRPolygon();
    poPolygon.OGRPolygon::importFromWkt( &wkt);
    Parcel p= Parcel(&poPolygon);

    char* wktS;
    p.get_geom()->exportToWkt(&wktS);
    //REQUIRE(wktS==wkt);
}
*/
////////////////////////////////////

////////////// Point ///////////////
/*
TEST_CASE("Point constructor + Getters + Setters","[Point] [get_x] [get_y] [get_z] [set_x] [set_y] [set_z]")
{
    Point a =  Point(2,5,6);
    Point b =  Point();
    b.set_x(3);
    b.set_y(9);
    b.set_z(7);

    REQUIRE(a.get_x()==2.0);
    REQUIRE(a.get_y()==5.0);
    REQUIRE(a.get_z()==6.0);
    REQUIRE(b.get_x()==3.0);
    REQUIRE(b.get_y()==9.0);
    REQUIRE(b.get_z()==7.0);
}

TEST_CASE("operator == Point are computed","[opertator==]")
{
    Point a =  Point(2,5,6);
    Point b =  Point(3,9,7);
    Point c =  Point(5,6,8);

    REQUIRE(a==a);
    REQUIRE(b==b);
    REQUIRE(!(c==a));
}

TEST_CASE("translate Point are computed","[translate]")
{
    Point a =  Point(2,5,6);
    double vec[3];
    vec[0] = 1;
    vec[1] = 2;
    vec[2] = 3;
    a.translate(vec);

    REQUIRE(a.get_x()==3.0);
    REQUIRE(a.get_y()==7.0);
    REQUIRE(a.get_z()==9.0);
}

TEST_CASE("rotate Point are computed", "[rotate]")
{
    Point a = Point(1,-1,2);
    double vec[3];
    vec[0] = 0;
    vec[1] = 0;
    vec[2] = 1;
    double angle =  M_PI_2l;
    a.rotate(vec,angle);

    REQUIRE(a.get_x()==1.0);
    //REQUIRE(a.get_y()==sin(M_PI_2l)*1*1);
    REQUIRE(a.get_z()==2.0);
}

TEST_CASE("size Point are computed", "[size]")
{
    Point a = Point(2,5,6);
    double vec[3];
    vec[0] = 1;
    vec[1] = 2;
    vec[2] = 3;
    a.size(vec);

    REQUIRE(a.get_x()==2.0);
    REQUIRE(a.get_y()==10.0);
    REQUIRE(a.get_z()==18.0);
}

////////////////////////////////////

////////////// Road ////////////////

TEST_CASE("Road are computed","[Road]")
{
    const char* wkt ="POLYGON ((55.4683455250644 -21.3282187046573,55.4683460303297 -21.3282180820721,55.4685788303297 -21.3279358820721,55.4685905503442 -21.3279255206688,55.46860489859 -21.3279192880722,55.468620470561 -21.3279177943725,55.468635741964 -21.3279211857833,55.4686492179279 -21.3279291303297,55.4686595793312 -21.3279408503442,55.4686658119277 -21.32795519859,55.4686673056275 -21.327970770561,55.4686639142167 -21.327986041964,55.4686559696703 -21.3279995179279,55.4684234247991 -21.3282814086609,55.4681532749356 -21.3286197953427,55.4681417225811 -21.3286303433531,55.4681274761246 -21.3286368052333,55.4681119301085 -21.3286385484493,55.4680966062852 -21.3286354023632,55.4680830046573 -21.3286276749356,55.4680724566469 -21.3286161225811,55.4680659947667 -21.3286018761245,55.4680642515507 -21.3285863301085,55.4680673976368 -21.3285710062852,55.4680751250644 -21.3285574046573,55.4683455250644 -21.3282187046573))";
    OGRPolygon poPolygon= OGRPolygon();
    poPolygon.OGRPolygon::importFromWkt( &wkt);
    Road r= Road(&poPolygon, 1);
    REQUIRE(r.get_type()==1);
    char* wktS;
    r.get_geom()->exportToWkt(&wktS);
    //REQUIRE(wktS==wkt);
}

////////////////////////////////////

///////////// Triangle /////////////

TEST_CASE("Triangle constructor + Getters are computed", "[Triangle] [get_p1] [get_p2] [get_p3] [get_type]")
{
    Point a =  Point(2,5,6);
    Point b =  Point(3,9,7);
    Point c =  Point(5,6,8);
    Triangle d = Triangle(a,b,c,WALL);

    REQUIRE(d.get_p1() == a);
    REQUIRE(d.get_p2() == b);
    REQUIRE(d.get_p3() == c);
    REQUIRE(d.get_type() == WALL);
}


TEST_CASE("add_type Triangle are computed", "[add_type]")
{
    Point a =  Point(2,5,6);
    Point b =  Point(3,9,7);
    Point c =  Point(5,6,8);
    Triangle d = Triangle(a,b,c,WALL);
    d.set_type(ROOF);

    REQUIRE(d.get_type() == ROOF);
}

TEST_CASE("is_equal Triangle are computed", "[is_equal]")
{
    Point a =  Point(2,5,6);
    Point b =  Point(3,9,7);
    Point c =  Point(5,6,8);
    Triangle d = Triangle(a,b,c,WALL);
    Triangle e = Triangle(a,b,c,WALL);

    REQUIRE(d.is_equal(e));
}

TEST_CASE("translate Triangle are computed", "[translate]")
{
    Point a =  Point(2,5,6);
    Point b =  Point(3,9,7);
    Point c =  Point(5,6,8);

    Triangle d = Triangle(a,b,c,WALL);

    double vec[3];
    vec[0] = 1;
    vec[1] = 2;
    vec[2] = 3;

    d.translate(vec);

    Point e =  Point(3,7,9);
    Point f =  Point(4,11,10);
    Point g =  Point(6,8,11);

    Triangle h = Triangle(e,f,g,WALL);

    REQUIRE(d.is_equal(h));
}

TEST_CASE("rotate Triangle are computed", "[rotate]")
{

}

TEST_CASE("size Triangle are computed", "[size]")
{
    Point a =  Point(2,5,6);
    Point b =  Point(3,9,7);
    Point c =  Point(5,6,8);

    Triangle d = Triangle(a,b,c,WALL);

    double vec[3];
    vec[0] = 1;
    vec[1] = 2;
    vec[2] = 3;

    d.size(vec);

    Point e =  Point(2,10,18);
    Point f =  Point(3,18,21);
    Point g =  Point(5,12,24);

    Triangle h = Triangle(e,f,g,WALL);

    REQUIRE(d.is_equal(h));

}

TEST_CASE("split Triangle are computed", "[split]")
{
    Point p1(1,1,0);
    Point p2(2,1,0);
    Point p3(1,2,0);

    Triangle tri(p1,p2,p3,WALL);

    Point origin(0,0,0);
    double axis[3][1];
    axis[0][0] = 1;
    axis[1][0] = 1;
    axis[2][0] = 0;

    vector<Triangle> ltri;

    ltri = tri.split(*axis,origin,ROOF);

    Point iZ(1.5,1.5,0);

    REQUIRE(ltri.size()==2);
    REQUIRE(ltri[0].get_type()==ROOF);
    REQUIRE(ltri[0].get_p1()==p1);
    REQUIRE(ltri[0].get_p2()==p2);
    REQUIRE(ltri[0].get_p3()==iZ);
    REQUIRE(ltri[1].get_p3()==p3);
}

////////////////////////////////////
*/

