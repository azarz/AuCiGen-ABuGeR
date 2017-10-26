#include <iostream>
#include <vector>
//#include "catch.h"
using namespace std;

int gauss3P(double A[3][3], double B[3][1], double C[3][1])
{
    double a1;
    double a2;
    double a3;
    double b1;
    double b2;
    double b3;
    double c1;
    double c2;
    double c3;
    double B1;
    double B2;
    double B3;
    double L1;
    double L2;
    if (A[0][0]!=0)
    {
        L1=A[0][1]/A[0][0];
        L2=A[0][2]/A[0][0];
        if (A[1][1]==A[0][1]*L1 && A[1][2]==A[0][2]*L1 && A[2][1]==A[0][1]*L2 && A[2][2]==A[0][2]*L2 && B[1][0]==B[0][0]*L1 && B[2][0]==B[0][0]*L2)
        {
            cout << "straight lines" << endl;
            return 2;
        }
    }
    else if (A[0][1]!=0)
    {
        L1=A[0][1]/A[0][1];
        L2=A[0][2]/A[0][1];
        if (A[1][0]==A[0][0]*L1 && A[1][2]==A[0][2]*L1 && A[2][0]==A[0][0]*L2 && A[2][2]==A[0][2]*L2 && B[1][0]==B[0][0]*L1 && B[2][0]==B[0][0]*L2)
        {
            cout << "straight lines" << endl;
            return 2;
        }
    }
    else if (A[0][0]!=0)
    {
        L1=A[0][1]/A[0][2];
        L2=A[0][2]/A[0][2];
        if (A[1][1]==A[0][1]*L1 && A[1][0]==A[0][0]*L1 && A[2][1]==A[0][1]*L2 && A[2][0]==A[0][0]*L2 && B[1][0]==B[0][0]*L1 && B[2][0]==B[0][0]*L2)
        {
            cout << "straight lines" << endl;
            return 2;
        }
    }


    //resolve
    if (A[0][0]==0 && A[1][0]==0 && A[2][0]==0)
    {
        cout << "no solution 1" << endl;
        return 0;
    }
    else if (A[0][0]!=0)
    {
        a1=A[0][0];
        a2=A[0][1];
        a3=A[0][2];
         B1=B[0][0];

        b1=A[1][0];
        b2=A[1][1];
        b3=A[1][2];
         B2=B[1][0];

        c1=A[2][0];
        c2=A[2][1];
        c3=A[2][2];
         B3=B[2][0];
    }
    else if (A[0][0]==0 && A[1][0]!=0)
    {
        a1=A[1][0];
        a2=A[1][1];
        a3=A[1][2];
         B1=B[1][0];

        b1=A[0][0];
        b2=A[0][1];
        b3=A[0][2];
         B2=B[0][0];

        c1=A[2][0];
        c2=A[2][1];
        c3=A[2][2];
         B3=B[2][0];
    }
    else if (A[0][0]==0 && A[1][0]==0 && A[2][0]!=0)
    {
        a1=A[2][0];
        a2=A[2][1];
        a3=A[2][2];
         B1=B[2][0];

        b1=A[1][0];
        b2=A[1][1];
        b3=A[1][2];
         B2=B[1][0];

        c1=A[0][0];
        c2=A[0][1];
        c3=A[0][2];
         B3=B[0][0];
    }
    double x;
    double y;
    double z;
    //résolution a1 toujour !=0
    if ((a1*b2-b1*a2)!=0 && (a1*b2-b1*a2)*(a1*c3-c1*a3)-(a1*c2-c1*a2)*(a1*b3-b1*a3)!=0)
    {
        z=((a1*b2-b1*a2)*(a1*B3-c1*B1)-(a1*c2-c1*a2)*(a1*B2-b1*B1))/((a1*b2-b1*a2)*(a1*c3-c1*a3)-(a1*c2-c1*a2)*(a1*b3-b1*a3));
        y=(a1*B2-b1*B1-(a1*b3-b1*a3)*z)/(a1*b2-b1*a2);
        x=(B1-a3*z-a2*y)/a1;
        cout << "solution 2" << endl;
    }
    else if ((a1*b2-b1*a2)!=0 && (a1*b2-b1*a2)*(a1*c3-c1*a3)-(a1*c2-c1*a2)*(a1*b3-b1*a3)==0)
    {
        cout << "no solution 3" << endl;
        return 0;
    }
    else if ((a1*b2-b1*a2)==0 && (a1*c2-c1*a2)==0)
    {
        cout << "no solution 4" << endl;
        return 0;
    }
    else if ((a1*b2-b1*a2)==0 && (a1*c2-c1*a2)!=0 && (a1*b3-b1*a3)==0)
    {
        cout << "no solution 5" << endl;
        return 0;
    }
    else if ((a1*b2-b1*a2)==0 && (a1*c2-c1*a2)!=0 && (a1*b3-b1*a3)!=0)
    {
        z=(a1*B2-b1*B1)/(a1*b3-b1*a3);
        y=(a1*B3-c1*B1-(a1*c3-c1*a3)*z)/(a1*c2-c1*a2);
        x=(B1-a3*z-a2*y)/a1;
    }
    C[0][0]=x;
    C[1][0]=y;
    C[2][0]=z;
    cout << "( "<< x << ", "<< y << ", " << z << ")"<<endl;
    return 1;
}
