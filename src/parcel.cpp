#include <iostream>
#include "parcel.h"
// include class FootPrint
using namespace std;


Parcel::Parcel()
{
    //ctor
    cout << "parcel" << endl;
}

Parcel::~Parcel()
{
    //dtor
    cout << "del" << endl;
}
double Parcel::C_area()
{
    //calculate the parcel area
}
double Parcel::C_area_price()
{
    //calculate the area price
}
double Parcel::C_floor_price()
/** Bonjour
*:param: dgdgdg
*/
{
    //calculate the area need for the rentability
}
int Parcel::C_n_floor()
{
    //calculate the number of floor
}
void Parcel::create_footprint()
{
    //create the foot print of building
}
