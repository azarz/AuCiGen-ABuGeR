#include"SS.h"
#include <iostream>

using namespace std;

BuildingModel crossed_spine(Building bu, double roofAngle)
{
    //getting the Buildingmodels
    vector<BuildingModel> bus = bu.get_building_models();
    double height=bu.get_height();

    //getting the exterior ring of the polygon ...
    OGRPolygon* poPoly = bu.get_geom();
    OGRLinearRing* poExteriorRing = (OGRLinearRing*)poPoly->getExteriorRing();
    //setting all the vertices edges of the polygon
    vector<Point> li_point;
    OGRPoint ptTemp;
    int NumberOfExteriorRingVertices = poExteriorRing ->OGRSimpleCurve::getNumPoints();
    double centroidx =0;
    double centroidy =0;
    for ( int k = 0; k < NumberOfExteriorRingVertices-1; k++)
    {
        poExteriorRing ->getPoint(k,&ptTemp);
        Point pt;
        if (ptTemp.getX()!=0.0 && ptTemp.getY()!=0.0)
        {
            pt= Point(ptTemp.getX(), ptTemp.getY(), height);
            li_point.push_back(pt);
            centroidx+=ptTemp.getX();
            centroidy+=ptTemp.getY();
        }
    }
    centroidx/=NumberOfExteriorRingVertices-1;
    centroidy/=NumberOfExteriorRingVertices-1;

    Point P;
    P.set_x(centroidx);
    P.set_y(centroidy);
    //setting the Z value w/ Thales relation = Tan(angle)*centroid_distance
    double d;
    double dY=P.get_y()-li_point.at(1).get_y();
    double dX=P.get_x()-li_point.at(1).get_x();
    d = sqrt( dX*dX/dY*dY );
    if (d<0){d*=-1;}//setting value to positive if it's negative
    P.set_z(( height )+( tan(roofAngle)*d ));
    //cout<<d<<endl;
    //cout<<tan(roofAngle)<<endl;
    //cout<<P.get_z()-height<<endl;

    //adding a new building model 'roof' from triangular fronts to those of the building list.
    vector<Triangle> li_triangle;
    Triangle fa(P,li_point.at(1),li_point.at(0),ROOF);
    li_triangle.push_back(fa);
    Triangle fb(P,li_point.at(2),li_point.at(1),ROOF);
    li_triangle.push_back(fb);
    Triangle fc(P,li_point.at(3),li_point.at(2),ROOF);
    li_triangle.push_back(fc);
    Triangle fd(P,li_point.at(0),li_point.at(3),ROOF);
    li_triangle.push_back(fd);

    BuildingModel roof(li_triangle,bu.get_parcel());
    return roof;
}

