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
        *@param[in] poPolygon OGRPolygon*: A road geometry.
        *@param[in] t_r int: The type of road (1: main road, 2: side road).
        */

        virtual ~Road();
        /**
        *@fn virtual Road::Road(OGRPolygon* poPolygon, int t_r)
        *Road destructor.
        */

        vector<string> to_obj(OGRPoint* centroid, int& index_offset);
        /**
        *@fn void Road::to_obj()
        *Creates an .obj of road.
        *@param[in] an OGRPoint pointer corresponding to the centroid of the city
        *@param[in] the index offset of the triangles.
        *@return A vector of 3 strings: 1-vertices 2-uv coordinates 3-faces
        **/

        //Getters
        OGRPolygon* get_geom()const{return geom;};
        /**
        *@fn OGRPolygon* Road::get_geom() const
        *Gets the geometry of road.
        *@return  geom OGRPolygon*.
        */
        int get_type()const{return type;};
        /**
        *@fn int Road::get_type() const
        *Gets the type of road (1: main road, 2: side road).
        *@return type int.
        */

    protected:
    private:
        OGRPolygon* geom;
        int type;
};

#endif // ROAD_H

