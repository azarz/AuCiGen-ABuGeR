#include <iostream>
#include <vector>
//#include "Parcel.h"
//#include "Envelop.h"
#include "open_shp.h"
#include <vector>

using namespace std;


vector<Polygon> ROADS;
vector<Polygon> PARCELS;


int main()
{
    //Parcel();
    char* fill_directory ="1_data/shp_R.shp";
    char layer_type ='R';
    ROADS=OpenShapeFile(fill_directory, layer_type);
    fill_directory ="1_data/shp_P.shp";
    layer_type ='P';
    PARCELS=OpenShapeFile(fill_directory, layer_type);
    cout << "Hello world!" << endl;
    return 0;
}
