#include "Triangle.h"
#include "Point.h"
#include "catch.h"
#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include "gauss.h"
#include "matrix_methods.h"





Triangle::Triangle()
{

}

Triangle::Triangle(Point T_p1, Point T_p2, Point T_p3, TriangleType T_type)
{
    type= T_type; //wall, floor, roof
    p1=T_p1;
    p2=T_p2;
    p3=T_p3;
}

Triangle::~Triangle()
{

}

void Triangle::print()
{
    std::cout<<"---Triangle---"<<std::endl;
    std::cout<<"_P1_ : ";
    p1.print();
    std::cout<<"_P2_ : ";
    p2.print();
    std::cout<<"_P3_ : ";
    p3.print();
    std::cout<<"--------------"<<std::endl;
}

void Triangle::set_type(TriangleType newType)
{
    type = newType;
}

void Triangle::translate(double vec[3])
{
    p1.translate(vec);
    p2.translate(vec);
    p3.translate(vec);
}

void Triangle::size(double vec[3])
{
    p1.size(vec);
    p2.size(vec);
    p3.size(vec);
}

void Triangle::rotate(double vec[3], double angle)
{
    p1.rotate(vec, angle);
    p2.rotate(vec, angle);
    p3.rotate(vec, angle);
}

bool Triangle::is_equal(Triangle otherTriangle)
{
    bool b1 = (p1 == otherTriangle.get_p1() && p2 == otherTriangle.get_p2() && p3 == otherTriangle.get_p3());
    bool b2 = (p1 == otherTriangle.get_p1() && p2 == otherTriangle.get_p3() && p3 == otherTriangle.get_p2());
    bool b3 = (p1 == otherTriangle.get_p2() && p2 == otherTriangle.get_p3() && p3 == otherTriangle.get_p1());
    bool b4 = (p1 == otherTriangle.get_p2() && p2 == otherTriangle.get_p1() && p3 == otherTriangle.get_p3());
    bool b5 = (p1 == otherTriangle.get_p3() && p2 == otherTriangle.get_p2() && p3 == otherTriangle.get_p1());
    bool b6 = (p1 == otherTriangle.get_p3() && p2 == otherTriangle.get_p1() && p3 == otherTriangle.get_p2());
    return (b1 || b2 || b3 || b4 || b5 || b6);
}

