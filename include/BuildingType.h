#ifndef BUILDINGTYPE_H
#define BUILDINGTYPE_H

#include <vector>
#include <iostream>
using namespace std;

class BuildingType
{
    public:
        BuildingType();
        virtual ~BuildingType();

        double get_profitability();
        double get_height(double n_floor);
        std::vector<int> get_surface_type();
        std::vector<double> get_margin();

        virtual void set_param() = 0;

        // Getters
        double get_profitability()const{return profitability;};
        double get_floor_height()const{return floor_height;};
        double get_gap()const{return gap;}; //height between the 0floor and the 1floor
        int get_roof()const{return roof;};
        int get_wall()const{return wall;};
        int get_floor()const{return floor;};
        double get_margin_parcel()const{return margin_parcel;};
        double get_margin_road()const{return margin_road;};

    protected:
        double profitability;
        double floor_height;
        double gap; //height between the 0floor and the 1floor
        int roof;
        int wall;
        int floor;
        double margin_parcel;
        double margin_road;
    private:
};

class Industry: public BuildingType
{
    public:
        Industry();
        void set_param();
    protected:
    private:
};
class Office: public BuildingType
{
    public:
        Office();
        void set_param();
    protected:
    private:
};
class ApartmentBuilding: public BuildingType
{
    public:
        ApartmentBuilding();
        void set_param();
    protected:
    private:
};
class Villa: public BuildingType
{
    public:
        Villa();
        void set_param();
    protected:
    private:
};
class Townhouse: public BuildingType
{
    public:
        Townhouse();
        void set_param();
    protected:
    private:
};
#endif // BUILDINGTYPE_H

