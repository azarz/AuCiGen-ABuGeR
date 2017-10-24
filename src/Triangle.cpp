#include "Triangle.h"
#include "Point.h"
#include "catch.h"
#include <vector>
#include <string>
#include <cmath>

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

}

void Triangle::add_type(TriangleType newType)
{
    type = newType;
}

void Triangle::translate(double vec[3])
{
    p1.translate(vec);
    p2.translate(vec);
    p3.translate(vec);
}

void Triangle::size(double vec[3])
{
    p1.size(vec);
    p2.size(vec);
    p3.size(vec);
}

void Triangle::rotate(double vec[3], double angle)
{
    p1.rotate(vec, angle);
    p2.rotate(vec, angle);
    p3.rotate(vec, angle);
}

bool Triangle::is_equal(Triangle otherTriangle)
{
    bool b1 = (p1 == otherTriangle.get_p1() && p2 == otherTriangle.get_p2() && p3 == otherTriangle.get_p3());
    bool b2 = (p1 == otherTriangle.get_p1() && p2 == otherTriangle.get_p3() && p3 == otherTriangle.get_p2());
    bool b3 = (p1 == otherTriangle.get_p2() && p2 == otherTriangle.get_p3() && p3 == otherTriangle.get_p1());
    bool b4 = (p1 == otherTriangle.get_p2() && p2 == otherTriangle.get_p1() && p3 == otherTriangle.get_p3());
    bool b5 = (p1 == otherTriangle.get_p3() && p2 == otherTriangle.get_p2() && p3 == otherTriangle.get_p1());
    bool b6 = (p1 == otherTriangle.get_p3() && p2 == otherTriangle.get_p1() && p3 == otherTriangle.get_p2());
    return (b1 || b2 || b3 || b4 || b5 || b6);
}



vector <Triangle> Triangle::split(double axis[3], Point orirgin, TriangleType newName)
{
    //to fill
}

Triangle Triangle::repeat(TriangleType newName)
{
    //to fill
}



/*

TEST_CASE("Triangle constructor + Getters are computed", "[Triangle] [get_p1] [get_p2] [get_p3] [get_type]")
{
    Point a =  Point(2,5,6);
    Point b =  Point(3,9,7);
    Point c =  Point(5,6,8);
    Triangle d = Triangle(a,b,c,WALL);

    REQUIRE(d.get_p1() == a);
    REQUIRE(d.get_p2() == b);
    REQUIRE(d.get_p3() == c);
    REQUIRE(d.get_type() == WALL);
}

TEST_CASE("add_type are computed", "[add_type]")
{
    Point a =  Point(2,5,6);
    Point b =  Point(3,9,7);
    Point c =  Point(5,6,8);
    Triangle d = Triangle(a,b,c,WALL);
    d.add_type(ROOF);

    REQUIRE(d.get_type() == ROOF);
}

TEST_CASE("is_equal are computed", "[is_equal]")
{
    Point a =  Point(2,5,6);
    Point b =  Point(3,9,7);
    Point c =  Point(5,6,8);
    Triangle d = Triangle(a,b,c,WALL);
    Triangle e = Triangle(a,b,c,WALL);

    REQUIRE(d.is_equal(e));
}

TEST_CASE("translate triangle are computed", "[translate]")
{
    Point a =  Point(2,5,6);
    Point b =  Point(3,9,7);
    Point c =  Point(5,6,8);

    Triangle d = Triangle(a,b,c,WALL);

    double vec[3];
    vec[0] = 1;
    vec[1] = 2;
    vec[2] = 3;

    d.translate(vec);

    Point e =  Point(3,7,9);
    Point f =  Point(4,11,10);
    Point g =  Point(6,8,11);

    Triangle h = Triangle(e,f,g,WALL);

    REQUIRE(d.is_equal(h));
}

TEST_CASE("rotate triangle are computed", "[rotate]")
{
    Point a =  Point(2,5,6);
    Point b =  Point(3,9,7);
    Point c =  Point(5,6,8);

    Triangle d = Triangle(a,b,c,WALL);

    double vec[3];
    vec[0] = 0;
    vec[1] = 0;
    vec[2] = 1;

    double angle = M_PI_2;

    d.rotate(vec,angle);

    Point e =  Point(-5,2,6);
    Point f =  Point(-9,3,7);
    Point g =  Point(-6,5,8);

    Triangle h = Triangle(e,f,g,WALL);

    //REQUIRE(d.is_equal(h));
}

TEST_CASE("size triangle are computed", "[size]")
{
    Point a =  Point(2,5,6);
    Point b =  Point(3,9,7);
    Point c =  Point(5,6,8);

    Triangle d = Triangle(a,b,c,WALL);

    double vec[3];
    vec[0] = 1;
    vec[1] = 2;
    vec[2] = 3;

    d.size(vec);

    Point e =  Point(2,10,18);
    Point f =  Point(3,18,21);
    Point g =  Point(5,12,24);

    Triangle h = Triangle(e,f,g,WALL);

    REQUIRE(d.is_equal(h));

}
*/
