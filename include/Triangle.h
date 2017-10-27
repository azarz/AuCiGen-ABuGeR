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
    public:

        Triangle();
        /**
        * Constructor.
        */

        Triangle(Point T_p1, Point T_p2, Point T_p3, TriangleType T_type);
        /**
        * Constructor with arguments.
        */

        virtual ~Triangle();
        /**
        * Destructor.
        */

        //Getters
        TriangleType get_type()const{return type;};
        /**
        * This function allows us to get the TriangleType of the Triangle.
        * @return The TriangleType of the Triangle.
        */

        Point get_p1()const{return p1;};
        /**
        * This function allows us to get the the first Point of the Triangle.
        * @return The first Point of the Triangle.
        */

        Point get_p2()const{return p2;};
        /**
        * This function allows us to get the second Point of the Triangle.
        * @return The second Point of the Triangle.
        */

        Point get_p3()const{return p3;};
        /**
        * This function allows us to get the third Point of the Triangle.
        * @return The third Point of the Triangle.
        */

        void add_type(TriangleType newType);
        /**
        * This function allows us to set the TriangleType of the Triangle.
        * @param[in] newType The TriangleType of the Triangle.
        */

        bool is_equal(Triangle otherTriangle);
        /**
        * This function allows us to check the equality between two Triangle.
        * @param[in] otherTriangle The other Triangle to compare.
        * @return The boolean of this equality.
        */

        void translate(double vec[3]);
        /**
        * This function allows us to translate the Triangle according to an array.
        * @param[in] vec It's the axis of the rotation.
        */

        void rotate(double vec[3], double angle);
        /**
        * This function allows us to rotate the Triangle according to an axis and an angle of rotation (the origin is [0, 0, 0]).
        * @param[in] vec It's the axis of the rotation.
        * @param[in] angle It's the angle of rotation.
        */

        void size(double vec[3]);
        /**
        * This function allows us to resize the Triangle according to an array (the origin is [0, 0, 0]).
        * @param[in] vec It's the axis of the rotation.
        */

        vector <Triangle> split(double axis[3], Point origin, TriangleType newName);
        /**
        * This function allows us to split the Triangle according to an axis and a origin point.
        * @param[in] axis It's the axis of the split.
        * @param[in] origin It's the origin point of the split (to fix the axis in the 3D dimension).
        * @param[in] newName It's the new type of the Triangle.
        */

        //Triangle repeat(TriangleType newName);
        /**
        * This function allows us to repeat/copy the triangle.
        * @param[in] newName It's the new type of the Triangle.
        */

        //void scope();
        /**
        * This function allows us to avoid the hidden walls inside buildingmodel.
        */

        //BuildingModel creat_roof();
        /**
        * This function allows us to create a roof.
        */

    protected:
    private:
        TriangleType type; //wall, floor, roof
        Point p1;
        Point p2;
        Point p3;
};

#endif // TRIANGLE_H
