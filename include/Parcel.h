#ifndef PARCEL_H
#define PARCEL_H

#include "ogrsf_frmts.h"
#include "BuildingType.h"
#include "orient.h"
#include "Footprint.h"

class Footprint;

class Parcel
{
    /**
    *@class Parcel
    *Contain parcel
    */
    public:
        Parcel(OGRPolygon* poPolygon);
        /**
        *@fn Parcel::Parcel(OGRPolygon* poPolygon)
        *Constructor.
        *@param[in] poPolygon OGRPolygon* : It's the parcel geometry.
        */

        virtual ~Parcel();
        /**
        *@fn virtual Parcel::~Parcel(OGRPolygon* poPolygon)
        *Destructor.
        */

        Footprint create_footprint(OGRLineString* linearIntersection, OGRLineString* otherSides);
        /**
        *@fn Footprint Parcel::create_footprint(OGRLineString* linearIntersection, OGRLineString* otherSides);
        *This function allows us to create the footprint of the building on the parcel.
        *@param[in] linearIntersection OGRLineString* : intersection between the parcel and the main road.
        *@param[in] otherSides OGRLineString* : the sides of the parcel that aren't "linearIntersection".
        *@returns the Footprint associated to the parcel.
        */

        void to_obj();
        /**
        *@fn void Parcel::to_obj()
        *This function allows us to create a .obj of road.
        **/

        void print();
        /**
        *@fn void Parcel::print();
        *This function allows us to display the parcel's attributes.
        */

        // Getters
        OGRPolygon* get_geom()const{return geom;};
        /**
        *@fn OGRPolygon* Parcel::get_geom() const
        *This function allows us to get the parcel's geometry.
        *@return geom
        */
        BuildingType* get_type()const{return type;};
        /**
        *@fn BuildingType* Parcel::get_type() const
        *This function allows us to get the parcel's type.
        *@return type
        */
        double get_area()const{return area;};
        /**
        *@fn double Parcel::get_area() const
        *This function allows us to get the parcel's area.
        *@return area
        */
        double get_area_price()const{return area_price;};
        /**
        *@fn double Parcel::get_area_price() const
        *This function allows us to get the parcel's area_price.
        *@return area_price
        */
        double get_floorspace()const{return floorspace;};
        /**
        *@fn double Parcel::get_floorspace() const
        *This function allows us to get the parcel's floorspace.
        *@return floorspace
        */

    protected:
    private:
        OGRPolygon* geom;
        BuildingType* type;
        double area;
        double area_price;
        double floorspace;
};

#endif // PARCEL_H
