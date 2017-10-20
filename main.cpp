#include <iostream>
#include <vector>
//#include "Parcel.h"
//#include "Envelop.h"
#include "open_shp.h"
#include <vector>
#include "Road.h"
#include "Parcel.h"

using namespace std;


vector<Road> ROADS;
vector<Parcel> PARCELS;


int main()
{
    //Parcel();
    char* fill_directory ="1_data/shp_R.shp";
    char layer_type ='R';
    ROADS=OpenShapeFile_roads(fill_directory);
    fill_directory ="1_data/shp_P.shp";
    layer_type ='P';
    PARCELS=OpenShapeFile_parcels(fill_directory);
    cout << "Hello world!" << endl;
    return 0;
}
