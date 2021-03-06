#include "Triangle.h"

#include <vector>
//#include <string>
#include <cmath>
#include <iostream>

#include "Point.h"

//#include "gauss.h"
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
    double Sp2[2][1], Op2[2][1];

    Op2[0][0]=Op[0][0];
    Op2[1][0]=Op[1][0];

    Sp2[0][0]=Sp[0][0];
    Sp2[1][0]=Sp[1][0];

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
    }
    else if (intersectUXp && intersectUYp)
    {
        Triangle tri1 = Triangle(p1,ix,iy,newName);
        Triangle tri2 = Triangle(p3,iy,p2,newName);
        Triangle tri3 = Triangle(p2,iy,ix,newName);
        result.push_back(tri1);
        result.push_back(tri2);
        result.push_back(tri3);
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
        return result;
    }
    else if (intersectUXp)
    {
        Triangle tri1 = Triangle(p1,ix,p3,newName);
        Triangle tri2 = Triangle(p2,p3,ix,newName);
        result.push_back(tri1);
        result.push_back(tri2);
        return result;
    }
    else if (intersectUYp)
    {
        Triangle tri1 = Triangle(p1,p2,iy,newName);
        Triangle tri2 = Triangle(p2,p3,iy,newName);
        result.push_back(tri1);
        result.push_back(tri2);
        return result;
    }
    else if (intersectUZp)
    {
        Triangle tri1 = Triangle(p1,p2,iz,newName);
        Triangle tri2 = Triangle(p1,iz,p3,newName);
        result.push_back(tri1);
        result.push_back(tri2);
        return result;
    }
    else
    {
        result.push_back(*this);
        return result;
    }
}

Triangle Triangle::repeat(TriangleType newName)
{
    return Triangle();
}

