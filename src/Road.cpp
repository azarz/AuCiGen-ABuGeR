#include "Road.h"
#include <iostream>
#include "ogrsf_frmts.h"
#include "poly_to_triangle.h"
#include "Triangle.h"
#include <string>
#include <sstream>
#include <fstream>
//#include "catch.h"

template <typename T>
  string num_to_string ( T Number )
  {
     ostringstream ss;
     ss << Number;
     return ss.str();
  }

Road::Road(OGRPolygon* poPolygon, int t_r)
{
    geom = poPolygon;
    type = t_r;
}

Road::~Road()
{
    //dtor
}

void Road::to_obj()
{
    // Converting the road polygons to triangles
    vector<Triangle> triangles;
    poly_to_triangle(geom,triangles,FLOOR);

    // Vector of all the points
    vector<Point> points;

    // Strings for the final output
    string vertices;
    string uv_coordinates;
    string faces;

    for (int i=0; i<triangles.size() ;++i)
    {
        // Getting the triangle and its points
        Triangle triangle = triangles.at(i);
        Point p1 = triangle.get_p1();
        Point p2 = triangle.get_p2();
        Point p3 = triangle.get_p3();

        // Boolean values to test whether the triangle's points are already listed
        bool p1_in_points = false;
        bool p2_in_points = false;
        bool p3_in_points = false;

        // Indexes of the points in the list, starting at 1
        int p1_index;
        int p2_index;
        int p3_index;

        // Initialization of th point list
        if(points.size()==0)
        {
            points.push_back(p1);
            points.push_back(p2);
            points.push_back(p3);

            p1_index = 1;
            p2_index = 2;
            p3_index = 3;
        // Usual case
        } else
        {
            // Testing if the triangles's points are already in the list
            for(i=0;i<points.size();++i)
            {
                Point p_i = points.at(i);
                if(p_i==p1){
                    p1_in_points = true;
                    p1_index = i+1;
                } else if(p_i==p2){
                    p2_in_points = true;
                    p2_index = i+1;
                } else if(p_i==p3){
                    p3_in_points = true;
                    p3_index = i+1;
                }
            }

            // If the point is new, it is added to the list. its index is then the size of the list
            if(!p1_in_points){
                points.push_back(p1);
                p1_index = points.size();
            }
            if(!p2_in_points){
                points.push_back(p2);
                p2_index = points.size();
            }
            if(!p3_in_points){
                points.push_back(p3);
                p3_index = points.size();
            }
        }

        // Constructing the face line corresponding to the triangle
        faces += "f " + num_to_string(p1_index) + "/1 "
                      + num_to_string(p2_index) + "/2 "
                      + num_to_string(p3_index) + "/3\n";

    }

    // Default uv coordinates
    uv_coordinates = "vt 0 0 \nvt 1 0 \nvt 0 1\n";

    // Constructing the vertex list base on the vector
    for(int i=0;i<points.size();++i)
    {
        Point vertex = points.at(i);
        vertices += "v " + num_to_string(vertex.get_x()) + " "
                         + num_to_string(vertex.get_y()) + " "
                         + num_to_string(vertex.get_z()) + "\n";

    }

    /* To control the output
    cout << vertices << endl;
    cout << uv_coordinates << endl;
    cout << faces << endl;
    */

    /* To have an output file
    ofstream out("roads.obj");
    out << vertices << uv_coordinates << faces;
    out.close();
    */

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
/**/
