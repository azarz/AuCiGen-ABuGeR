#ifndef ROAD_H
#define ROAD_H

#include <iostream>
#include "ogrsf_frmts.h"
using namespace std;

class Road
{
    public:
        Road();
        virtual ~Road();

        void to_obj();

        OGRPolygon geom;
        string type;
    protected:
    private:
};

#endif // ROAD_H
