#include "create_env_roof.h"
#include "BuildingModel.h"
#include "ogrsf_frmts.h"
#include "Point.h"
#include "Triangle.h"

void create_env_roof(double height, vector<Triangle>& li_tri)
{
    unsigned int size = li_tri.size();
    for (unsigned int i=0U; i<size; i+=1)
    {
        Triangle triangle = li_tri.at(i);
        Point P1 = triangle.get_p1();
        Point P2 = triangle.get_p3();
        Point P3 = triangle.get_p2();

        Point newP1 = Point(P1.get_x(), P1.get_y(), height);
        Point newP2 = Point(P2.get_x(), P2.get_y(), height);
        Point newP3 = Point(P3.get_x(), P3.get_y(), height);

        Triangle tri1 = Triangle(newP1, newP2, newP3, ROOF);
        li_tri.push_back(tri1);
    }
}
