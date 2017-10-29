#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;


enum TriangleType{
WALL,
FLOOR,
ROOF
};


class Triangle
{
    /**
    *@class Triangle
    *Contain a Triangle.
    */
    public:

        Triangle();
        /**
        *@fn Triangle::Triangle()
        *Constructor.
        */

        Triangle(Point T_p1, Point T_p2, Point T_p3, TriangleType T_type);
        /**
        *@fn Triangle::Triangle(Point T_p1, Point T_p2, Point T_p3, TriangleType T_type)
        *Constructor with arguments.
        */

        virtual ~Triangle();
        /**
        *@fn virtual Triangle::~Triangle()
        *Destructor.
        */

        //Getters
        TriangleType get_type()const{return type;};
        /**
        *@fn TriangleType Triangle::get_type() const
        *This function allows us to get the TriangleType of the Triangle.
        *@return The TriangleType of the Triangle.
        */

        Point get_p1()const{return p1;};
        /**
        *@fn Point Triangle::get_p1() const
        *This function allows us to get the the first Point of the Triangle.
        *@return The first Point of the Triangle.
        */

        Point get_p2()const{return p2;};
        /**
        *@fn Point Triangle::get_p2() const
        *This function allows us to get the second Point of the Triangle.
        *@return The second Point of the Triangle.
        */

        Point get_p3()const{return p3;};
        /**
        *@fn Point Triangle::get_p3() const
        *This function allows us to get the third Point of the Triangle.
        *@return The third Point of the Triangle.
        */

        void add_type(TriangleType newType);
        /**
        *@fn void Triangle::add_type(TriangleType newType)
        *This function allows us to set the TriangleType of the Triangle.
        *@param[in] newType : The TriangleType of the Triangle.
        */

        bool is_equal(Triangle otherTriangle);
        /**
        *@fn bool Triangle::is_equal(Triangle otherTriangle)
        *This function allows us to check the equality between two Triangle.
        *@param[in] otherTriangle : The other Triangle to compare.
        *@return The boolean of this equality.
        */

        void translate(double vec[3]);
        /**
        *@fn void Triangle::translate(double vec[3])
        *This function allows us to translate the Triangle according to an array.
        *@param[in] vec : It's the axis of the rotation.
        */

        void rotate(double vec[3], double angle);
        /**
        *@fn void Triangle::rotate(double vec[3], double angle)
        *This function allows us to rotate the Triangle according to an axis and an angle of rotation (the origin is [0, 0, 0]).
        *@param[in] vec : It's the axis of the rotation.
        *@param[in] angle : It's the angle of rotation.
        */

        void size(double vec[3]);
        /**
        *@fn void Triangle::size(double vec[3])
        *This function allows us to resize the Triangle according to an array (the origin is [0, 0, 0]).
        *@param[in] vec : It's the axis of the rotation.
        */

        vector <Triangle> split(double axis[3], Point origin, TriangleType newName);
        /**
        *@fn vector <Triangle> Triangle::split(double axis[3], Point origin, TriangleType newName)
        *This function allows us to split the Triangle according to an axis and a origin point.
        *@param[in] axis : It's the axis of the split.
        *@param[in] origin : It's the origin point of the split (to fix the axis in the 3D dimension).
        *@param[in] newName : It's the new type of the Triangle.
        *@return The list of triangle from the split
        */

        //Triangle repeat(TriangleType newName);
        /**
        *@fn Triangle Triangle::repeat(TriangleType newName)
        *This function allows us to repeat/copy the triangle.
        *@param[in] newName : It's the new type of the Triangle.
        *@return
        */

        //void scope();
        /**
        *@fn void Triangle::scope()
        *This function allows us to avoid the hidden walls inside buildingmodel.
        */

        //BuildingModel creat_roof();
        /**
        *@fn BuildingModel Triangle::creat_roof()
        *This function allows us to create a roof.
        *@return
        */

    protected:
    private:
        TriangleType type; //wall, floor, roof
        Point p1;
        Point p2;
        Point p3;
};

#endif // TRIANGLE_H
