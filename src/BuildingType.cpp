#include "BuildingType.h"

#include <vector>
#include <iostream>

BuildingType::BuildingType()
{
    //dtor;
}

BuildingType::~BuildingType()
{
    //dtor
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

std::vector<double> BuildingType::get_margin()
{
    double tmp[] = { margin_parcel, margin_road };
    std::vector<double> margin( tmp, tmp+2 );
    return margin;
}


Industry::Industry(){set_param();}
void Industry::set_param()
{
    profitability=2.0;
    floor_height=3.0;
    gap=15.0; //height between the 0floor and the 1floor
    roof=1;
    wall=1;
    floor=1;
    margin_parcel=2.0;
    margin_road=3.0;
    type="Industry";
}

Office::Office(){set_param();}
void Office::set_param()
{
    profitability=12.0;
    floor_height=3;
    gap=5; //height between the 0floor and the 1floor
    roof=1;
    wall=1;
    floor=1;
    margin_parcel=0.001;
    margin_road=0.001;
    type="Office";
}
ApartmentBuilding::ApartmentBuilding(){set_param();}
void ApartmentBuilding::set_param()
{
    profitability=6.0;
    floor_height=3.0;
    gap=5.0; //height between the 0floor and the 1floor
    roof=1;
    wall=1;
    floor=1;
    margin_parcel=0.001;
    margin_road=0.05;
    type="ApartmentBuilding";
}
Villa::Villa(){set_param();}
void Villa::set_param()
{
    profitability=1.0;
    floor_height=3.0;
    gap=3.0; //height between the 0floor and the 1floor
    roof=1;
    wall=1;
    floor=1;
    margin_parcel=0.1;
    margin_road=0.1;
    type="Villa";
}
Townhouse::Townhouse(){set_param();}
void Townhouse::set_param()
{
    profitability=1.0;
    floor_height=1.0;
    gap=1.0; //height between the 0floor and the 1floor
    roof=1;
    wall=1;
    floor=1;
    margin_parcel=0.001;
    margin_road=0.05;
    type="Townhouse";
}
