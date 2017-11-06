#include "Road.h"
#include <iostream>
#include "ogrsf_frmts.h"
#include "poly_to_triangle.h"
#include "Triangle.h"
#include <string>
#include <fstream>
#include "triangles_to_obj.h"
//#include "catch.h"


Road::Road(OGRPolygon* poPolygon, int t_r)
{
    geom = poPolygon;
    type = t_r;
}

Road::~Road()
{
    //dtor
}

vector<string> Road::to_obj(OGRPoint* centroid)
{
    // Converting the road polygons to triangles
    vector<Triangle> triangles;
    poly_to_triangle(geom,triangles,FLOOR);

    return triangles_to_obj(triangles, centroid->getX(), centroid->getY());
}


/*TEST_CASE("Road are computed","[Road]")
{
    char* wkt ="POLYGON ((55.4683455250644 -21.3282187046573,55.4683460303297 -21.3282180820721,55.4685788303297 -21.3279358820721,55.4685905503442 -21.3279255206688,55.46860489859 -21.3279192880722,55.468620470561 -21.3279177943725,55.468635741964 -21.3279211857833,55.4686492179279 -21.3279291303297,55.4686595793312 -21.3279408503442,55.4686658119277 -21.32795519859,55.4686673056275 -21.327970770561,55.4686639142167 -21.327986041964,55.4686559696703 -21.3279995179279,55.4684234247991 -21.3282814086609,55.4681532749356 -21.3286197953427,55.4681417225811 -21.3286303433531,55.4681274761246 -21.3286368052333,55.4681119301085 -21.3286385484493,55.4680966062852 -21.3286354023632,55.4680830046573 -21.3286276749356,55.4680724566469 -21.3286161225811,55.4680659947667 -21.3286018761245,55.4680642515507 -21.3285863301085,55.4680673976368 -21.3285710062852,55.4680751250644 -21.3285574046573,55.4683455250644 -21.3282187046573))";
    OGRPolygon poPolygon= OGRPolygon();
    poPolygon.OGRPolygon::importFromWkt( &wkt);
    Road r= Road(&poPolygon, 1);
    REQUIRE(r.get_type()==1);
    char* wktS;
    r.get_geom()->exportToWkt(&wktS);
    //REQUIRE(wktS==wkt);
}
*/
