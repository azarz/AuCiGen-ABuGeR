#include "create_wall.h"
#include "BuildingModel.h"
#include "ogrsf_frmts.h"
#include "Point.h"
#include "Triangle.h"

void create_wall(OGRPolygon* poPolygon, double height, vector<Triangle>& li_tri)
{
    vector<Point> li_point;
    OGRPoint ptTemp;
    //int NumberOfInnerRings = poPolygon ->getNumInteriorRings();
    OGRLinearRing *poExteriorRing = poPolygon ->getExteriorRing();
    int NumberOfExteriorRingVertices = poExteriorRing ->OGRSimpleCurve::getNumPoints();
    cout << "NumberOfExteriorRingVertices "<<NumberOfExteriorRingVertices<<endl;
    if (poExteriorRing ->isClockwise())
    {
        for ( int k = 0; k < NumberOfExteriorRingVertices; k++)//NumberOfExteriorRingVertices; k++ )
        {
            poExteriorRing ->getPoint(k,&ptTemp);
            Point* pt;
            if (ptTemp.getX()!=0.0 && ptTemp.getY()!=0.0)
            {
                pt= new Point(ptTemp.getX(), ptTemp.getY(), 0.0);
                //printf("%.10f, %.10f\n", ptTemp.getX(), ptTemp.getY());
                li_point.push_back(*pt);
            }
        }
    }
    else
    {
        for ( int k = NumberOfExteriorRingVertices-1; k <= 0; k--)//NumberOfExteriorRingVertices; k++ )
        {
            poExteriorRing ->getPoint(k,&ptTemp);
            Point* pt;
            if (ptTemp.getX()!=0.0 && ptTemp.getY()!=0.0)
            {
                pt= new Point(ptTemp.getX(), ptTemp.getY(), 0.0);
                //printf("%.10f, %.10f\n", ptTemp.getX(), ptTemp.getY());
                li_point.push_back(*pt);
            }
        }
    }
    //cout << "nomber points" << NumberOfExteriorRingVertices-1 <<endl;
    //int i=0;

    for (int i=0; i<li_point.size()-1; i++)
    {
        Point P1 = li_point.at(i);
        Point P2 = li_point.at(i+1);
        Point P3 = Point(P2.get_x(), P2.get_y(), P2.get_z()+height);
        Point P4 = Point(P1.get_x(), P1.get_y(), P1.get_z()+height);
        Triangle tri1 = Triangle(P3, P2, P1, WALL);
        Triangle tri2 = Triangle(P4, P3, P1, WALL);
        li_tri.push_back(tri1);
        li_tri.push_back(tri2);
    }
}
/*
#include "catch.h"

TEST_CASE("creat_wall are computed","[creat_wall]")
{
    char * wkt = "POLYGON ((55.4678416936841 -21.3283219559282, 55.4678375166117 -21.3283189126795, 55.467812437186 -21.3283006408084, 55.4680106001766 -21.3280669525981, 55.468037199703 -21.328085230485, 55.4678416936841 -21.3283219559282))";
    OGRPolygon poPolygon= OGRPolygon();
    poPolygon.OGRPolygon::importFromWkt( &wkt);
    vector<Triangle> li_tri;
    creat_wall(&poPolygon, 4, li_tri);
    REQUIRE(li_tri.size()==10);
    REQUIRE(li_tri.at(0).get_p1().get_x()==55.4678375166117);
    REQUIRE(li_tri.at(0).get_p1().get_y()==-21.3283189126795);
    REQUIRE(li_tri.at(0).get_p1().get_z()==4);
    REQUIRE(li_tri.at(0).get_p2().get_x()==55.4678375166117);
    REQUIRE(li_tri.at(0).get_p2().get_y()==-21.3283189126795);
    REQUIRE(li_tri.at(0).get_p2().get_z()==0);
    REQUIRE(li_tri.at(0).get_p3().get_x()==55.4678416936841);
    REQUIRE(li_tri.at(0).get_p3().get_y()==-21.3283219559282);
    REQUIRE(li_tri.at(0).get_p3().get_z()==0);

}
*/