BuildingModel linear_spine(Building bu, double roofAngle)
{
    vector<Triangle> li_triangle;
    //getting the Buildingmodels
    vector<BuildingModel> bus = bu.get_building_models();

    //getting the exterior ring of the polygon ...
    OGRPolygon* poPoly = bu.get_geom();
    OGRLinearRing* poExteriorRing = (OGRLinearRing*)poPoly->getExteriorRing();
    //setting all the vertices edges of the polygon
    vector<Point> li_point;
    OGRPoint ptTemp;
    int NumberOfExteriorRingVertices = poExteriorRing ->OGRSimpleCurve::getNumPoints();
    for ( int k = 0; k < NumberOfExteriorRingVertices-1; k++)
    {
        poExteriorRing ->getPoint(k,&ptTemp);
        Point pt;
        if (ptTemp.getX()!=0.0 && ptTemp.getY()!=0.0)
        {
            pt= Point(ptTemp.getX(), ptTemp.getY(), bu.get_height());
            li_point.push_back(pt);
        }
    }
    if (NumberOfExteriorRingVertices==5)
    {
        //getting the higher distance edge (lengthwise and crosswise)
        /* if __l1__           else  __l1__
          a...........b              a....b
          .           .   |          . m1 .
        m1.   l1>l2   .m2 l2         .    . |
          .           .   |          .    . l2
          d...........c              .    . |
                                     d....c
                                       m2
        */
        double dx = li_point.at(1).get_x()-li_point.at(0).get_x();
        double dy =li_point.at(1).get_y()-li_point.at(0).get_y();
        double l1 = sqrt(dx*dx+dy*dy);
        dx =li_point.at(1).get_x()-li_point.at(2).get_x();
        dy =li_point.at(1).get_y()-li_point.at(2).get_y();
        double l2 = sqrt(dx*dx+dy*dy);

        Point m1;// setting middle point of width on the left side
        Point m2;//and right side         (with height from angle roof)
        if (l1>l2)//if __l1__>__l2__: m2=c.translate([cb]/2) & m1=d.translate([da]/2),
            {
            m2.set_x( li_point.at(2).get_x() + ( (li_point.at(1).get_x()-li_point.at(2).get_x())/2) );
            m2.set_y( li_point.at(2).get_y() + ( (li_point.at(1).get_y()-li_point.at(2).get_y()) /2) );
            m2.set_z( li_point.at(2).get_z() + ( (li_point.at(1).get_z()-li_point.at(2).get_z()) /2) +(tan(roofAngle)*(l2/2)) );

            m1.set_x( li_point.at(3).get_x() + ( (li_point.at(0).get_x()-li_point.at(3).get_x()) /2) );
            m1.set_y( li_point.at(3).get_y() + ( (li_point.at(0).get_y()-li_point.at(3).get_y()) /2) );
            m1.set_z( li_point.at(3).get_z() + ( (li_point.at(0).get_z()-li_point.at(3).get_z()) /2) +(tan(roofAngle)*(l2/2)));
            Triangle fa(m1,li_point.at(1),li_point.at(0),ROOF);
            li_triangle.push_back(fa);
            Triangle fb(m2,li_point.at(1),m1,ROOF);
            li_triangle.push_back(fb);
            Triangle fc(m2,m1,li_point.at(2),ROOF);
            li_triangle.push_back(fc);
            Triangle fd(m1,li_point.at(3),li_point.at(2),ROOF);
            li_triangle.push_back(fd);

            Triangle fe(m1,li_point.at(0),li_point.at(3),WALL);
            li_triangle.push_back(fe);
            Triangle ff(m2,li_point.at(2),li_point.at(1),WALL);
            li_triangle.push_back(ff);
        }
        //else : m1=a.translate([ab]/2);m2=d.translate([dc]/2)
        else
        {
            m1.set_x( li_point.at(0).get_x() + ( (li_point.at(1).get_x()-li_point.at(0).get_x()) /2) );
            m1.set_y( li_point.at(0).get_y() + ( (li_point.at(1).get_y()-li_point.at(0).get_y()) /2) );
            m1.set_z( li_point.at(0).get_z() + ( (li_point.at(1).get_z()-li_point.at(0).get_z()) /2) +(tan(roofAngle)*(l1/2)) );

            m2.set_x( li_point.at(3).get_x() + ( (li_point.at(2).get_x()-li_point.at(3).get_x()) /2) );
            m2.set_y( li_point.at(3).get_y() + ( (li_point.at(2).get_y()-li_point.at(3).get_y()) /2) );
            m2.set_z( li_point.at(3).get_z() + ( (li_point.at(2).get_z()-li_point.at(3).get_z()) /2) +(tan(roofAngle)*(l1/2)));

            Triangle fa(m1,li_point.at(2),li_point.at(1),ROOF);
            li_triangle.push_back(fa);
            Triangle fb(m2,li_point.at(2),m1,ROOF);
            li_triangle.push_back(fb);
            Triangle fc(m2,m1,li_point.at(3),ROOF);
            li_triangle.push_back(fc);
            Triangle fd(m1,li_point.at(0),li_point.at(3),ROOF);
            li_triangle.push_back(fd);

            Triangle fe(m1,li_point.at(1),li_point.at(0),WALL);
            li_triangle.push_back(fe);
            Triangle ff(m2,li_point.at(3),li_point.at(2),WALL);
            li_triangle.push_back(ff);
        }
    }
    else if (NumberOfExteriorRingVertices==7)
    {
        Point A, B, C;
        double dx = li_point.at(5).get_x()-li_point.at(0).get_x();
        double dy =li_point.at(5).get_y()-li_point.at(0).get_y();
        double lA = sqrt(dx*dx+dy*dy);
        dx = li_point.at(2).get_x()-li_point.at(3).get_x();
        dy =li_point.at(2).get_y()-li_point.at(3).get_y();
        double lC = sqrt(dx*dx+dy*dy);
        double lm=(lA+lC)/2;
        A.set_x( (li_point.at(5).get_x()+li_point.at(0).get_x()) /2);
        A.set_y( (li_point.at(5).get_y()+li_point.at(0).get_y()) /2);
        A.set_z( (li_point.at(5).get_z()+li_point.at(0).get_z()) /2 +(tan(roofAngle)*(lm/2)) );

        B.set_x( (li_point.at(1).get_x()+li_point.at(4).get_x()) /2);
        B.set_y( (li_point.at(1).get_y()+li_point.at(4).get_y()) /2);
        B.set_z( (li_point.at(1).get_z()+li_point.at(4).get_z()) /2 +(tan(roofAngle)*(lm/2)) );

        C.set_x( (li_point.at(2).get_x()+li_point.at(3).get_x()) /2);
        C.set_y( (li_point.at(2).get_y()+li_point.at(3).get_y()) /2);
        C.set_z( (li_point.at(2).get_z()+li_point.at(3).get_z()) /2 +(tan(roofAngle)*(lm/2)) );

        Triangle tri;
        tri=Triangle(A, li_point.at(5), li_point.at(4), ROOF);
        li_triangle.push_back(tri);
        tri=Triangle(B, A, li_point.at(4), ROOF);
        li_triangle.push_back(tri);
        tri=Triangle(B, li_point.at(0), A, ROOF);
        li_triangle.push_back(tri);
        tri=Triangle(li_point.at(1), li_point.at(0), B, ROOF);
        li_triangle.push_back(tri);
        tri=Triangle(li_point.at(1), B, C, ROOF);
        li_triangle.push_back(tri);
        tri=Triangle(li_point.at(2), li_point.at(1), C, ROOF);
        li_triangle.push_back(tri);
        tri=Triangle(li_point.at(4), li_point.at(3), C, ROOF);
        li_triangle.push_back(tri);
        tri=Triangle(li_point.at(4), C, B, ROOF);
        li_triangle.push_back(tri);

        tri=Triangle(li_point.at(0), li_point.at(5), A, WALL);
        li_triangle.push_back(tri);
        tri=Triangle(li_point.at(3), li_point.at(2), C, WALL);
        li_triangle.push_back(tri);
    }

    //adding a new building model 'roof' from triangular fronts to those of the building list.

    BuildingModel roof(li_triangle,bu.get_parcel());
    return roof;
}

