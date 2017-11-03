#ifndef ROAD_H
#define ROAD_H

#include <iostream>
#include "ogrsf_frmts.h"
using namespace std;

class Road
{
    /**
    *@class Road
    *Contain Road.
    */
    public:
        Road(OGRPolygon* poPolygon, int t_r);
        /**
        *@fn Road::Road(OGRPolygon* poPolygon, int t_r)
        *Road creator.
        *@param[in] poPolygon OGRPolygon* : It's a road geometry.
        *@param[in] t_r int : It's the type of road (1: main road, 2: side road).
        */

        virtual ~Road();
        /**
        *@fn virtual Road::Road(OGRPolygon* poPolygon, int t_r)
        *Road destructor.
        */

        void to_obj();
        /**
        *@fn void Road::to_obj()
        *This function allows us to creates an .obj of road.
        **/

        //Getters
        OGRPolygon* get_geom()const{return geom;};
        /**
        *@fn OGRPolygon* Road::get_geom() const
        *This function allows us to get the geometry of road.
        *@return  geom OGRPolygon*.
        */
        int get_type()const{return type;};
        /**
        *@fn int Road::get_type() const
        *This function allows us to get the type of road (1: main road, 2: side road).
        *@return type int.
        */

    protected:
    private:
        OGRPolygon* geom;
        int type;
};

#endif // ROAD_H

