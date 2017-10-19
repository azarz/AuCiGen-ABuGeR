#ifndef FOOTPRINT_H
#define FOOTPRINT_H

#include "parcel.h"
#include "ogrsf_frmts.h"

class FootPrint
{
    public:
        FootPrint();
        virtual ~FootPrint();

        void create_envelop();

        OGRPolygon geom;
        Parcel *parcel;
    protected:
    private:
};

#endif // FOOTPRINT_H
