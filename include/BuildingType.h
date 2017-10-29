#ifndef BUILDINGTYPE_H
#define BUILDINGTYPE_H

#include <vector>
#include <iostream>
using namespace std;

class BuildingType
{
    /**
    *@class BuildingType
    *Contain the generality for all building type.
    */
    public:
        BuildingType();
        /**
        *@fn BuildingType::BuildingType()
        *Constructor.
        */
        virtual ~BuildingType();
        /**
        *@fn virtual BuildingType::~BuildingType()
        *Destructor.
        */

        double get_height(double n_floor);
        /**
        *@fn double BuildingType::get_height(double n_floor)
        *This function allows us to calculate the height of the building without roof.
        @param[in] n_floor : It's the number of floor.
        *@return building_height double
        */

        virtual void set_param() = 0;
        /**
        *@fn virtual void BuildingType::set_param() = 0
        *This function allows us to set the parameter to zero.
        */

        std::vector<double> get_margin();
        /**
        *@fn std::vector<double> BuildingType::get_margin()
        *This function allows us to get the two type of margin between the building and the
        *parcel borders [m].
        *@return [margin_parcel, margin_road] std::vector<double>
        */

        // Getters
        double get_profitability()const{return profitability;};
        /**
        *@fn double BuildingType::get_profitability() const
        *This function allows us to get the profitability price [€/m2].
        *@return profitability double
        */

        double get_floor_height()const{return floor_height;};
        /**
        *@fn double BuildingType::get_floor_height() const
        *This function allows us to get the height for one floor [m].
        *@return floor_height double
        */

        double get_gap()const{return gap;};
        /**
        *@fn double BuildingType::get_gap() const
        *This function allows us to get the height betwen the 1st floor and the second floor.
        *@return gap double
        */

        int get_roof()const{return roof;};
        /**
        *@fn int BuildingType::get_roof() const
        *This function allows us to get the roof type for the building.
        *@return roof int
        */

        int get_wall()const{return wall;};
        /**
        *@fn int BuildingType::get_wall() const
        *This function allows us to get the wall type for the building.
        *@return wall int
        */

        int get_floor()const{return floor;};
        /**
        *@fn int BuildingType::get_floor() const
        *This function allows us to get the floor type for the building.
        *@return floor int
        */

        double get_margin_parcel()const{return margin_parcel;};
        /**
        *@fn double BuildingType::get_margin_parcel() const
        *This function allows us to get the margin between the building and the parcel.
        *border without road [m]
        *@return margin_parcel double
        */

        double get_margin_road()const{return margin_road;};
        /**
        *@fn double BuildingType::get_margin_road() const
        *This function allows us to get the margin between the building and the parcel.
        *border with road [m]
        *@return margin_road double
        */

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
    /**
    *@class Industry: public BuildingType
    *Contain the generality for all building type.
    */
    public:
        Industry();
        /**
        *@fn Industry::Industry()
        *Constructor.
        */
        void set_param();
        /**
        *@fn void Industry::set_param()
        *Set the value to the parameter.
        */
    protected:
    private:
};
class Office: public BuildingType
{
    /**
    *@class Office: public BuildingType
    *Contain the generality for all building type.
    */
    public:
        Office();
        /**
        *@fn Office::Office()
        *Constructor.
        */
        void set_param();
        /**
        *@fn void Office::set_param()
        *Set the value to the parameter.
        */
    protected:
    private:
};
class ApartmentBuilding: public BuildingType
{
    /**
    *@class ApartmentBuilding: public BuildingType
    *Contain the generality for all building type.
    */
    public:
        ApartmentBuilding();
        /**
        *@fn ApartmentBuilding::ApartmentBuilding()
        *Constructor.
        */
        void set_param();
        /**
        *@fn void ApartmentBuilding::set_param()
        *Set the value to the parameter.
        */
    protected:
    private:
};
class Villa: public BuildingType
{
    /**
    *@class Villa: public BuildingType
    *Contain the generality for all building type.
    */
    public:
        Villa();
        /**
        *@fn Villa::Villa()
        *Constructor.
        */
        void set_param();
        /**
        *@fn void Villa::set_param()
        *Set the value to the parameter.
        */
    protected:
    private:
};
class Townhouse: public BuildingType
{
    /**
    *@class Townhouse: public BuildingType
    *Contain the generality for all building type.
    */
    public:
        Townhouse();
        /**
        *@fn Townhouse::Townhouse()
        *Constructor.
        */
        void set_param();
        /**
        *@fn Townhouse::void set_param()
        *Set the value to the parameter.
        */
    protected:
    private:
};
#endif // BUILDINGTYPE_H

