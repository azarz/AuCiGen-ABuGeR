#ifndef BUILDING_H
#define BUILDING_H

#include "Parcel.h"
#include "BuildingModel.h"
#include "Envelop.h"
#include <vector>
#include "ogrsf_frmts.h"

class Building
{
/**
*@class Building
*Contain the Building.
*/
    public:
        Building(Envelop* env);
        /**
        *@fn Building::Building()
        *Constructor.
        *@param[in] env: envelop object
        */
        virtual ~Building();
        /**
        *@fn virtual Building::~Building()
        *Destructor.
        */

        void creat_roof(double roofAngle);
        /**
        *@fn BuildingModel Building::creat_roof(double roofAngle)
        *Creates a roof for a simple building depending of his roof angle.
        *@param[in] roofAngle: The roof angle.
        */

        vector<string> to_obj(OGRPoint* centroid, int& index_offset);
        /**
        *@fn void Building::to_obj()
        *Converts the Building to Wavefront .obj format.
        *@param[in] centroid: an OGRPoint pointer corresponding to the centroid of the city
        *@param[in] index_offset: the index offset
        **/

        // Getters
        Parcel* get_parcel()const{return parcel;};
        /**
        *@fn Parcel* Building::get_parcel() const
        *Gets the Parcel associated with the building.
        *@return parcel Parcel*
        */

        std::vector<BuildingModel> get_building_models()const{return building_models;};
        /**
        *@fn std::vector<BuildingModel> Building::get_building_models() const
        *Gets the list of BuildingModel associated to one house.
        *@return building_models std::vector<BuildingModel>
        */
        double get_height()const{return height;};
        /**
        *@fn double get_height()const{return height;};
        *Gets the building's height.
        *@return height double
        */

        OGRPolygon* get_geom()const{return geom;};
        /**
        *@fn OGRPolygon* Building::get_geom() const
        *Gets the building's geometry.
        *@return geom OGRPolygon*
        */

    protected:
    private:
        Parcel* parcel;
        std::vector<BuildingModel> building_models;
        double height;
        OGRPolygon* geom;
};

#endif // BUILDING_H
