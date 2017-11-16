#ifndef CREATE_ENV_ROOF_H_INCLUDED
#define CREATE_ENV_ROOF_H_INCLUDED

#include "ogrsf_frmts.h"
#include "Triangle.h"

/** @file */
void create_env_roof(double height, vector<Triangle>& li_tri);
/**
*@fn void create_env_roof(double height, vector<Triangle>& li_tri)
*Creates envelop roof
*@param[in] height: The building height.
*@param[in/out] li_tri: The output list of ROOF Triangle, already containing the floor triangles.
*/

#endif // CREAT_WALL_H_INCLUDED
