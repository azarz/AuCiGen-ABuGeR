#include <iostream>
#include <vector>
//#include "Parcel.h"
//#include "Envelop.h"
#include "open_shp.h"
#include <vector>

using namespace std;

int main()
{
    //Parcel();
    char* fill_directory ="/home/formation/AuCiGen/ABuGeR/1_data/shp_R.shp";
    char layer_type ='R';
    vector<Polygon> ROADS=OpenShapeFile(fill_directory, layer_type);
    fill_directory ="/home/formation/AuCiGen/ABuGeR/1_data/shp_P.shp";
    layer_type ='P';
    vector<Polygon> PARCELS=OpenShapeFile(fill_directory, layer_type);
    cout << "Hello world!" << endl;
    return 0;
}
