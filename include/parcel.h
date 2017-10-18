#ifndef PARCEL_H
#define PARCEL_H


class Parcel
{
    public:
        Parcel();
        virtual ~Parcel();
        double C_area();
        double C_area_price();
        double C_floor_price();
        int C_n_floor();
        double C_height();
        void create_footprint();
        double area;
        double area_price;
        double floor_price;
        int n_floor;
        double height;
    protected:
    private:
};

#endif // PARCEL_H
