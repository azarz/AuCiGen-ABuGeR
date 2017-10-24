#include "Point.h"
#include <cmath>
#define PI 3.14159265

Point::Point()
{
}
Point::Point(double p_x, double p_y, double p_z)
{
    //ctor
    x= p_x;
    y= p_y;
    z= p_z;
}

Point::~Point()
{
    //dtor
}

bool operator==(Point a, Point b)
{
    return (a.get_x() == b.get_x() && a.get_y() == b.get_y() && a.get_z() == b.get_z());
}

void Point::translate(double vec[3])
{
    x += vec[0];
    y += vec[1];
    z += vec[2];
}

void Point::rotate(double vec[3], double angle)
{
    double c = cos(angle * PI / 180.0);
    double s = sin(angle * PI / 180.0);
    double xtemp = (vec[0]*vec[0]*2*(1-c)+c)*x + (vec[0]*vec[1]*(1-c)-vec[2]*s)*y + (vec[0]*vec[2]*(1-c)+vec[2]*s)*z;
    double ytemp = (vec[1]*vec[1]*2*(1-c)+c)*y + (vec[0]*vec[1]*(1-c)+vec[2]*s)*x + (vec[1]*vec[2]*(1-c)-vec[2]*s)*z;
    double ztemp = (vec[2]*vec[2]*2*(1-c)+c)*z + (vec[0]*vec[2]*(1-c)-vec[2]*s)*x + (vec[1]*vec[2]*(1-c)+vec[2]*s)*y;
    x = xtemp;
    y = ytemp;
    z = ztemp;
}

void Point::size(double vec[3])
{
    x *= vec[0];
    y *= vec[1];
    z *= vec[2];
}








