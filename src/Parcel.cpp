#include <iostream>
#include "Parcel.h"
#include "ogrsf_frmts.h"
#include "BuildingType.h"
#include "Footprint.h"
#include <vector>
#include "Triangle.h"
#include "poly_to_triangle.h"
#include "triangles_to_obj.h"
using namespace std;


Parcel::Parcel(OGRPolygon* poPolygon, OGRPoint* centroid)
{
    //ctor
    //area(1), area_price(1), floorspace(1)//
    geom = poPolygon;

    area = poPolygon->OGRCurvePolygon::get_Area();


    //type = new Industry();
    area=geom->OGRCurvePolygon::get_Area();
    area_price=10*area;
    type = this->compute_type(centroid);
    floorspace=area_price*(type->get_profitability()); // need profitability !!!!!!
    //cout << type->get_type() << endl;
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

    OGRGeometry* diff1 = geom->Difference(road_buffer);
    OGRGeometry* diff2 = diff1->Difference(neigh_buffer);

    OGRGeometry* contour = diff2->getBoundary();
    OGRLinearRing* contour2 = (OGRLinearRing*) contour;
    Footprint footprint(contour2,this);
    return footprint;
}

void Parcel::to_obj(OGRPoint* centroid)
{
    // Converting the road polygons to triangles
    vector<Triangle> triangles;
    poly_to_triangle(geom,triangles,FLOOR);

    triangles_to_obj(triangles, centroid->getX(), centroid->getY());
}


BuildingType* Parcel::compute_type(OGRPoint* centroid)
{
    int a= rand() % 5;
    if (a==0)
    {
        //cout<<"I"<<endl;
        //type = new Industry();
        return new Industry();
    }
    if (a==1)
    {
        //cout<<"O"<<endl;
        //type = new Office();
        return new Office();
    }
    if (a==2)
    {
        //cout<<"AB"<<endl;
        //type = new ApartmentBuilding();
        return  new ApartmentBuilding();
    }
    if (a==3)
    {
        //cout<<"V"<<endl;
        //type = new Villa();
        return  new Villa();
    }
    else
    {
        //cout<<"TH"<<endl;
        //type = new Townhouse();
        return new Townhouse();
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
/**/
