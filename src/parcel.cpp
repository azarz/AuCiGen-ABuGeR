#include <iostream>
#include "parcel.h"
#include "ogrsf_frmts.h"
#include "BuildingType.h"
#include "FootPrint.h"
#include <vector>
using namespace std;


Parcel::Parcel()
{
    //ctor
    cout << "parcel" << endl;
}

Parcel::~Parcel()
{
    //dtor
    cout << "del" << endl;
}

OGRLinearRing Parcel::create_footprint(OGRLineString linearIntersection, OGRLineString otherSides)
{
    vector<double> margins = type->get_margin();
    OGRPolygon road_buffer = linearIntersection.Buffer(margins.at(1));
    OGRPolygon neigh_buffer = otherSides.Buffer(margins.at(0));

    OGRPolygon diff1 = Parcel.geom.Difference(road_buffer);
    OGRPolygon diff2 = diff1.Difference(neigh_buffer);

    OGRLinearRing contour = diff2.getLinearGeometry();

    return contour;
}

void Parcel::to_obj()
{
    //convert to .obj
}