vector <Triangle> Triangle::split(double axis[3], Point origin, TriangleType newName)
{
    vector <Triangle> result;

    //set AC coordinates
    double ac0 = p3.get_x() - p1.get_x();
    double ac1 = p3.get_y() - p1.get_y();
    double ac2 = p3.get_z() - p1.get_z();
    double AC[3][1];
    AC[0][0]=ac0;
    AC[1][0]=ac1;
    AC[2][0]=ac2;
    //set AB coordinates
    double ab0 = p2.get_x() - p1.get_x();
    double ab1 = p2.get_y() - p1.get_y();
    double ab2 = p2.get_z() - p1.get_z();
    double AB[3][1];
    AB[0][0]=ab0;
    AB[1][0]=ab1;
    AB[2][0]=ab2;
    //set BC coordinates
    double bc0 = p3.get_x() - p2.get_x();
    double bc1 = p3.get_y() - p2.get_y();
    double bc2 = p3.get_z() - p2.get_z();
    double BC[3][1];
    BC[0][0]=bc0;
    BC[1][0]=bc1;
    BC[2][0]=bc2;
    //set S coordinates
    double s0 = origin.get_x() + axis[0];
    double s1 = origin.get_y() + axis[1];
    double s2 = origin.get_z() + axis[2];
    double S[3][1];
    S[0][0]=s0;
    S[1][0]=s1;
    S[2][0]=s2;
    //set UX and UY
    double UX[3][1], UY[3][1];
    UX[0][0] = AB[0][0];
    UX[1][0] = AB[1][0];
    UX[2][0] = AB[2][0];
    UY[0][0] = AC[0][0];
    UY[1][0] = AC[1][0];
    UY[2][0] = AC[2][0];
    //calculate UZ = AB ^ AC
    double uz0 = ab1*ac2 - ab2*ac1;
    double uz1 = ab2*ac0 - ab0*ac2;
    double uz2 = ab0*ac1 - ab1*ac0;
    double UZ[3][1];
    UZ[0][0]=uz0;
    UZ[1][0]=uz1;
    UZ[2][0]=uz2;
    //set matrix M to transform carthesian coordinates in projected coordinates
    double mat[3][3];
    mat[0][0]=UX[0][0];
    mat[1][0]=UX[1][0];
    mat[2][0]=UX[2][0];
    mat[0][1]=UY[0][0];
    mat[1][1]=UY[1][0];
    mat[2][1]=UY[2][0];
    mat[0][2]=UZ[0][0];
    mat[1][2]=UZ[1][0];
    mat[2][2]=UZ[2][0];

    double M[3][3];
    invert_matrix(mat,M);

    //transform origin and S in the new set of coordinates
    double Sp[3][1], Op[3][1], St[3][1], Ot[3][1], O[3][1], T[3][1], T2[3][1];
    O[0][0]=origin.get_x();
    O[1][0]=origin.get_y();
    O[2][0]=origin.get_z();

    T[0][0]=p1.get_x();
    T[1][0]=p1.get_y();
    T[2][0]=p1.get_z();

    T2[0][0]=-p1.get_x();
    T2[1][0]=-p1.get_y();
    T2[2][0]=-p1.get_z();

    matrix_translation(T2,S,St);
    matrix_translation(T2,O,Ot);

    matrix_product(M,St,Sp);
    matrix_product(M,Ot,Op);

    //set 2D variables
    double Sp2[2][1], Op2[2][1], UXp2[2][1], UYp2[2][1], Ap2[2][1], Bp2[2][1], Cp2[2][2];
    Ap2[0][0]=0;
    Ap2[1][0]=0;

    Bp2[0][0]=1;
    Bp2[1][0]=0;

    Cp2[0][0]=0;
    Cp2[1][0]=1;

    Op2[0][0]=Op[0][0];
    Op2[1][0]=Op[1][0];

    Sp2[0][0]=Sp[0][0];
    Sp2[1][0]=Sp[1][0];

    UXp2[0][0]=1;
    UXp2[0][0]=0;

    UYp2[0][0]=0;
    UYp2[0][0]=1;

    //vector OS
    double OSp2[2][1];
    OSp2[0][0]=Sp2[0][0]-Op2[0][0];
    OSp2[1][0]=Sp2[1][0]-Op2[1][0];

    bool intersectUXp(false);
    bool intersectUYp(false);
    bool intersectUZp(false);

    Point ix;
    Point iy;
    Point iz;

    //exeption for line // at UXp2 or UYp2
    if (OSp2[1][0] == 0)
    {
        double constValue = Op2[1][0];

        if (constValue < 1 && constValue > 0)
        {
            intersectUYp = true;
            intersectUZp = true;

            double IYp[3][1];
            IYp[1][0]=constValue;
            IYp[0][0]=0;
            IYp[2][0]=0;
            double IZp[3][1];
            IZp[0][0]=constValue;
            IZp[1][0]=1-constValue;
            IZp[2][0]=0;

            double IY[3][1];
            double IZ[3][1];
            double IYt[3][1];
            double IZt[3][1];

            matrix_product(mat,IYp,IYt);
            matrix_product(mat,IZp,IZt);

            matrix_translation(T,IYt,IY);
            matrix_translation(T,IZt,IZ);

            iy.set_x(IY[0][0]);
            iy.set_y(IY[1][0]);
            iy.set_z(IY[2][0]);
            iz.set_x(IZ[0][0]);
            iz.set_y(IZ[1][0]);
            iz.set_z(IZ[2][0]);
        }
    }
    else if (OSp2[0][0] == 0)
    {
        //case x=constant
        double constValue = Op2[0][0];

        if (constValue < 1 && constValue > 0)
        {
            intersectUXp = true;
            intersectUZp = true;

            double IXp[3][1];
            IXp[0][0]=constValue;
            IXp[1][0]=0;
            IXp[2][0]=0;
            double IZp[3][1];
            IZp[0][0]=constValue;
            IZp[1][0]=1-constValue;
            IZp[2][0]=0;

            double IX[3][1];
            double IZ[3][1];
            double IXt[3][1];
            double IZt[3][1];
            matrix_product(mat,IXp,IXt);
            matrix_product(mat,IZp,IZt);

            matrix_translation(T,IXt,IX);
            matrix_translation(T,IZt,IZ);

            ix.set_x(IX[0][0]);
            ix.set_y(IX[1][0]);
            ix.set_z(IX[2][0]);
            iz.set_x(IZ[0][0]);
            iz.set_y(IZ[1][0]);
            iz.set_z(IZ[2][0]);
        }
    }
    else
    {
        //line equation ax+b
        double coeffLine = OSp2[1][0] / OSp2[0][0]; //a
        double originValue = Op2[1][0] - coeffLine*Op2[0][0]; //b

        //test UXp intersection
        double xUXp = -originValue / coeffLine;

        if (xUXp < 1 && xUXp > 0)
        {
            intersectUXp = true;
            double IXp[3][1];
            IXp[0][0]=xUXp;
            IXp[1][0]=0;
            IXp[2][0]=0;

            double IX[3][1];
            double IXt[3][1];
            matrix_product(mat,IXp,IXt);
            matrix_translation(T,IXt,IX);

            ix.set_x(IX[0][0]);
            ix.set_y(IX[1][0]);
            ix.set_z(IX[2][0]);
        }

        //test UYp intersection
        double yUYp = originValue;

        if (yUYp < 1 && yUYp > 0)
        {
            intersectUYp = true;
            double IYp[3][1];
            IYp[1][0]=yUYp;
            IYp[0][0]=0;
            IYp[2][0]=0;

            double IY[3][1];
            double IYt[3][1];
            matrix_product(mat,IYp,IYt);
            matrix_translation(T,IYt,IY);

            iy.set_x(IY[0][0]);
            iy.set_y(IY[1][0]);
            iy.set_z(IY[2][0]);
        }

        //test UZp intersection
        double xUZp = (originValue - 1) / (-1 - coeffLine);

        if (xUZp < 1 && xUZp > 0)
        {
            intersectUZp = true;
            double IZp[3][1];
            IZp[0][0]=xUZp;
            IZp[1][0]=1-xUZp;
            IZp[2][0]=0;

            double IZ[3][1];
            double IZt[3][1];

            matrix_product(mat,IZp,IZt);

            matrix_translation(T,IZt,IZ);

            iz.set_x(IZ[0][0]);
            iz.set_y(IZ[1][0]);
            iz.set_z(IZ[2][0]);
        }

    }



    if (intersectUXp && intersectUYp && intersectUZp)
    {
        result.push_back(*this);
        return result;
        std::cout << "all"<< std::endl;
    }
    else if (intersectUXp && intersectUYp)
    {
        Triangle tri1 = Triangle(p1,ix,iy,newName);
        Triangle tri2 = Triangle(p3,iy,p2,newName);
        Triangle tri3 = Triangle(p2,iy,ix,newName);
        result.push_back(tri1);
        result.push_back(tri2);
        result.push_back(tri3);
        std::cout << "x y"<< std::endl;
        return result;
    }
    else if (intersectUXp && intersectUZp)
    {
        Triangle tri1 = Triangle(p1,ix,p2,newName);
        Triangle tri2 = Triangle(p2,iz,ix,newName);
        Triangle tri3 = Triangle(p3,ix,iz,newName);
        result.push_back(tri1);
        result.push_back(tri2);
        result.push_back(tri3);
        std::cout << "x z"<< std::endl;
        return result;
    }
    else if (intersectUYp && intersectUZp)
    {
        Triangle tri1 = Triangle(p1,iz,iy,newName);
        Triangle tri2 = Triangle(p2,iz,p1,newName);
        Triangle tri3 = Triangle(p3,iy,iz,newName);
        result.push_back(tri1);
        result.push_back(tri2);
        result.push_back(tri3);
        std::cout << "y z"<< std::endl;
        return result;
    }
    else if (intersectUXp)
    {
        Triangle tri1 = Triangle(p1,ix,p3,newName);
        Triangle tri2 = Triangle(p2,p3,ix,newName);
        result.push_back(tri1);
        result.push_back(tri2);
        std::cout << "x"<< std::endl;
        return result;
    }
    else if (intersectUYp)
    {
        Triangle tri1 = Triangle(p1,p2,iy,newName);
        Triangle tri2 = Triangle(p2,p3,iy,newName);
        result.push_back(tri1);
        result.push_back(tri2);
        std::cout << "y"<< std::endl;
        return result;
    }
    else if (intersectUZp)
    {
        iz.print();
        Triangle tri1 = Triangle(p1,p2,iz,newName);
        Triangle tri2 = Triangle(p1,iz,p3,newName);
        result.push_back(tri1);
        result.push_back(tri2);
        std::cout << "z"<< std::endl;
        return result;
    }
    else
    {
        result.push_back(*this);
        std::cout << "cooool"<< std::endl;
        return result;
    }

}




