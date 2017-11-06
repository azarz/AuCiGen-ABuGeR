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
        *@param[in] poPolygon OGRPolygon*: The parcel geometry.
        */

        virtual ~Parcel();
        /**
        *@fn virtual Parcel::~Parcel(OGRPolygon* poPolygon)
        *Destructor.
        */

        Footprint create_footprint(OGRLineString* linearIntersection, OGRLineString* otherSides);
        /**
        *@fn Footprint Parcel::create_footprint(OGRLineString* linearIntersection, OGRLineString* otherSides);
        *Creates the footprint of the building on the parcel.
        *@param[in] linearIntersection OGRLineString*: intersection between the parcel and the main road.
        *@param[in] otherSides OGRLineString*: the sides of the parcel that aren't "linearIntersection".
        *@returns the Footprint associated to the parcel.
        */

        void to_obj(OGRPoint* centroid);
        /**
        *@fn void Parcel::to_obj()
        *Converts the Parcel to Wavefront .obj format.
        *@param[in] an OGRPoint pointer corresponding to the centroid of the city
        **/

        void print();
        /**
        *@fn void Parcel::print();
        *Displays the Parcel attributes.
        */

        void compute_type(OGRPoint* centroid);
        /**
        *@fn void Parcel::compute_type();
        *Computes the type of the parcel.
        *@param[in] centroid OGRPoint*: Then centroid of the city.
        */

        // Getters
        OGRPolygon* get_geom()const{return geom;};
        /**
        *@fn OGRPolygon* Parcel::get_geom() const
        *Gets the parcel's geometry.
        *@return geom
        */
        BuildingType* get_type()const{return type;};
        /**
        *@fn BuildingType* Parcel::get_type() const
        *Gets the parcel's type.
        *@return type
        */
        double get_area()const{return area;};
        /**
        *@fn double Parcel::get_area() const
        *Gets the parcel's area.
        *@return area
        */
        double get_area_price()const{return area_price;};
        /**
        *@fn double Parcel::get_area_price() const
        *Gets the parcel's area_price.
        *@return area_price
        */
        double get_floorspace()const{return floorspace;};
        /**
        *@fn double Parcel::get_floorspace() const
        *Get the parcel's floorspace.
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
