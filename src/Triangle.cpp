#include "Triangle.h"
#include "Point.h"
#include <vector>
#include <string>

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


/*
Triangle[2] Triangle::split(double axis[3], Point orirgin, string oldName, string newName)
{
    //to fill
}

Triangle Triangle::repeat(string newName)
{
    //to fill
=======
    //delete p1;
    //delete p2;
    //delete p3;
>>>>>>> b09b6814f60911ff2cf67854168a380500d8d474
}
*/
