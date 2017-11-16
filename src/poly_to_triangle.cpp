#include "poly_to_triangle.h"

#include "Triangle.h"
#include "ogrsf_frmts.h"
#include "Point.h"
#include <ogr_geometry.h>
#include <iostream>

using namespace std;

void poly_to_triangle(OGRPolygon* poPolygon, vector<Triangle>& li_vector, TriangleType type)
{
    vector<Point> li_point;
    OGRPoint ptTemp;
    OGRLinearRing* poExteriorRing = (OGRLinearRing*)poPolygon->getExteriorRing();
    int NumberOfExteriorRingVertices = poExteriorRing ->OGRSimpleCurve::getNumPoints();
    for ( int k = 0; k < NumberOfExteriorRingVertices-1; k++)//NumberOfExteriorRingVertices; k++ )
    {
        poExteriorRing ->getPoint(k,&ptTemp);
        Point* pt;
        if (ptTemp.getX()!=0.0 && ptTemp.getY()!=0.0)
        {
            pt= new Point(ptTemp.getX(), ptTemp.getY(), 0.0);
            li_point.push_back(*pt);
        }
    }
    unsigned int i=0U;
    Triangle* tri;
    int counter(0);
    while (li_point.size()>=3)
    {
        if (i>=li_point.size())
        {
            i=0;
            counter++;
        }
        OGRPoint p1 = OGRPoint(li_point.at(i).get_x(), li_point.at(i).get_y(), li_point.at(i).get_z());
        unsigned int j=i+1;
        if (j>=li_point.size())
        {
            j=j-li_point.size();
        }
        OGRPoint p2 =OGRPoint(li_point.at(j).get_x(), li_point.at(j).get_y(), li_point.at(j).get_z());
        unsigned int k=i+2;
        if (k>=li_point.size())
        {
            k=k-li_point.size();
        }
        OGRPoint p3 =OGRPoint(li_point.at(k).get_x(), li_point.at(k).get_y(), li_point.at(k).get_z());
        OGRTriangle triangle =	OGRTriangle(p1,p2,p3);
        if (poPolygon->OGRCurvePolygon::Contains(&triangle) || counter>=3)
        {
            OGRLinearRing* triangle_trace = (OGRLinearRing*)triangle.getExteriorRing();
            if (!triangle_trace->isClockwise())
            {
                tri = new Triangle(li_point.at(i), li_point.at(j), li_point.at(k), type);
            }
            else
            {
                tri = new Triangle(li_point.at(k), li_point.at(j), li_point.at(i), type);
            }
            li_vector.push_back(*tri);
            li_point.erase(li_point.begin()+j);
        }
        else
        {
        i++;
        }
    }
}
