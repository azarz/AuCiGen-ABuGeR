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

void Parcel::create_footprint()
{
    //create the foot print of building
}
