#include <iostream>
#include "Parcel.h"
#include "ogrsf_frmts.h"
#include "BuildingType.h"
#include "Footprint.h"
#include <vector>
using namespace std;


Parcel::Parcel(OGRPolygon* poPolygon)
{
    //ctor
    //area(1), area_price(1), floorspace(1)// area(geom->OGRCurvePolygon::get_Area());
    geom = poPolygon;
    type = new Industry();
    area=geom->OGRCurvePolygon::get_Area();
    area_price=10*area;
    floorspace=area_price*(type->get_profitability()); // need profitability !!!!!!
    /*cout << "parcel :" <<endl;
    cout << "area->"<< area << endl;
    cout << "area_price->"<< area_price << endl;
    cout << "floorspace->" << floorspace<< endl;*/

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

OGRLinearRing* Parcel::create_footprint(OGRLineString* linearIntersection, OGRLineString* otherSides)
{
    vector<double> margins = type->get_margin();
    OGRGeometry* road_buffer = linearIntersection->Buffer(margins.at(1));
    OGRGeometry* neigh_buffer = otherSides->Buffer(margins.at(0));

    OGRGeometry* diff1 = geom->Difference(road_buffer);
    OGRGeometry* diff2 = diff1->Difference(neigh_buffer);

    OGRGeometry* contour = diff2->getBoundary();
    OGRLinearRing* contour2 = (OGRLinearRing*) contour;
    return contour2;
}

void Parcel::to_obj()
{
    //convert to .obj
}
