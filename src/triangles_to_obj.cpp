#include "triangles_to_obj.h"

#include <string>
#include <vector>
#include <iostream>

#include <sstream>


template <typename T>
  string num_to_string ( T Number )
  {
     ostringstream ss;
     ss << Number;
     return ss.str();
  }

vector<string> triangles_to_obj(vector<Triangle> triangles, int& index_offset,
                                double x_centroid, double y_centroid)
{
    // Vector of all the points
    vector<Point> points;

    // Strings for the final output
    string vertices;
    string uv_coordinates;
    string faces;

    for (unsigned int i=0U; i<triangles.size() ;++i)
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

        // Initialization of the point list
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
            // (Last half of the triangles for faster results, because the common points are
            //   in adjacent triangles)
            for(unsigned int j=(i-i/2)*3;j<points.size();++j)
            {
                Point p_j = points.at(j);
                if(p_j==p1){
                    p1_in_points = true;
                    p1_index = j+1;
                } else if(p_j==p2){
                    p2_in_points = true;
                    p2_index = j+1;
                } else if(p_j==p3){
                    p3_in_points = true;
                    p3_index = j+1;
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
        faces += "f " + num_to_string(p1_index + index_offset) + "/1 "
                      + num_to_string(p2_index + index_offset) + "/2 "
                      + num_to_string(p3_index + index_offset) + "/3\n";

    }

    // Default uv coordinates
    uv_coordinates = "vt 0 0 \nvt 100 0 \nvt 0 100\n";

    // Constructing the vertex list base on the vector
    for(unsigned int i=0;i<points.size();++i)
    {
        Point vertex = points.at(i);
        vertices += "v " + num_to_string(vertex.get_x() - x_centroid) + " "
                         + num_to_string(vertex.get_z()) + " "
                         + num_to_string(-(vertex.get_y() - y_centroid)) + "\n";

    }

    vector<string> results;

    // Updating the index offset
    index_offset+= points.size();

    results.push_back(vertices);
    results.push_back(uv_coordinates);
    results.push_back(faces);

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

    return results;
}
