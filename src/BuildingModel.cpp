#include "BuildingModel.h"

#include <vector>
#include <iostream>

#include "Parcel.h"
#include "Point.h"
#include "Triangle.h"

BuildingModel::BuildingModel()
{
    //ctor
}

BuildingModel::BuildingModel(std::vector<Triangle> li_T, Parcel* p)
{
    li_triangle=li_T;
    parcel=p;
}

BuildingModel::~BuildingModel()
{
    //dtor
}

void BuildingModel::translate(double vec[3], TriangleType name)
{
    for (unsigned int i=0U; i<li_triangle.size(); i++)
    {
        if (li_triangle[i].get_type() == name)
        {
            li_triangle[i].translate(vec);
        }
    }
}

void BuildingModel::rotate(double vec[3], double angle, TriangleType name)
{
    for (unsigned int i=0U; i<li_triangle.size(); i++)
    {
        if (li_triangle[i].get_type() == name)
        {
            li_triangle[i].rotate(vec,angle);
        }
    }
}

void BuildingModel::size(double vec[3], TriangleType name)
{
    for (unsigned int i=0U; i<li_triangle.size(); i++)
    {
        if (li_triangle[i].get_type() == name)
        {
            li_triangle[i].size(vec);
        }
    }
}

void BuildingModel::split(double axis[3], Point origin, TriangleType oldName, TriangleType newName )
{
    for (unsigned int i=0U; i<li_triangle.size(); i++)
    {
        if (li_triangle[i].get_type() == oldName)
        {
            vector <Triangle> listSplit = li_triangle[i].split(axis,origin,newName);
            li_triangle[i]=listSplit[0];
            for(unsigned int i=1; i<listSplit.size(); i++)
            {
                li_triangle.push_back(listSplit[i]);
            }
        }
    }
}

void BuildingModel::repeat(TriangleType oldName, TriangleType newName)
{
    for (int i=0; i<li_triangle.size(); i++)
    {
        if (li_triangle[i].get_type() == newName)
        {
            Triangle temp = li_triangle[i].repeat(newName);
            li_triangle.push_back(temp);
        }
    }
}

void BuildingModel::scope()
{

}

void BuildingModel::join(BuildingModel buildingModel)
{
    for (unsigned int i=0U; i<buildingModel.li_triangle.size(); i++)
    {
        li_triangle.push_back(buildingModel.li_triangle[i]);
    }
}

void BuildingModel::to_obj()
{

}
