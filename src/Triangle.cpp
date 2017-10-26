#include "Triangle.h"
#include "Point.h"
#include "catch.h"
#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include "gauss.h"

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

void Triangle::add_type(TriangleType newType)
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
    double ac1 = p3.get_x() - p1.get_x();
    double ac2 = p3.get_y() - p1.get_y();
    double ac3 = p3.get_z() - p1.get_z();
    //set AB coordinates
    double ab1 = p2.get_x() - p1.get_x();
    double ab2 = p2.get_y() - p1.get_y();
    double ab3 = p2.get_z() - p1.get_z();
    //set BC coordinates
    double bc1 = p3.get_x() - p2.get_x();
    double bc2 = p3.get_y() - p2.get_y();
    double bc3 = p3.get_z() - p2.get_z();
    //set S coordinates
    double x = origin.get_x() + axis[0];
    double y = origin.get_y() + axis[1];
    double z = origin.get_z() + axis[2];
    //init S' coordinates
    double x1;
    double y1;
    double z1;

    //calculate V = AC ^ AB
    double v1 = ac2*ab3 - ac3*ab2;
    double v2 = ac3*ab1 - ac1*ab3;
    double v3 = ac1*ab2 - ac2*ab1;

    //set matrix of the equation
    double A[3][3];
    A[0][0] = ac1;
    A[0][1] = ac2;
    A[0][2] = ac3;
    A[1][0] = ab1;
    A[1][1] = ab2;
    A[1][2] = ab3;
    A[2][0] = v1;
    A[2][1] = v2;
    A[2][2] = v3;

    //set result of the equation for S'
    double B[3][1];
    B[0][0] = ac1*x + ac2*y + ac3*z;
    B[1][0] = ab1*x + ab2*y + ab3*z;
    B[2][0] = v1*p1.get_x() + v2*p1.get_y() + v3*p2.get_z();

    //set S' array
    double X[3][1];
    //fill S' array
    gauss3P(A,B,X);

    //set result of the equation for origin (O)
    double B2[3][1];
    B[0][0] = ac1*origin.get_x() + ac2*origin.get_y() + ac3*origin.get_z();
    B[1][0] = ab1*origin.get_x() + ab2*origin.get_y() + ab3*origin.get_z();
    B[2][0] = v1*p1.get_x() + v2*p1.get_y() + v3*p2.get_z();

    //set O' array
    double X2[3][1];
    //fill O' array
    int score = gauss3P(A,B2,X2);

    //set an array for the projected line
    double d1 = X2[0][0] - X[0][0];
    double d2 = X2[1][0] - X[1][0];
    double d3 = X2[2][0] - X[2][0];

    //set matrix of intersection between the projected line and a side of the triangle (AB)
    double MDAB[3][3];
    MDAB[0][0] = d1;
    MDAB[0][1] = - ab1;
    MDAB[0][2] = 0;
    MDAB[1][0] = d2;
    MDAB[1][1] = - ab2;
    MDAB[1][2] = 0;
    MDAB[2][0] = d3;
    MDAB[2][1] = - ab3;
    MDAB[2][2] = 0;
    //set matrix of intersection between the projected line and a side of the triangle (BC)
    double MDBC[3][3];
    MDBC[0][0] = d1;
    MDBC[0][1] = - bc1;
    MDBC[0][2] = 0;
    MDBC[1][0] = d2;
    MDBC[1][1] = - bc2;
    MDBC[1][2] = 0;
    MDBC[2][0] = d3;
    MDBC[2][1] = - bc3;
    MDBC[2][2] = 0;
    //set matrix of intersection between the projected line and a side of the triangle (CA)
    double MDCA[3][3];
    MDCA[0][0] = d1;
    MDCA[0][1] = ac1;
    MDCA[0][2] = 0;
    MDCA[1][0] = d2;
    MDCA[1][1] = ac2;
    MDCA[1][2] = 0;
    MDCA[2][0] = d3;
    MDCA[2][1] = ac3;
    MDCA[2][2] = 0;

    //set the results of the different intersections
    double BDAB[3][1];
    BDAB[0][0] = p1.get_x() - X[0][0];
    BDAB[1][1] = p1.get_y() - X[1][0];
    BDAB[2][0] = p1.get_z() - X[2][0];

    double BDBC[3][1];
    BDBC[0][0] = p2.get_x() - X[0][0];
    BDBC[1][1] = p2.get_y() - X[1][0];
    BDBC[2][0] = p2.get_z() - X[2][0];

    double BDCA[3][1];
    BDCA[0][0] = p3.get_x() - X[0][0];
    BDCA[1][1] = p3.get_y() - X[1][0];
    BDCA[2][0] = p3.get_z() - X[2][0];

    //init the parameters of the parametric equation for the intersection
    double paramDAB[3][1];
    double paramDBC[3][1];
    double paramDCA[3][1];

    //fill param array
    int scoreAB = gauss3P(MDAB,BDAB,paramDAB);
    int scoreBC = gauss3P(MDBC,BDBC,paramDBC);
    int scoreCA = gauss3P(MDCA,BDCA,paramDCA);

    paramDAB[2][0] = scoreAB;
    paramDBC[2][0] = scoreBC;
    paramDCA[2][0] = scoreCA;

    // init coordinates of intersection points
    double PDAB[3][1];
    double QDAB[3][1];
    double PDBC[3][1];
    double QDBC[3][1];
    double PDCA[3][1];
    double QDCA[3][1];

    //if the projected line contains a side of the triangle it's useless to split it
    if (paramDAB[2][0] == 2 || paramDBC[2][0] == 2 || paramDCA[2][0] == 2)
    {
        result.push_back(*this);
        return result;
    }
    //if there is a side parallel to the projected line it's useless to search an intersection
    else if (paramDAB[2][0] == 1)
    {
            //init intersection points coordinates
        double P[3][1];
        double Q[3][1];

        P[0][0] = d1*paramDBC[0][0] + X[0][0];
        P[1][0] = d2*paramDBC[0][0] + X[1][0];
        P[2][0] = d3*paramDBC[0][0] + X[2][0];

        Q[0][0] = d1*paramDCA[0][0] + X[0][0];
        Q[1][0] = d2*paramDCA[0][0] + X[1][0];
        Q[2][0] = d3*paramDCA[0][0] + X[2][0];

        double bp1 = P[0][0] - p2.get_x() ;
        double bp2 = P[1][0] - p2.get_y() ;
        double bp3 = P[2][0] - p2.get_z() ;

        if(bp1/bc1 < 1 && bp1/bc1 > 0 && bp2/bc2 < 1 && bp2/bc2 > 0 && bp3/bc3 < 1 && bp3/bc3 > 0)
        {
            result.push_back(Triangle(p1,p2,Point(P[0][0],P[1][0],P[2][0]),newName));
            result.push_back(Triangle(p2,Point(P[0][0],P[1][0],P[2][0]),Point(Q[0][0],Q[1][0],Q[2][0]),newName));
            result.push_back(Triangle(Point(P[0][0],P[1][0],P[2][0]),p3,Point(Q[0][0],Q[1][0],Q[2][0]),newName));
            return result;
        }
        else
        {
            result.push_back(*this);
            return result;
        }
    }
    else if (paramDBC[2][0] == 1)
    {
            //init intersection points coordinates
        double P[3][1];
        double Q[3][1];

        P[0][0] = d1*paramDAB[0][0] + X[0][0];
        P[1][0] = d2*paramDAB[0][0] + X[1][0];
        P[2][0] = d3*paramDAB[0][0] + X[2][0];

        Q[0][0] = d1*paramDCA[0][0] + X[0][0];
        Q[1][0] = d2*paramDCA[0][0] + X[1][0];
        Q[2][0] = d3*paramDCA[0][0] + X[2][0];

        double ap1 = P[0][0] - p1.get_x() ;
        double ap2 = P[1][0] - p1.get_y() ;
        double ap3 = P[2][0] - p1.get_z() ;

        if (ap1/ab1 < 1 && ap1/ab1 > 0 && ap2/ab2 < 1 && ap2/ab2 > 0 && ap3/ab3 < 1 && ap3/ab3 > 0)
        {
            result.push_back(Triangle(p1,Point(P[0][0],P[1][0],P[2][0]),Point(Q[0][0],Q[1][0],Q[2][0]),newName));
            result.push_back(Triangle(p2,p3,Point(P[0][0],P[1][0],P[2][0]),newName));
            result.push_back(Triangle(Point(P[0][0],P[1][0],P[2][0]),p3,Point(Q[0][0],Q[1][0],Q[2][0]),newName));
            return result;
        }
        else
        {
            result.push_back(*this);
            return result;
        }
    }
    else if (paramDCA[2][0] == 1)
    {
            //init intersection points coordinates
        double P[3][1];
        double Q[3][1];

        P[0][0] = d1*paramDBC[0][0] + X[0][0];
        P[1][0] = d2*paramDBC[0][0] + X[1][0];
        P[2][0] = d3*paramDBC[0][0] + X[2][0];

        Q[0][0] = d1*paramDAB[0][0] + X[0][0];
        Q[1][0] = d2*paramDAB[0][0] + X[1][0];
        Q[2][0] = d3*paramDAB[0][0] + X[2][0];

        double bp1 = P[0][0] - p2.get_x() ;
        double bp2 = P[1][0] - p2.get_y() ;
        double bp3 = P[2][0] - p2.get_z() ;

       if(bp1/bc1 < 1 && bp1/bc1 > 0 && bp2/bc2 < 1 && bp2/bc2 > 0 && bp3/bc3 < 1 && bp3/bc3 > 0)
        {
            result.push_back(Triangle(p1,Point(P[0][0],P[1][0],P[2][0]),p3,newName));
            result.push_back(Triangle(Point(P[0][0],P[1][0],P[2][0]),p1,Point(Q[0][0],Q[1][0],Q[2][0]),newName));
            result.push_back(Triangle(p2,Point(P[0][0],P[1][0],P[2][0]),Point(Q[0][0],Q[1][0],Q[2][0]),newName));
            return result;
        }
        else
        {
            result.push_back(*this);
            return result;
        }
    }

    else
    {
        double Pt[3][1];
        double Qt[3][1];
        double Rt[3][1];

        Pt[0][0] = d1*paramDAB[0][0] + X[0][0];
        Pt[1][0] = d2*paramDAB[0][0] + X[1][0];
        Pt[2][0] = d3*paramDAB[0][0] + X[2][0];

        Qt[0][0] = d1*paramDBC[0][0] + X[0][0];
        Qt[1][0] = d2*paramDBC[0][0] + X[1][0];
        Qt[2][0] = d3*paramDBC[0][0] + X[2][0];

        Rt[0][0] = d1*paramDCA[0][0] + X[0][0];
        Rt[1][0] = d2*paramDCA[0][0] + X[1][0];
        Rt[2][0] = d3*paramDCA[0][0] + X[2][0];

        Point P(Pt[0][0],Pt[1][0],Pt[2][0]);
        Point R(Rt[0][0],Rt[1][0],Rt[2][0]);
        Point Q(Qt[0][0],Qt[1][0],Qt[2][0]);

        double ap1 = P.get_x() - p1.get_x() ;
        double ap2 = P.get_y() - p1.get_y() ;
        double ap3 = P.get_z() - p1.get_z() ;

        double bq1 = Q.get_x() - p2.get_x() ;
        double bq2 = Q.get_y() - p2.get_y() ;
        double bq3 = Q.get_z() - p2.get_z() ;

        double cr1 = R.get_x() - p3.get_x() ;
        double cr2 = R.get_y() - p3.get_y() ;
        double cr3 = R.get_z() - p3.get_z() ;

        if (P==R && R==Q)
        {
            result.push_back(*this);
            return result;
        }

        else if (P==R)
        {
            result.push_back(Triangle(p1,p2,Q,newName));
            result.push_back(Triangle(p1,Q,p3,newName));
            return result;
        }
        else if (P==Q)
        {
            result.push_back(Triangle(p1,p2,R,newName));
            result.push_back(Triangle(p3,R,p2,newName));
            return result;
        }
        else if (Q==R)
        {
            result.push_back(Triangle(p1,P,p3,newName));
            result.push_back(Triangle(p2,p3,P,newName));
            return result;
        }
        else if ((!(ap1/ab1 < 1 && ap1/ab1 > 0 && ap2/ab2 < 1 && ap2/ab2 > 0 && ap3/ab3 < 1 && ap3/ab3 > 0)) && (!(bq1/bc1 < 1 && bq1/bc1 > 0 && bq2/bc2 < 1 && bq2/bc2 > 0 && bq3/bc3 < 1 && bq3/bc3 > 0)) && (!(-cr1/ac1 < 1 && -cr1/ac1 > 0 && -cr2/ac2 < 1 && -cr2/ac2 > 0 && -cr3/ac3 < 1 && -cr3/ac3 > 0)))
        {
            result.push_back(*this);
            return result;
        }
        else if ((ap1/ab1 < 1 && ap1/ab1 > 0 && ap2/ab2 < 1 && ap2/ab2 > 0 && ap3/ab3 < 1 && ap3/ab3 > 0) && (bq1/bc1 < 1 && bq1/bc1 > 0 && bq2/bc2 < 1 && bq2/bc2 > 0 && bq3/bc3 < 1 && bq3/bc3 > 0))
        {
            result.push_back(Triangle(p1,P,p3,newName));
            result.push_back(Triangle(p2,Q,P,newName));
            result.push_back(Triangle(p3,P,Q,newName));
            return result;
        }
        else if ((ap1/ab1 < 1 && ap1/ab1 > 0 && ap2/ab2 < 1 && ap2/ab2 > 0 && ap3/ab3 < 1 && ap3/ab3 > 0) && (-cr1/ac1 < 1 && -cr1/ac1 > 0 && -cr2/ac2 < 1 && -cr2/ac2 > 0 && -cr3/ac3 < 1 && -cr3/ac3 > 0))
        {
            result.push_back(Triangle(p1,P,R,newName));
            result.push_back(Triangle(p2,p3,P,newName));
            result.push_back(Triangle(p3,R,P,newName));
            return result;
        }
        else if ((bq1/bc1 < 1 && bq1/bc1 > 0 && bq2/bc2 < 1 && bq2/bc2 > 0 && bq3/bc3 < 1 && bq3/bc3 > 0) && (-cr1/ac1 < 1 && -cr1/ac1 > 0 && -cr2/ac2 < 1 && -cr2/ac2 > 0 && -cr3/ac3 < 1 && -cr3/ac3 > 0))
        {
            result.push_back(Triangle(p1,p2,Q,newName));
            result.push_back(Triangle(p1,Q,R,newName));
            result.push_back(Triangle(p3,R,Q,newName));
            return result;
        }
        else
        {
            std::cout << "Je ny avais pas pensé !" << std::endl;
        }

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

TEST_CASE("add_type are computed", "[add_type]")
{
    Point a =  Point(2,5,6);
    Point b =  Point(3,9,7);
    Point c =  Point(5,6,8);
    Triangle d = Triangle(a,b,c,WALL);
    d.add_type(ROOF);

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
    Point a =  Point(2,5,6);
    Point b =  Point(3,9,7);
    Point c =  Point(5,6,8);

    Triangle d = Triangle(a,b,c,WALL);

    double vec[3];
    vec[0] = 0;
    vec[1] = 0;
    vec[2] = 1;

    double angle = M_PI_2;

    d.rotate(vec,angle);

    Point e =  Point(-5,2,6);
    Point f =  Point(-9,3,7);
    Point g =  Point(-6,5,8);

    Triangle h = Triangle(e,f,g,WALL);

    //REQUIRE(d.is_equal(h));
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
*/
