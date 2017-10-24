#include "BuildingType.h"

BuildingType::BuildingType()
{
    //dtor;
}

BuildingType::~BuildingType()
{
    //dtor
}
double BuildingType::get_profitability()
{
    return profitability;
}
double BuildingType::get_height(double n_floor)
{
    double height;
    height=floor_height;
    if (n_floor >1)
    {
        height+=gap+(n_floor-1)*floor_height;
    }
    return height;
}
std::vector<int> BuildingType::get_surface_type()
{
    int tmp[] = { roof, wall, floor };
    std::vector<int> surface_type( tmp, tmp+3 );
    return surface_type;
}
std::vector<double> BuildingType::get_margin()
{
    double tmp[] = { margin_parcel, margin_road };
    std::vector<double> margin( tmp, tmp+2 );
    return margin;
}


Industry::Industry(){set_param();}
void Industry::set_param()
{
    profitability=1.0;
    floor_height=1.0;
    gap=1.0; //height between the 0floor and the 1floor
    roof=1;
    wall=1;
    floor=1;
    margin_parcel=0.00001;
    margin_road=0.00001;
}
Office::Office(){set_param();}
void Office::set_param()
{
    profitability=1;
    floor_height=1;
    gap=1; //height between the 0floor and the 1floor
    roof=1;
    wall=1;
    floor=1;
    margin_parcel=1;
    margin_road=1;
}
ApartmentBuilding::ApartmentBuilding(){set_param();}
void ApartmentBuilding::set_param()
{
    profitability=1;
    floor_height=1;
    gap=1; //height between the 0floor and the 1floor
    roof=1;
    wall=1;
    floor=1;
    margin_parcel=1;
    margin_road=1;
}
Villa::Villa(){set_param();}
void Villa::set_param()
{
    profitability=1;
    floor_height=1;
    gap=1; //height between the 0floor and the 1floor
    roof=1;
    wall=1;
    floor=1;
    margin_parcel=1;
    margin_road=1;
}
Townhouse::Townhouse(){set_param();}
void Townhouse::set_param()
{
    profitability=1;
    floor_height=1;
    gap=1; //height between the 0floor and the 1floor
    roof=1;
    wall=1;
    floor=1;
    margin_parcel=1;
    margin_road=1;
}
