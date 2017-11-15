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
    if (poExteriorRing ->isClockwise())
    {
        for ( int k = 0; k < NumberOfExteriorRingVertices; k++)//NumberOfExteriorRingVertices; k++ )
        {
            poExteriorRing ->getPoint(k,&ptTemp);
            Point pt;
            //if (ptTemp.getX()!=0.0 && ptTemp.getY()!=0.0)
            //{
                pt = Point(ptTemp.getX(), ptTemp.getY(), 0.0);
                //printf("%.10f, %.10f\n", ptTemp.getX(), ptTemp.getY());
                li_point.push_back(pt);
            //}
        }
    }
    else
    {
        for ( int k = NumberOfExteriorRingVertices-1; k >= 0; k--)//NumberOfExteriorRingVertices; k++ )
        {
            poExteriorRing ->getPoint(k,&ptTemp);
            Point pt;
            //if (ptTemp.getX()!=0.0 && ptTemp.getY()!=0.0)
            //{
                pt = Point(ptTemp.getX(), ptTemp.getY(), 0.0);
                //printf("%.10f, %.10f\n", ptTemp.getX(), ptTemp.getY());
                li_point.push_back(pt);
            //}
        }
    }
    //cout << "nomber points" << NumberOfExteriorRingVertices <<endl;
    //cout << "nomber points" <<  li_point.size() <<endl;
    //int i=0;

    for (unsigned int i=0U; i<li_point.size()-1; i+=1)
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
