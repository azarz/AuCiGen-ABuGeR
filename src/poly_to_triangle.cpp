#include "poly_to_triangle.h"
#include "Triangle.h"
#include "ogrsf_frmts.h"
#include "Point.h"
#include <ogr_geometry.h>
#include <iostream>
//#include "catch.h"
using namespace std;

void poly_to_triangle(OGRPolygon* poPolygon, vector<Triangle>& li_vector, TriangleType type)
{
    vector<Point> li_point;
    OGRPoint ptTemp;
    //int NumberOfInnerRings = poPolygon ->getNumInteriorRings();
    OGRLinearRing* poExteriorRing = (OGRLinearRing*)poPolygon->Boundary();
    int NumberOfExteriorRingVertices = poExteriorRing ->OGRSimpleCurve::getNumPoints();
    for ( int k = 0; k < NumberOfExteriorRingVertices-1; k++)//NumberOfExteriorRingVertices; k++ )
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
    //cout << "nomber points" << NumberOfExteriorRingVertices-1 <<endl;
    unsigned int i=0U;
    /*for (int k=0; k<li_point.size(); k++)
    {
        cout << li_point.at(k).get_x() << endl;
    }*/

    Triangle* tri;
    while (li_point.size()>=3)
    {
        if (i>=li_point.size())
        {
            i=0;
        }
        //double a= li_point.at(i).get_x();
        OGRPoint p1 = OGRPoint(li_point.at(i).get_x(), li_point.at(i).get_y(), li_point.at(i).get_z());
        //OGRPoint p1 = OGRPoint(a, a, a);
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
        //OGRGeometry* g_tri = (OGRGeometry * ) triangle;
        //cout << i<<", "<< j <<", "<< k <<  " / " << li_point.size() << "test : " << poPolygon->OGRCurvePolygon::Contains(&triangle) << "   "<< li_vector.size() << endl;
        if (poPolygon->OGRCurvePolygon::Contains(&triangle))
        {
            //cout << li_point.at(i).get_x()<<endl;
            OGRLinearRing* triangle_trace = (OGRLinearRing*)triangle.Boundary();
            if (!triangle_trace->isClockwise())
                tri = new Triangle(li_point.at(i), li_point.at(j), li_point.at(k), type);
            else
                tri = new Triangle(li_point.at(k), li_point.at(j), li_point.at(i), type);
            li_vector.push_back(*tri);
            li_point.erase(li_point.begin()+j);
        }
        else
        {
        i++;
        }
    }/**/
    //cout << "in : "<<li_vector.at(0).get_p2().get_x()<<endl;
    //cout << "in : "<<li_vector.at(2).get_p2()->get_x()<<endl;
}


/*TEST_CASE("poly_to_triangle are computed","[poly_to_triangle]")
{
    vector<Parcel> PARCELS;
    char* fill_directory ="1_data/test/test_parcel.shp";
    OpenShapeFile_parcels(fill_directory, PARCELS);
    vector<Triangle> li_vector;
    poly_to_triangle(PARCELS.at(7).get_geom(), li_vector );
    REQUIRE(li_vector.at(0).get_type()==FLOOR);
    REQUIRE(li_vector.size()==30);

}*/
