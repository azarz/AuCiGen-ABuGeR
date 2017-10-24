#ifndef POINT_H
#define POINT_H


class Point
{
    /**
    *@class Point
    *contain the point's coordinates
    */
    public:
        Point();
        /**
        *Simple créator Point()
        */
        Point(double p_x, double p_y, double p_z);
        /**
        *Créator Point()
        *@param[in] p_x double : x coordinate
        *@param[in] p_y double : y coordinate
        *@param[in] p_z double : z coordinate
        */
        virtual ~Point();

        //Getters
        double get_x()const{return x;};
        /**
        *Point::get_x()
        *give the x coordinate
        *@return x double
        */
        double get_y()const{return y;};
        /**
        *Point::get_y()
        *give the y coordinate
        *@return y double
        */
        double get_z()const{return z;};
        /**
        *Point::get_z()
        *give the z coordinate
        *@return z double
        */

        //Other functions
        void translate(double vec[3]);
        void rotate(double vec[3], double angle);
        void size(double vec[3]);

    protected:
    private:
        double x;
        double y;
        double z;
};

bool operator==(Point a, Point b);

#endif // POINT_H
