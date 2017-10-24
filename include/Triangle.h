#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
enum TriangleType{
WALL,
FLOOR,
ROOF
};
*/

class Triangle
{
    public:
        Triangle(Point* T_p1, Point* T_p2, Point* T_p3, vector<string> T_type);
        virtual ~Triangle();

        //Getters
        vector<string> get_type()const{return type;};
        Point* get_p1()const{return p1;};
        Point* get_p2()const{return p2;};
        Point* get_p3()const{return p3;};

        void add_type(string newType);

        void translate(double vec[3]);
        void rotate(double vec[3], double angle);
        void size(double vec[3]);

        bool is_equal(Triangle otherTriangle);

        //Triangle[2] split(double axis[3], Point orirgin, string oldName, string newName);
        //void repeat(string newName);
        //void scope();

        //BuildingModel creat_roof();



    protected:
    private:
        vector<string> type; //wall, floor, roof
        Point* p1;
        Point* p2;
        Point* p3;
};

#endif // TRIANGLE_H
