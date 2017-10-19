#ifndef PARCEL_H
#define PARCEL_H


class Parcel
{
    public:
        Parcel();
        virtual ~Parcel();
        void create_footprint();
        double area;
        double area_price;
        double floor_price;
    protected:
    private:
};

#endif // PARCEL_H
