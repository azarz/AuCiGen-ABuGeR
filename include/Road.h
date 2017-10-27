#ifndef ROAD_H
#define ROAD_H

#include <iostream>
#include "ogrsf_frmts.h"
using namespace std;

class Road
{
    /**
    *@class Road
    *contain Road
    */
    public:
        Road(OGRPolygon* poPolygon, int t_r);
        /**
        *@fn Road::Road(OGRPolygon* poPolygon, int t_r)
        *Road creator
        *@param[in] poPolygon OGRPolygon* : road goemetry
        *@param[in] t_r int : type of road (1: main road, 2: side road)
        */
        virtual ~Road();

        void to_obj();
        /**
        *@fn Road::to_obj()
        *creates a .obj of road
        **/

        //Getters
        OGRPolygon* get_geom()const{return geom;};
        /**
        *@fn OGRPolygon* Road::get_geom()
        *get the geometry of road
        *@return  geom OGRPolygon*
        */
        int get_type()const{return type;};
        /**
        *@fn int Road::get_type()
        *get the type of road (1: main road, 2: side road)
        *@return  type int
        */

    protected:
    private:
        OGRPolygon* geom;
        int type;
};

#endif // ROAD_H

