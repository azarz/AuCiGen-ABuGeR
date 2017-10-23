#include "Triangle.h"

Triangle::Triangle()
{
}
Triangle::Triangle(Point T_p1, Point T_p2, Point T_p3, TriangleType T_type)
{
    type= T_type; //wall, floor, roof
    p1=T_p1;
    p2=T_p2;
    p3=T_p3;
}

Triangle::~Triangle()
{
    //delete p1;
    //delete p2;
    //delete p3;
}
