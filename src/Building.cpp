#include "Building.h"
#include "Parcel.h"
#include "BuildingModel.h"
#include "Envelop.h"
#include <vector>

Building::Building(Envelop* env)
{
    //ctor
    parcel=env->get_parcel();
    string parcel_type = parcel->get_type()->get_type();
    cout << parcel_type << endl;

    //rectangle

}

Building::~Building()
{
    //dtor
}

void Building::creat_roof(double roofAngle)
{

}
void Building::to_obj(OGRPoint* centroid)
{
    //
}

