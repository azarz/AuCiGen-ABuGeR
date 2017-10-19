#include <iostream>
#include "parcel.h"
#include "ogrsf_frmts.h"
#include "BuildingType.h"
#include "FootPrint.h"
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
void Parcel::to_obj()
{
    //convert to .obj
}
