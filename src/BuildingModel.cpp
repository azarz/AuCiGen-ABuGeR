#include "BuildingModel.h"
#include "Triangle.h"
#include "Point.h"
#include "Parcel.h"
#include <vector>
#include <iostream>

BuildingModel::BuildingModel()
{
    //ctor
}

BuildingModel::~BuildingModel()
{
    //dtor
}
void BuildingModel::translate(double vec[3], TriangleType name)
{
    for (int i=0; i<li_triangle.size(); i++)
    {
        if (li_triangle[i].get_type() == name)
        {
            li_triangle[i].translate(vec);
        }
    }
}
void BuildingModel::rotate(double vec[3], double angle, TriangleType name)
{
    for (int i=0; i<li_triangle.size(); i++)
    {
        if (li_triangle[i].get_type() == name)
        {
            li_triangle[i].rotate(vec,angle);
        }
    }
}
void BuildingModel::size(double vec[3], TriangleType name)
{
    for (int i=0; i<li_triangle.size(); i++)
    {
        if (li_triangle[i].get_type() == name)
        {
            li_triangle[i].size(vec);
        }
    }
}
/*
void BuildingModel::split(double axis[3], Point origin, string oldName, string newName )
{
    for (int i=0; i<li_triangle.size(); i++)
    {
        int j=0;
        bool b = true;
        while (j<li_triangle[i].get_type().size() && b)
        {
            if (li_triangle[i].get_type()[j] == oldName){b=false;}
            j++;
        }
        if (!b)
        {
            Triangle[2] listSplit = li_triangle[i].split(axis,origin,newName);
            li_triangle[i]=listSplit[0];
            li_triangle.push_back(listSplit[1]);
        }
    }
}
void BuildingModel::repeat(string oldName, string newName)
{
    for (int i=0; i<li_triangle.size(); i++)
    {
        int j=0;
        bool b = true;
        while (j<li_triangle[i].get_type().size() && b)
        {
            if (li_triangle[i].get_type()[j] == oldName){b=false;}
            j++;
        }
        if (!b)
        {
            Triangle temp = li_triangle[i].repeat(newName);
            li_triangle.push_back(temp);
        }
    }
}
void BuildingModel::scope()
{

}
BuildingModel BuildingModel::join()
{

}
BuildingModel BuildingModel::creat_roof()
{

}

void BuildingModel::to_obj()
{

}
*/
