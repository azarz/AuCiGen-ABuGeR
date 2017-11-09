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
    //area(1), area_price(1), floorspace(1)//
    geom = poPolygon;

    area = poPolygon->OGRCurvePolygon::get_Area();


    //type = new Industry();
    area=geom->OGRCurvePolygon::get_Area();
    area_price=10*area;
    this->compute_type(centroid);
    floorspace=area_price*(type->get_profitability()); // need profitability !!!!!!
}

Parcel::~Parcel()
{
    //dtor
    //cout << "del" << endl;
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

/*TEST_CASE("Parcel are computed","[Parcel]")
{
    char* wkt ="POLYGON ((55.4683455250644 -21.3282187046573,55.4683460303297 -21.3282180820721,55.4685788303297 -21.3279358820721,55.4685905503442 -21.3279255206688,55.46860489859 -21.3279192880722,55.468620470561 -21.3279177943725,55.468635741964 -21.3279211857833,55.4686492179279 -21.3279291303297,55.4686595793312 -21.3279408503442,55.4686658119277 -21.32795519859,55.4686673056275 -21.327970770561,55.4686639142167 -21.327986041964,55.4686559696703 -21.3279995179279,55.4684234247991 -21.3282814086609,55.4681532749356 -21.3286197953427,55.4681417225811 -21.3286303433531,55.4681274761246 -21.3286368052333,55.4681119301085 -21.3286385484493,55.4680966062852 -21.3286354023632,55.4680830046573 -21.3286276749356,55.4680724566469 -21.3286161225811,55.4680659947667 -21.3286018761245,55.4680642515507 -21.3285863301085,55.4680673976368 -21.3285710062852,55.4680751250644 -21.3285574046573,55.4683455250644 -21.3282187046573))";
    OGRPolygon poPolygon= OGRPolygon();
    poPolygon.OGRPolygon::importFromWkt( &wkt);
    Parcel p= Parcel(&poPolygon);

    char* wktS;
    p.get_geom()->exportToWkt(&wktS);
    //REQUIRE(wktS==wkt);
}
*/
