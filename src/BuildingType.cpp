#include "BuildingType.h"

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
    margin_parcel=0.10;
    margin_road=0.10;
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

/*
#include "catch.h"
TEST_CASE("Industry are computed", "[Industry]")
{
    Industry I;
    REQUIRE(I.get_floor() ==1);
    REQUIRE(I.get_floor_height() ==1);
    REQUIRE(I.get_gap() ==1);
    REQUIRE(I.get_height(1) ==1);
    REQUIRE(I.get_height(2) ==3);
    REQUIRE(I.get_height(3) ==4);
    double tmp[] = { 0.00001, 0.00001 };
    std::vector<double> margin( tmp, tmp+2 );
    REQUIRE(I.get_margin() ==margin);
    REQUIRE(I.get_margin_parcel() ==0.00001);
    REQUIRE(I.get_margin_road() ==0.00001);
    REQUIRE(I.get_profitability() ==1);
    REQUIRE(I.get_roof() ==1);
    REQUIRE(I.get_wall() ==1);
}
TEST_CASE("Office are computed", "[Office]")
{
    Office I;
    REQUIRE(I.get_floor() ==1);
    REQUIRE(I.get_floor_height() ==1);
    REQUIRE(I.get_gap() ==1);
    REQUIRE(I.get_height(1) ==1);
    REQUIRE(I.get_height(2) ==3);
    REQUIRE(I.get_height(3) ==4);
    double tmp[] = { 0.00001, 0.00001 };
    std::vector<double> margin( tmp, tmp+2 );
    REQUIRE(I.get_margin() ==margin);
    REQUIRE(I.get_margin_parcel() ==0.00001);
    REQUIRE(I.get_margin_road() ==0.00001);
    REQUIRE(I.get_profitability() ==1);
    REQUIRE(I.get_roof() ==1);
    REQUIRE(I.get_wall() ==1);
}
TEST_CASE("ApartmentBuilding are computed", "[ApartmentBuilding]")
{
    ApartmentBuilding I;
    REQUIRE(I.get_floor() ==1);
    REQUIRE(I.get_floor_height() ==1);
    REQUIRE(I.get_gap() ==1);
    REQUIRE(I.get_height(1) ==1);
    REQUIRE(I.get_height(2) ==3);
    REQUIRE(I.get_height(3) ==4);
    double tmp[] = { 0.00001, 0.00001 };
    std::vector<double> margin( tmp, tmp+2 );
    REQUIRE(I.get_margin() ==margin);
    REQUIRE(I.get_margin_parcel() ==0.00001);
    REQUIRE(I.get_margin_road() ==0.00001);
    REQUIRE(I.get_profitability() ==1);
    REQUIRE(I.get_roof() ==1);
    REQUIRE(I.get_wall() ==1);
}
TEST_CASE(" Villa are computed", "[Villa]")
{
     Villa I;
    REQUIRE(I.get_floor() ==1);
    REQUIRE(I.get_floor_height() ==1);
    REQUIRE(I.get_gap() ==1);
    REQUIRE(I.get_height(1) ==1);
    REQUIRE(I.get_height(2) ==3);
    REQUIRE(I.get_height(3) ==4);
    double tmp[] = { 0.00001, 0.00001 };
    std::vector<double> margin( tmp, tmp+2 );
    REQUIRE(I.get_margin() ==margin);
    REQUIRE(I.get_margin_parcel() ==0.00001);
    REQUIRE(I.get_margin_road() ==0.00001);
    REQUIRE(I.get_profitability() ==1);
    REQUIRE(I.get_roof() ==1);
    REQUIRE(I.get_wall() ==1);
}
TEST_CASE("Townhouse are computed", "[Townhouse]")
{
    Townhouse I;
    REQUIRE(I.get_floor() ==1);
    REQUIRE(I.get_floor_height() ==1);
    REQUIRE(I.get_gap() ==1);
    REQUIRE(I.get_height(1) ==1);
    REQUIRE(I.get_height(2) ==3);
    REQUIRE(I.get_height(3) ==4);
    double tmp[] = { 0.00001, 0.00001 };
    std::vector<double> margin( tmp, tmp+2 );
    REQUIRE(I.get_margin() ==margin);
    REQUIRE(I.get_margin_parcel() ==0.00001);
    REQUIRE(I.get_margin_road() ==0.00001);
    REQUIRE(I.get_profitability() ==1);
    REQUIRE(I.get_roof() ==1);
    REQUIRE(I.get_wall() ==1);
}
*/
