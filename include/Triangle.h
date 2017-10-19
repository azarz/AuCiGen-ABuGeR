#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point.h"
#include <iostream>

using namespace std;

class Triangle
{
    public:
        Triangle();
        virtual ~Triangle();



        string type; //wall, floor, roof
        Point *p1;
        Point *p2;
        Point *p3;
    protected:
    private:
};

#endif // TRIANGLE_H
