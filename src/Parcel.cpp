#include <iostream>
#include "Parcel.h"
#include "ogrsf_frmts.h"
#include "BuildingType.h"
#include "Footprint.h"
#include <vector>
using namespace std;


Parcel::Parcel()
{
    //ctor
    //type = new Industry;
    cout << "parcel" << endl;
}

Parcel::~Parcel()
{
    //dtor
    cout << "del" << endl;
}

OGRLinearRing* Parcel::create_footprint(OGRLineString* linearIntersection, OGRLineString* otherSides)
{
    vector<double> margins = type->get_margin();
    OGRGeometry* road_buffer = linearIntersection->Buffer(margins.at(1));
    OGRGeometry* neigh_buffer = otherSides->Buffer(margins.at(0));

    OGRGeometry* diff1 = geom.Difference(road_buffer);
    OGRGeometry* diff2 = diff1->Difference(neigh_buffer);

    OGRGeometry* contour = diff2->getLinearGeometry();
    OGRLinearRing* contour2 = (OGRLinearRing*) contour;
    return contour2;
}

void Parcel::to_obj()
{
    //convert to .obj
}