BuildingModel linear_cross_spine(Building bu, double roofAngle)
{
    vector<Triangle> li_triangle;
    //getting the Buildingmodels
    vector<BuildingModel> bus = bu.get_building_models();

    //getting the exterior ring of the polygon ...
    OGRPolygon* poPoly = bu.get_geom();
    OGRLinearRing* poExteriorRing = (OGRLinearRing*)poPoly->getExteriorRing();
    //setting all the vertices edges of the polygon
    vector<Point> li_point;
    OGRPoint ptTemp;
    int NumberOfExteriorRingVertices = poExteriorRing ->OGRSimpleCurve::getNumPoints();
    double centroidx =0;
    double centroidy =0;
    for ( int k = 0; k < NumberOfExteriorRingVertices-1; k++)
    {
        poExteriorRing ->getPoint(k,&ptTemp);
        Point* pt;
        if (ptTemp.getX()!=0.0 && ptTemp.getY()!=0.0)
        {
            pt= new Point(ptTemp.getX(), ptTemp.getY(),bu.get_height());
            li_point.push_back(*pt);
            centroidx+=ptTemp.getX();
            centroidy+=ptTemp.getY();
        }
    }
    centroidx/=NumberOfExteriorRingVertices-1;
    centroidy/=NumberOfExteriorRingVertices-1;
    Point P;
    P.set_x(centroidx);
    P.set_y(centroidy);

    //getting the higher distance edge (lengthwise and crosswise)
    // if __l1__           else  __l1__
    //  a...........b              a....b
    //  .           .   |          . m1 .
    //m1.   l1>l2   .m2 l2         .    . |
    //  .           .   |          .    . l2
    //  d...........c              .    . |
    //                             d....c
    //                               m2

    double dx = li_point.at(1).get_x()-li_point.at(0).get_x();
    double dy =li_point.at(1).get_y()-li_point.at(0).get_y();
    double l1 = sqrt(dx*dx+dy*dy);
    dx =li_point.at(1).get_x()-li_point.at(2).get_x();
    dy =li_point.at(1).get_y()-li_point.at(2).get_y();
    double l2 = sqrt(dx*dx+dy*dy);

    Point m1;// setting middle point of width on the left side
    Point m2;//and right side         (with height from angle roof)
    if (l1>l2)//if __l1__>__l2__: m2=c.translate([cb]/2) & m1=d.translate([da]/2)
        {
        m2.set_x( ((li_point.at(1).get_x()+li_point.at(2).get_x())/2  + P.get_x())/2);
        m2.set_y( ((li_point.at(1).get_y()+li_point.at(2).get_y())/2  + P.get_y())/2);
        double dx = m2.get_x()-li_point.at(2).get_x();
        double dy = m2.get_y()-li_point.at(2).get_y();
        double d = sqrt(dx*dx+dy*dy);
        m2.set_z( bu.get_height() + (tan(roofAngle)*d) );

        m1.set_x( ((li_point.at(0).get_x()+li_point.at(3).get_x()) /2 + P.get_x())/2) ;
        m1.set_y( ((li_point.at(0).get_y()+li_point.at(3).get_y()) /2 + P.get_y())/2) ;
        m1.set_z( m2.get_z());

        Triangle fa(m1,li_point.at(1),li_point.at(0),ROOF);
        li_triangle.push_back(fa);
        Triangle fb(m2,li_point.at(1),m1,ROOF);
        li_triangle.push_back(fb);
        Triangle fc(m2,m1,li_point.at(2),ROOF);
        li_triangle.push_back(fc);
        Triangle fd(m1,li_point.at(3),li_point.at(2),ROOF);
        li_triangle.push_back(fd);

        Triangle fe(m1,li_point.at(0),li_point.at(3),ROOF);
        li_triangle.push_back(fe);
        Triangle ff(m2,li_point.at(2),li_point.at(1),ROOF);
        li_triangle.push_back(ff);
        }
    //else : m1=a.translate([ab]/2);m2=d.translate([dc]/2)
    else
    {
        m1.set_x( ((li_point.at(1).get_x()+li_point.at(0).get_x()) /2 +  P.get_x())/2);
        m1.set_y( ((li_point.at(1).get_y()+li_point.at(0).get_y()) /2 +  P.get_y())/2);
        double dx = m1.get_x()-li_point.at(0).get_x();
        double dy = m1.get_y()-li_point.at(0).get_y();
        double d = sqrt(dx*dx+dy*dy);
        m1.set_z( bu.get_height() + (tan(roofAngle)*d) );

        m2.set_z( bu.get_height() + (tan(roofAngle)*d) );
        m2.set_x( ((li_point.at(2).get_x()+li_point.at(3).get_x()) /2 + P.get_x())/2);
        m2.set_y( ((li_point.at(2).get_y()+li_point.at(3).get_y()) /2 + P.get_y())/2);
        m2.set_z( m1.get_z());

        Triangle fa(m1,li_point.at(2),li_point.at(1),ROOF);
        li_triangle.push_back(fa);
        Triangle fb(m2,li_point.at(2),m1,ROOF);
        li_triangle.push_back(fb);
        Triangle fc(m2,m1,li_point.at(3),ROOF);
        li_triangle.push_back(fc);
        Triangle fd(m1,li_point.at(0),li_point.at(3),ROOF);
        li_triangle.push_back(fd);

        Triangle fe(m1,li_point.at(1),li_point.at(0),ROOF);
        li_triangle.push_back(fe);
        Triangle ff(m2,li_point.at(3),li_point.at(2),ROOF);
        li_triangle.push_back(ff);
    }
    return BuildingModel(li_triangle, bu.get_parcel());
}

