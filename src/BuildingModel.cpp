#include "BuildingModel.h"
#include "Triangle.h"
#include "Point.h"
#include "Parcel.h"
#include <vector>
#include <iostream>

#include "catch.h"

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
            for(int i=1; i<listSplit.size(); i++)
            {
                li_triangle.push_back(listSplit[i]);
            }
        }
    }
}

/*
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
*/

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


/*

TEST_CASE("BuildingModel and Getters are computed", "[BuildingModel]")
{
    Point p1(1,1,0);
    Point p2(2,1,0);
    Point p3(1,2,0);

    Triangle tri(p1,p2,p3,WALL);
    vector<Triangle> ltri;
    ltri.push_back(tri);

    Parcel par;
    BuildingModel test = BuildingModel(ltri,&par);

    REQUIRE(test.get_li_triangle()[0].is_equal(tri));
    //REQUIRE(test.get_parcel() ==)
}

TEST_CASE("translate BuildingModel", "[translate]")
{
    Point a =  Point(2,5,6);
    Point b =  Point(3,9,7);
    Point c =  Point(5,6,8);

    Triangle d = Triangle(a,b,c,WALL);

    double vec[3];
    vec[0] = 1;
    vec[1] = 2;
    vec[2] = 3;

    Point e =  Point(3,7,9);
    Point f =  Point(4,11,10);
    Point g =  Point(6,8,11);

    Triangle h = Triangle(e,f,g,FLOOR);

    vector<Triangle> ltri;
    ltri.push_back(d);
    ltri.push_back(h);

    Parcel par;
    BuildingModel test = BuildingModel(ltri,&par);

    test.translate(vec,WALL);

    REQUIRE(test.get_li_triangle()[0].is_equal(test.get_li_triangle()[1]));
}

TEST_CASE("rotate BuildingModel", "[rotate]")
{

}

TEST_CASE("size BuildingModel", "[size]")
{

}

TEST_CASE("split BuildingModel are computed", "[spli]")
{
    // simple intersection

    Point p1(1,1,0);
    Point p2(2,1,0);
    Point p3(1,2,0);

    Triangle tri(p1,p2,p3,WALL);

    Point origin(0,0,0);
    double axis[3][1];
    axis[0][0] = 1;
    axis[1][0] = 1;
    axis[2][0] = 0;

    vector<Triangle> ltri;
    ltri.push_back(tri);

    Parcel par;
    BuildingModel test = BuildingModel(ltri,&par);

    test.split(*axis,origin,WALL,ROOF);

    Point iZ(1.5,1.5,0);

    REQUIRE(test.get_li_triangle().size()==2);
    REQUIRE(test.get_li_triangle()[0].get_type()==ROOF);
    REQUIRE(test.get_li_triangle()[0].get_p1()==p1);
    REQUIRE(test.get_li_triangle()[0].get_p2()==p2);
    REQUIRE(test.get_li_triangle()[0].get_p3()==iZ);
    REQUIRE(test.get_li_triangle()[1].get_p3()==p3);

    // double intersection (d)

    Point dp1(1,1,0);
    Point dp2(2,1,0);
    Point dp3(1,2,0);

    Triangle dtri(dp1,dp2,dp3,WALL);

    Point dorigin(0,2.5,0);
    double daxis[3][1];
    daxis[0][0] = 1;
    daxis[1][0] = -1;
    daxis[2][0] = 8;

    vector<Triangle> dltri;
    dltri.push_back(dtri);

    Parcel dpar;
    BuildingModel dtest = BuildingModel(dltri,&dpar);

    dtest.split(*daxis,dorigin,WALL,ROOF);

    Point diX(1.5,1,0);
    Point diY(1,1.5,0);

    REQUIRE(dtest.get_li_triangle().size()==3);
    REQUIRE(dtest.get_li_triangle()[0].get_type()==ROOF);
    REQUIRE(dtest.get_li_triangle()[0].get_p1()==dp1);
    REQUIRE(dtest.get_li_triangle()[0].get_p2()==diX);
    REQUIRE(dtest.get_li_triangle()[0].get_p3()==diY);
    REQUIRE(dtest.get_li_triangle()[2].get_p1()==dp2);
    REQUIRE(dtest.get_li_triangle()[1].get_p1()==dp3);

    // no intersection

    Point np1(1,1,0);
    Point np2(2,1,0);
    Point np3(1,2,0);

    Triangle ntri(np1,np2,np3,WALL);

    Point norigin(0,0,0);
    double naxis[3][1];
    naxis[0][0] = 1;
    naxis[1][0] = -1;
    naxis[2][0] = 8;

    vector<Triangle> nltri;
    nltri.push_back(ntri);

    Parcel npar;
    BuildingModel ntest = BuildingModel(nltri,&npar);

    ntest.split(*naxis,norigin,WALL,ROOF);

    REQUIRE(ntest.get_li_triangle().size()==1);
    REQUIRE(ntest.get_li_triangle()[0].get_type()==WALL);
    REQUIRE(ntest.get_li_triangle()[0].get_p1()==np1);
    REQUIRE(ntest.get_li_triangle()[0].get_p2()==np2);
    REQUIRE(ntest.get_li_triangle()[0].get_p3()==np3);

    // ux issue

    Point xp1(1,1,0);
    Point xp2(2,1,0);
    Point xp3(1,2,0);

    Triangle xtri(xp1,xp2,xp3,WALL);

    Point xorigin(0,1.5,0);
    double xaxis[3][1];
    xaxis[0][0] = 1;
    xaxis[1][0] = 0;
    xaxis[2][0] = 8;

    vector<Triangle> xltri;
    xltri.push_back(xtri);

    Parcel xpar;
    BuildingModel xtest = BuildingModel(xltri,&xpar);

    xtest.split(*xaxis,xorigin,WALL,ROOF);

    Point xiY(1,1.5,0);
    Point xiZ(1.5,1.5,0);

    REQUIRE(xtest.get_li_triangle().size()==3);
    REQUIRE(xtest.get_li_triangle()[0].get_type()==ROOF);
    REQUIRE(xtest.get_li_triangle()[0].get_p1()==xp1);
    REQUIRE(xtest.get_li_triangle()[0].get_p2()==xiZ);
    REQUIRE(xtest.get_li_triangle()[0].get_p3()==xiY);
    REQUIRE(xtest.get_li_triangle()[1].get_p1()==xp2);
    REQUIRE(xtest.get_li_triangle()[2].get_p1()==xp3);

    // uy issue

    Point yp1(1,1,0);
    Point yp2(2,1,0);
    Point yp3(1,2,0);

    Triangle ytri(yp1,yp2,yp3,WALL);

    Point yorigin(1.5,0,0);
    double yaxis[3][1];
    yaxis[0][0] = 0;
    yaxis[1][0] = 1;
    yaxis[2][0] = 0;

    vector<Triangle> yltri;
    yltri.push_back(ytri);

    Parcel ypar;
    BuildingModel ytest = BuildingModel(yltri,&ypar);

    ytest.split(*yaxis,yorigin,WALL,ROOF);

    Point yiX(1.5,1,0);
    Point yiZ(1.5,1.5,0);

    REQUIRE(ytest.get_li_triangle().size()==3);
    REQUIRE(ytest.get_li_triangle()[0].get_type()==ROOF);
    REQUIRE(ytest.get_li_triangle()[0].get_p1()==yp1);
    REQUIRE(ytest.get_li_triangle()[0].get_p2()==yiX);
    REQUIRE(ytest.get_li_triangle()[0].get_p3()==yp2);
    REQUIRE(ytest.get_li_triangle()[2].get_p3()==yiZ);
    REQUIRE(ytest.get_li_triangle()[2].get_p1()==yp3);
}

*/
