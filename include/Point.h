#ifndef POINT_H
#define POINT_H


class Point
{
    /**
    *@class Point
    *Contain the point's coordinates
    */
    public:
        Point();
        /**
        *@fn Point::Point()
        *Simple constructor.
        */
        Point(double p_x, double p_y, double p_z);
        /**
        *@fn Point::Point()
        *Constructor with coordinates parameters.
        *@param[in] p_x double : x coordinate.
        *@param[in] p_y double : y coordinate.
        *@param[in] p_z double : z coordinate.
        */
        virtual ~Point();
        /**
        *@fn virtual Point::Point()
        *Destructor.
        */
        //Getters
        double get_x()const{return x;};
        /**
        *@fn double Point::get_x() const
        *This function allows us to get the x coordinate.
        *@return x double
        */
        double get_y()const{return y;};
        /**
        *@fn double Point::get_y() const
        *This function allows us to get the y coordinate.
        *@return y double
        */
        double get_z()const{return z;};
        /**
        *@fn double Point::get_z() const
        *This function allows us to get the z coordinate.
        *@return z double
        */

        //Other functions
        void translate(double vec[3]);
        /**
        *@fn void Point::translate(double vec[3])
        *This function allows us to translate the point with a 3d vector,
        *update the x, y, z coordiantes.
        *@param[in] vec vector<double> dim 3 : It's a translate vector
        */
        void rotate(double vec[3], double angle);
        /**
        *@fn void Point::rotate(double vec[3], double angle)
        *This function allows us to rotate the point with a rotate axe and a angle,
        *update the x, y, z coordiantes.
        *@param[in] vec vector<double> dim 3 : It's the rotate axe
        *@param[in] angle double : It's a rotate angle [rad]
        */
        void size(double vec[3]);
        /**
        *@fn void Point::size(double vec[3])
        *This function allows us to resize the Point according to an array (the origin is [0, 0, 0]),
        *update the x, y, z coordiantes.
        *@param[in] vec vector<double> dim 3 : ?????
        */

    protected:
    private:
        double x;
        double y;
        double z;
};

bool operator==(Point a, Point b);

#endif // POINT_H