BuildingModel flat_roof(Building bu)
{
    //getting the exterior ring of the polygon ...
    OGRPolygon* poPoly = bu.get_geom();
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
    vector<Triangle> li_triangle;
    if (NumberOfExteriorRingVertices==5)
    {
        li_triangle.push_back(Triangle(li_point.at(0),li_point.at(2),li_point.at(1),ROOF));
        li_triangle.push_back(Triangle(li_point.at(0),li_point.at(3),li_point.at(2),ROOF));
    }
    else if (NumberOfExteriorRingVertices==7)
    {
        li_triangle.push_back(Triangle(li_point.at(1),li_point.at(0),li_point.at(5),ROOF));
        li_triangle.push_back(Triangle(li_point.at(4),li_point.at(1),li_point.at(5),ROOF));
        li_triangle.push_back(Triangle(li_point.at(2),li_point.at(1),li_point.at(3),ROOF));
        li_triangle.push_back(Triangle(li_point.at(3),li_point.at(1),li_point.at(4),ROOF));
    }
    return BuildingModel(li_triangle, bu.get_parcel());
}

/*
#include "catch.h"
#include "open_shp.h"
#include "Point.h"
#include <fstream>
TEST_CASE("XSkeleton is computed","[crossed_spine]")
{
    int offset(0);
    vector<Road> ROADS;
    vector<Parcel> PARCELS;
    OGRPoint* centroid;
    const char* file_path ="1_data/paris_test/route_secondaire_buffer_2.shp";
    const char* layer_name ="route_secondaire_buffer_2";
    centroid = open_shp_roads(file_path, ROADS, layer_name);
    file_path ="1_data/paris_test/test_paris_seuil_2.shp";
    layer_name ="test_paris_seuil_2";
    open_shp_parcels(file_path, PARCELS, centroid, layer_name);

    OGRGeometry* parcel = PARCELS.at(30).get_geom();
    OGRLineString* v2 = get_intersection_road(parcel,ROADS);
    OGRLineString* v3 = get_other_sides(parcel,v2);
    Footprint v4 = PARCELS.at(30).create_footprint(v2,v3);
    Envelop v5 = v4.create_envelop();
    Building bu = Building(&v5);

    crossed_spine(bu, M_PI/8);
    //linear_spine(bu, M_PI/8);
    vector<string> v = bu.to_obj(centroid,offset);

    ofstream bu_obj("testroof.obj");
    bu_obj << v.at(0) << v.at(1) << v.at(2);
    bu_obj.close();


} */
