#ifndef ENVELOP_H
#define ENVELOP_H

#include "BuildingModel.h"
#include "FootPrint.h"
#include "parcel.h"

class Envelop
{
    public:
        Envelop();
        virtual ~Envelop();



        BuildingModel *volume;
        FootPrint *footprint;
        Parcel *parcel;
        int n_floor;
    protected:
    private:
};

#endif // ENVELOP_H