/*
Triangle Triangle::repeat(TriangleType newName)
{
    return Triangle();
}
*/



/*
TEST_CASE("Triangle constructor + Getters are computed", "[Triangle] [get_p1] [get_p2] [get_p3] [get_type]")
{
    Point a =  Point(2,5,6);
    Point b =  Point(3,9,7);
    Point c =  Point(5,6,8);
    Triangle d = Triangle(a,b,c,WALL);

    REQUIRE(d.get_p1() == a);
    REQUIRE(d.get_p2() == b);
    REQUIRE(d.get_p3() == c);
    REQUIRE(d.get_type() == WALL);
}

/*
TEST_CASE("add_type are computed", "[add_type]")
{
    Point a =  Point(2,5,6);
    Point b =  Point(3,9,7);
    Point c =  Point(5,6,8);
    Triangle d = Triangle(a,b,c,WALL);
    d.set_type(ROOF);

    REQUIRE(d.get_type() == ROOF);
}

TEST_CASE("is_equal are computed", "[is_equal]")
{
    Point a =  Point(2,5,6);
    Point b =  Point(3,9,7);
    Point c =  Point(5,6,8);
    Triangle d = Triangle(a,b,c,WALL);
    Triangle e = Triangle(a,b,c,WALL);

    REQUIRE(d.is_equal(e));
}

TEST_CASE("translate triangle are computed", "[translate]")
{
    Point a =  Point(2,5,6);
    Point b =  Point(3,9,7);
    Point c =  Point(5,6,8);

    Triangle d = Triangle(a,b,c,WALL);

    double vec[3];
    vec[0] = 1;
    vec[1] = 2;
    vec[2] = 3;

    d.translate(vec);

    Point e =  Point(3,7,9);
    Point f =  Point(4,11,10);
    Point g =  Point(6,8,11);

    Triangle h = Triangle(e,f,g,WALL);

    REQUIRE(d.is_equal(h));
}

TEST_CASE("rotate triangle are computed", "[rotate]")
{

}

TEST_CASE("size triangle are computed", "[size]")
{
    Point a =  Point(2,5,6);
    Point b =  Point(3,9,7);
    Point c =  Point(5,6,8);

    Triangle d = Triangle(a,b,c,WALL);

    double vec[3];
    vec[0] = 1;
    vec[1] = 2;
    vec[2] = 3;

    d.size(vec);

    Point e =  Point(2,10,18);
    Point f =  Point(3,18,21);
    Point g =  Point(5,12,24);

    Triangle h = Triangle(e,f,g,WALL);

    REQUIRE(d.is_equal(h));

}

TEST_CASE("split Triangle are computed", "[split]")
{
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

    ltri = tri.split(*axis,origin,ROOF);

    Point iZ(1.5,1.5,0);

    REQUIRE(ltri.size()==2);
    REQUIRE(ltri[0].get_type()==ROOF);
    REQUIRE(ltri[0].get_p1()==p1);
    REQUIRE(ltri[0].get_p2()==p2);
    REQUIRE(ltri[0].get_p3()==iZ);
    REQUIRE(ltri[1].get_p3()==p3);
}
*/
