#include "Parcel.h"

#include <iostream>
#include <vector>

#include "BuildingType.h"
#include "Footprint.h"
#include "Triangle.h"

#include "ogrsf_frmts.h"
#include "poly_to_triangle.h"
#include "triangles_to_obj.h"

using namespace std;

Parcel::Parcel()
{

}

Parcel::Parcel(OGRPolygon* poPolygon, OGRPoint* centroid)
{
    //ctor
    geom = poPolygon;
    area = poPolygon->OGRCurvePolygon::get_Area();
    area_price=10*area;
    this->compute_type(centroid);
    floorspace=area_price*(type->get_profitability()); // need profitability !!!!!!
}

Parcel::~Parcel()
{
    //dtor
}

void Parcel::print(){
    cout << "parcel :" <<endl;
    cout << "geom:"<< geom->getGeometryType() << endl;
    cout << "area->"<< geom->OGRCurvePolygon::get_Area() << endl;
    cout << "area_price->"<< area_price << endl;
    cout << "floorspace->" << floorspace<< endl;
}

Footprint Parcel::create_footprint(OGRLineString* linearIntersection, OGRLineString* otherSides)
{
    vector<double> margins = type->get_margin();

    OGRGeometry* road_buffer = linearIntersection->Buffer(margins.at(1));
    OGRGeometry* neigh_buffer = otherSides->Buffer(margins.at(0));

    //By default, the footprint takes all the parcel space
    Footprint footprint(geom->getExteriorRing(),this);

    //If the difference returns an empty thing, return the parcel contour
    OGRGeometry* diff1 = geom->Difference(road_buffer);
    if (diff1->getGeometryType()!=3)
    {
        return footprint;
    }

    OGRGeometry* diff2_geom = diff1->Difference(neigh_buffer);

    if (diff2_geom->getGeometryType()!=3)
    {
        return footprint;
    }

    OGRPolygon* diff2 = (OGRPolygon*)diff2_geom;
    OGRGeometry* contour = diff2->getExteriorRing();
    OGRLinearRing* contour2 = (OGRLinearRing*) contour;

    // More common: if the contour is a LinearRing (expected)
    footprint= Footprint(contour2,this);
    return footprint;
}

vector<string> Parcel::to_obj(OGRPoint* centroid, int& index_offset)
{
    // Converting the road polygons to triangles
    vector<Triangle> triangles;
    poly_to_triangle(geom,triangles,FLOOR);

    return triangles_to_obj(triangles, index_offset, centroid->getX(), centroid->getY());
}


void Parcel::compute_type(OGRPoint* centroid)
{
    //Thresholds of distance from the center to determine the districts
    double low_thresh = 1500; //In meters
    double high_thresh = 4500;

    bool downtown = false;
    bool uptown = false;
    bool suburbs = false;

    double dist_centroid = geom->Distance(centroid);

    if (dist_centroid <= low_thresh)
    {
        downtown = true;
    } else if (dist_centroid > high_thresh)
    {
        suburbs = true;
    } else
    {
        uptown = true;
    }

    int a = rand() % 100;
    if (downtown)
    {
        if (a<50)
        {
            type = new Office();
        } else
        {
            type = new ApartmentBuilding();
        }
    } else if (uptown)
    {
        if (a<60)
        {
            type = new ApartmentBuilding();
        } else if (a>=60 && a<90)
        {
            type = new Townhouse();
        } else
        {
            type = new Office();
        }
    } else if (suburbs)
    {
        if (a<50)
        {
            type = new Villa();
        } else if (a>=50 && a<75)
        {
            type = new Industry();
        } else
        {
            type = new Townhouse();
        }
    } else
    {
        type = new Office();
    }

}
