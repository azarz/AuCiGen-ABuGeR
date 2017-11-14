#include "ABuGeR.h"
#include "EAGL.h"


int main()
{
    const char* file_path_Road ="1_data/paris_test/route_secondaire_buffer.shp";
    const char* layer_name_Road ="route_secondaire_buffer";
    const char* file_path_Parcel ="1_data/paris_test/test_paris_seuil.shp";
    const char* layer_name_Parcel ="test_paris_seuil";
    int a = ABuGeR(file_path_Road, layer_name_Road, file_path_Parcel, layer_name_Parcel);
    int b = EAGL();
    return a+b;
}
