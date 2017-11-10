#include"SS.h"
#include <iostream>

using namespace std;

void compute_roof()
{
    //check number of vertice
    cout<< "hello";
}

void crossed_spine(Building bu, double roofAngle)
{
    //getting the Buildingmodels
    vector<BuildingModel> bus = bu.get_building_models();

    //getting the exterior ring of the polygon ...
    OGRPolygon* poPoly = bu.get_parcel()->get_geom();
    OGRLinearRing* poExteriorRing = (OGRLinearRing*)poPoly->getExteriorRing();
    //setting all the vertices edges of the polygon
    vector<Point> li_point;
    OGRPoint ptTemp;
    int NumberOfExteriorRingVertices = poExteriorRing ->OGRSimpleCurve::getNumPoints();
    for ( int k = 0; k < NumberOfExteriorRingVertices-1; k++)
    {
        poExteriorRing ->getPoint(k,&ptTemp);
        Point* pt;
        if (ptTemp.getX()!=0.0 && ptTemp.getY()!=0.0)
        {
            pt= new Point(ptTemp.getX(), ptTemp.getY(),bu.get_height());
            li_point.push_back(*pt);
        }
    }
    //getting the OGR centroid
    OGRPoint centroid;
    poPoly->Centroid(&centroid);
    //setting the vertice of the centroid
    Point P;
    P.set_x(centroid.getX());
    P.set_y(centroid.getY());
    //setting the Z value w/ Thales relation = Tan(angle)*centroid_distance
    double d;
    d = ( P.get_y()-li_point.at(0).get_y() )/( P.get_x()-li_point.at(0).get_x() );
    if (d<0){d*=-1;}//setting value to positive if it's negative
    P.set_z(( bu.get_height() )+( tan(roofAngle)*d ));
    cout<<d<<endl;
    cout<<P.get_z();

    //adding a new building model 'roof' from triangular fronts to those of the building list.
    vector<Triangle> li_triangle;
    Triangle fa(P,li_point.at(0),li_point.at(1),ROOF);
    li_triangle.push_back(fa);
    Triangle fb(P,li_point.at(1),li_point.at(2),ROOF);
    li_triangle.push_back(fb);
    Triangle fc(P,li_point.at(2),li_point.at(3),ROOF);
    li_triangle.push_back(fc);
    Triangle fd(P,li_point.at(3),li_point.at(0),ROOF);
    li_triangle.push_back(fd);

    BuildingModel roof(li_triangle,bu.get_parcel());
    bus.push_back(roof);
}

