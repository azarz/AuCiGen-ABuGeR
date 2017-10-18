#include "shpto3d.h"
#include <iostream>
using namespace std;

shpto3d::shpto3d(std::string fill_path, std::string fill_name)
{
    name=fill_name;
    path=fill_path+"/"+fill_name+".shp";
    cout << "ok" << endl;
    cout << name << endl;
    cout << path << endl;
}

shpto3d::~shpto3d()
{
    cout << "fin" << endl;
}

/*shpto3d::readSHP()
{

}
*/
