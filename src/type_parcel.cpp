#include "type_parcel.h"
#include "BuildingType.h"
#include <stdlib.h>


BuildingType* type_parcel()
{
    int a= rand() % 5;
    if (a==0)
    {
        //cout<<"I"<<endl;
        return new Industry();
    }
    if (a==1)
    {
        //cout<<"O"<<endl;
        return new Office();
    }
    if (a==2)
    {
        //cout<<"AB"<<endl;
        return new ApartmentBuilding();
    }
    if (a==3)
    {
        //cout<<"V"<<endl;
        return new Villa();
    }
    else
    {
        //cout<<"TH"<<endl;
        return new Townhouse();
    }
}
