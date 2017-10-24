#include "Point.h"

#include "catch.h"
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
    std::cout << ytemp << std::endl;

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


/*

TEST_CASE("Point constructor + Getter","[Point] [get_x] [get_y] [get_z]")
{
    Point a =  Point(2,5,6);
    Point b =  Point(3,9,7);

    REQUIRE(a.get_x()==2.0);
    REQUIRE(a.get_y()==5.0);
    REQUIRE(a.get_z()==6.0);
    REQUIRE(b.get_x()==3.0);
    REQUIRE(b.get_y()==9.0);
    REQUIRE(b.get_z()==7.0);
}

TEST_CASE("operator == are computed","[opertator==]")
{
    Point a =  Point(2,5,6);
    Point b =  Point(3,9,7);
    Point c =  Point(5,6,8);

    REQUIRE(a==a);
    REQUIRE(b==b);
    REQUIRE(!(c==a));
}

TEST_CASE("translate are computed","[translate]")
{
    Point a =  Point(2,5,6);
    double vec[3];
    vec[0] = 1;
    vec[1] = 2;
    vec[2] = 3;
    a.translate(vec);

    REQUIRE(a.get_x()==3.0);
    REQUIRE(a.get_y()==7.0);
    REQUIRE(a.get_z()==9.0);
}

TEST_CASE("rotate are computed", "[rotate]")
{
    Point a = Point(1,-1,2);
    double vec[3];
    vec[0] = 0;
    vec[1] = 0;
    vec[2] = 1;
    double angle =  M_PI_2l;
    a.rotate(vec,angle);

    REQUIRE(a.get_x()==1.0);
    //REQUIRE(a.get_y()==sin(M_PI_2l)*1*1);
    REQUIRE(a.get_z()==2.0);
}

TEST_CASE("size are computed", "[size]")
{
    Point a = Point(2,5,6);
    double vec[3];
    vec[0] = 1;
    vec[1] = 2;
    vec[2] = 3;
    a.size(vec);

    REQUIRE(a.get_x()==2.0);
    REQUIRE(a.get_y()==10.0);
    REQUIRE(a.get_z()==18.0);
}
/*
