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

        //Getters
        OGRPolygon get_geom()const{return geom;};
        string get_type()const{return type;};

    protected:
    private:
        OGRPolygon geom;
        string type;
};

#endif // ROAD_H
