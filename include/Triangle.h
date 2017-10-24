#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point.h"
#include <iostream>

using namespace std;

enum TriangleType{
WALL,
FLOOR,
ROOF
};

class Triangle
{
    public:
        Triangle();
        Triangle(Point T_p1, Point T_p2, Point T_p3, TriangleType T_type);
        virtual ~Triangle();

        //Getters
        TriangleType get_type()const{return type;};
        Point get_p1()const{return p1;};
        Point get_p2()const{return p2;};
        Point get_p3()const{return p3;};

    protected:
    private:
        TriangleType type; //wall, floor, roof
        Point p1;
        Point p2;
        Point p3;
};

#endif // TRIANGLE_H