void linear_spine(Building bu, double roofAngle)
{
//getting the Buildingmodels
    vector<BuildingModel> bus = bu.get_building_models();

    //getting the exterior ring of the polygon ...
    OGRPolygon* poPoly = bu.get_parcel()->get_geom();
    OGRLinearRing* poExteriorRing = (OGRLinearRing*)poPoly->getExteriorRing();
    //setting all the vertices edges of the polygon
    vector<Point> li_point;
    OGRPoint ptTemp;
    int NumberOfExteriorRingVertices = poExteriorRing ->OGRSimpleCurve::getNumPoints();
    for ( int k = 0; k < NumberOfExteriorRingVertices-1; k++)
    {
        poExteriorRing ->getPoint(k,&ptTemp);
        Point* pt;
        if (ptTemp.getX()!=0.0 && ptTemp.getY()!=0.0)
        {
            pt= new Point(ptTemp.getX(), ptTemp.getY(),bu.get_height());
            li_point.push_back(*pt);
        }
    }

    //getting the higher distance edge (lengthwise and crosswise)
    double l1 = ( li_point.at(1).get_y()-li_point.at(0).get_y() )/( li_point.at(1).get_x()-li_point.at(0).get_x() );
    if (l1<0){l1*=-1;}//setting value to positive if it's negative
    double l2 = ( li_point.at(1).get_y()-li_point.at(2).get_y() )/( li_point.at(1).get_x()-li_point.at(2).get_x() );
    if (l2<0){l2*=-1;}

    Point m1;// setting middle point of width on the left side
    Point m2;//and right side         (with height from angle roof)
    /* if __l1__           else  __l1__
      a...........b              a....b
      .           .   |          . m1 .
    m1.   l1>l2   .m2 l2         .    . |
      .           .   |          .    . l2
      d...........c              .    . |
                                 d....c
                                   m2
    */

    //if l1>l2: m2=c.translate([cb]/2) & m1=d.translate([da]/2),
    if (l1>l2)
        {
        m2.set_x( li_point.at(2).get_x() + ( (li_point.at(1).get_x()-li_point.at(2).get_x())/2) );
        m2.set_y( li_point.at(2).get_y() + ( (li_point.at(1).get_y()-li_point.at(2).get_y()) /2) );
        m2.set_z( li_point.at(2).get_z() + ( (li_point.at(1).get_z()-li_point.at(2).get_z()) /2) +(tan(roofAngle)*(l2/2)) );

        m1.set_x( li_point.at(3).get_x() + ( (li_point.at(0).get_x()-li_point.at(3).get_x()) /2) );
        m1.set_y( li_point.at(3).get_y() + ( (li_point.at(0).get_y()-li_point.at(3).get_y()) /2) );
        m1.set_z( li_point.at(3).get_z() + ( (li_point.at(0).get_z()-li_point.at(3).get_z()) /2) +(tan(roofAngle)*(l2/2)));

        }
    //else : m1=a.translate([ab]/2);m2=d.translate([dc]/2)
    else
    {
        m1.set_x( li_point.at(0).get_x() + ( (li_point.at(1).get_x()-li_point.at(0).get_x()) /2) );
        m1.set_y( li_point.at(0).get_y() + ( (li_point.at(1).get_y()-li_point.at(0).get_y()) /2) );
        m1.set_z( li_point.at(0).get_z() + ( (li_point.at(1).get_z()-li_point.at(0).get_z()) /2) +(tan(roofAngle)*(l2/2)) );

        m2.set_x( li_point.at(3).get_x() + ( (li_point.at(2).get_x()-li_point.at(3).get_x()) /2) );
        m2.set_y( li_point.at(3).get_y() + ( (li_point.at(2).get_y()-li_point.at(3).get_y()) /2) );
        m2.set_z( li_point.at(3).get_z() + ( (li_point.at(2).get_z()-li_point.at(3).get_z()) /2) +(tan(roofAngle)*(l1/2)));

    }
    //adding a new building model 'roof' from triangular fronts to those of the building list.
    vector<Triangle> li_triangle;
    Triangle fa(m1,li_point.at(0),li_point.at(1),ROOF);
    li_triangle.push_back(fa);
    Triangle fb(m1,li_point.at(1),m2,ROOF);
    li_triangle.push_back(fb);
    Triangle fc(m1,m2,li_point.at(2),ROOF);
    li_triangle.push_back(fc);
    Triangle fd(m1,li_point.at(2),li_point.at(3),ROOF);
    li_triangle.push_back(fd);

    BuildingModel roof(li_triangle,bu.get_parcel());
    bus.push_back(roof);
}


void linear_cross_spine(/*trace*/)
{
//get vertices
//get segments 11 & l2
//if l1>l2:E=b.translate((bc/2)+(ba/4));F=d.translate((da/2)+(ab/4);
//else : E=a.translate((ab/2));F=c.translate((cd/2));
}

/*
#include "catch.h"
#include "open_shp.h"
#include "Point.h"
//#include <fstream>
TEST_CASE("XSkeleton is computed","[crossed_spine]")
{
    int offset(0);
    vector<Road> ROADS;
    vector<Parcel> PARCELS;
    OGRPoint* centroid;
    const char* file_path ="1_data/test/road_test.shp";
    const char* layer_name ="road_test";
    centroid = open_shp_roads(file_path, ROADS, layer_name);
    file_path ="1_data/test/test_parcel.shp";
    layer_name ="test_parcel";
    open_shp_parcels(file_path, PARCELS, centroid, layer_name);

    OGRGeometry* parcel = PARCELS.at(30).get_geom();
    OGRLineString* v2 = get_intersection_road(parcel,ROADS);
    OGRLineString* v3 = get_other_sides(parcel,v2);
    Footprint v4 = PARCELS.at(30).create_footprint(v2,v3);
    Envelop v5 = v4.create_envelop();
    Building bu = Building(&v5);

    crossed_spine(bu, M_PI/8);
    linear_spine(bu, M_PI/8);
    bu.to_obj(centroid,offset);


}/**/
