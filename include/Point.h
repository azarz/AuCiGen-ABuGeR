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
        *@param[in] p_x double: x coordinate.
        *@param[in] p_y double: y coordinate.
        *@param[in] p_z double: z coordinate.
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
        *Gets the x coordinate.
        *@return x double
        */
        double get_y()const{return y;};
        /**
        *@fn double Point::get_y() const
        *Gets the y coordinate.
        *@return y double
        */
        double get_z()const{return z;};
        /**
        *@fn double Point::get_z() const
        *Gets the z coordinate.
        *@return z double
        */
        //Setters
        void set_x(double p_x){x=p_x;};
        /**
        *@fn void Point::set_x()
        *Sets the x coordinate.
        *@param[in] p_x double
        */
        void set_y(double p_y){y=p_y;};
        /**
        *@fn void Point::set_y()
        *Sets the y coordinate.
        *@param[in] p_y double
        */
        void set_z(double p_z){z=p_z;};
        /**
        *@fn void Point::set_z()
        *Sets the z coordinate.
        *@param[in] p_z double
        */

        void print();
        /**
        *@fn void Point::print()
        *Print the coordinates of the point.
        */

        //Other functions
        void translate(double vec[3]);
        /**
        *@fn void Point::translate(double vec[3])
        *Translates the point with a 3d vector,
        *updates the x, y, z coordiantes.
        *@param[in] vec vector<double> dim 3: Translation vector
        */
        void rotate(double vec[3], double angle);
        /**
        *@fn void Point::rotate(double vec[3], double angle)
        *Rotates the point with a rotate axis and a angle,
        *updates the x, y, z coordinates.
        *@param[in] vec vector<double> dim 3: Rotation axis
        *@param[in] angle double: Rotation angle [rad]
        */
        void size(double vec[3]);
        /**
        *@fn void Point::size(double vec[3])
        *Resizes the Point according to an array (the origin is [0, 0, 0]),
        *updates the x, y, z coordinates.
        *@param[in] vec vector<double> dim 3: WTF IS RESIZING A POINT ??????
        */

    protected:
    private:
        double x;
        double y;
        double z;
};

bool operator==(Point a, Point b);

#endif // POINT_H
