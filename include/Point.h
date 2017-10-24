#ifndef POINT_H
#define POINT_H


class Point
{
    public:
        Point();
        Point(double p_x, double p_y, double p_z);
        virtual ~Point();

        //Getters
        double get_x()const{return x;};
        double get_y()const{return y;};
        double get_z()const{return z;};

    protected:
    private:
        double x;
        double y;
        double z;
};

#endif // POINT_H
