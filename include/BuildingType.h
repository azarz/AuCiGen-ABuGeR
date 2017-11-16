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
        *Calculates the height of the building without roof.
        @param[in] n_floor: The number of floors.
        *@return building_height double
        */

        virtual void set_param() = 0;
        /**
        *@fn virtual void BuildingType::set_param() = 0
        *Sets the parameters. Implemented in child classes.
        */

        std::vector<double> get_margin();
        /**
        *@fn std::vector<double> BuildingType::get_margin()
        *Gets the margins between the building and the
        *parcel borders [m].
        *@return [margin_parcel, margin_road] std::vector<double>
        */

        // Getters
        double get_profitability()const{return profitability;};
        /**
        *@fn double BuildingType::get_profitability() const
        *Gets the profitability price [€/m2].
        *@return profitability double
        */

        double get_floor_height()const{return floor_height;};
        /**
        *@fn double BuildingType::get_floor_height() const
        *Gets the height for one floor [m].
        *@return floor_height double
        */

        double get_gap()const{return gap;};
        /**
        *@fn double BuildingType::get_gap() const
        *Gets the height between the 1st floor and the second floor.
        *@return gap double
        */

        int get_roof()const{return roof;};
        /**
        *@fn int BuildingType::get_roof() const
        *Gets the roof type for the building.
        *@return roof int
        */

        int get_wall()const{return wall;};
        /**
        *@fn int BuildingType::get_wall() const
        *Gets the wall type of the building.
        *@return wall int
        */

        int get_floor()const{return floor;};
        /**
        *@fn int BuildingType::get_floor() const
        *Gets the floor type for the building.
        *@return floor int
        */

        double get_margin_parcel()const{return margin_parcel;};
        /**
        *@fn double BuildingType::get_margin_parcel() const
        *Gets the margin between the building and the parcel.
        *border without road [m]
        *@return margin_parcel double
        */

        double get_margin_road()const{return margin_road;};
        /**
        *@fn double BuildingType::get_margin_road() const
        *Gets the margin between the building and the parcel.
        *border with road [m]
        *@return margin_road double
        */

        string get_type()const{return type;};
        /**
        *@fn string get_type() const
        *Gets the type for the building.
        *@return type string
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
        string type;
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
        *Sets the value of the parameters.
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
        *Sets the value of the parameters.
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
        *Sets the value of the parameters.
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
        *Sets the value of the parameters.
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
        *Sets the value of the parameters.
        */
    protected:
    private:
};
#endif // BUILDINGTYPE_H

