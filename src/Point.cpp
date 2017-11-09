#include "Point.h"

#include <iostream>
#include <cmath>

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

void Point::print()
{
    std::cout<<x<<", "<<y<<", "<<z<<std::endl;
}

void Point::translate(double vec[3])
{
    x += vec[0];
    y += vec[1];
    z += vec[2];
}

void Point::rotate(double vec[3], double angle)
{
    double c = cos(angle);
    double s = sin(angle);

    //normalisation de vec
    double ux = sqrt(vec[0]*vec[0]/(vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2]));
    double uy = sqrt(vec[1]*vec[1]/(vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2]));
    double uz = sqrt(vec[2]*vec[2]/(vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2]));
    double xtemp = (ux*ux*(1-c)+c)*x + (ux*uy*(1-c)-uz*s)*y + (ux*uz*(1-c)+uy*s)*z;
    double ytemp = (uy*uy*(1-c)+c)*y + (ux*uy*(1-c)+uz*s)*x + (uy*uz*(1-c)-ux*s)*z;
    double ztemp = (uz*uz*(1-c)+c)*z + (ux*uz*(1-c)-uy*s)*x + (uy*uz*(1-c)+ux*s)*y;

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
