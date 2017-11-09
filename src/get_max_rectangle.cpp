#include "get_max_rectangle.h"

#include "ogrsf_frmts.h"
#include <iostream>
#include <vector>
using namespace std;

#include <stdio.h>
#include <math.h>

int larger_rectangle_included (vector<int> b, int N, int M, vector<int>& lim, int best_area)
{
    int llx =0;
    int lly =0;
    int urx;
    int ury;
    int best_11x = 0;
    int best_11y = 0;
    int best_urx = 0;
    int best_ury = 0;
    while  (llx < N && (N-llx)*M>best_area )
    {
        lly=0;
        while (lly<M && (N-llx)*(M-lly)> best_area)
        {
            //cout<<"llx = "<<llx<<" lly = "<< lly <<" value = "<< b.at(llx*M+lly)<<endl;
            if (b.at(llx*M+lly)!=0)
            {
                int a = floor(best_area/N);
                for (urx = llx+a; urx < N; urx++)
                {
                    ury = lly+floor(best_area/(urx-llx+1));
                    while (ury < M && all_ones(llx,lly, urx, ury, b, M))
                    {
                        int area_temp=area(llx,lly, urx, ury );
                        if (area_temp>best_area)
                        {
                                best_11x = llx;
                                best_11y = lly;
                                best_urx = urx;
                                best_ury = ury;
                                best_area=area_temp;
                        }
                        ury ++;
                    }
                }
            }
            lly++;
        }
        llx++;
    }
    lim.push_back (best_11x);lim.push_back (best_11y);
    lim.push_back (best_11x);lim.push_back (best_ury);
    lim.push_back (best_urx);lim.push_back (best_ury);
    lim.push_back (best_urx);lim.push_back (best_11y);
    lim.push_back (best_11x);lim.push_back (best_11y);
    return best_area;
}
int area(int llx, int lly, int urx, int ury)
{
    if (llx>urx || lly>ury) // If ur is left of or
        return 0;               // below 11: return 0
    else
        return (urx-llx+1)*(ury-lly+1);
}
int areaL(int llx, int lly, int urx, int ury, vector<int> b, int M, vector<int>& not_lim)
{
    if (llx>urx || lly>ury) // If ur is left of or
        return 0;               // below 11: return 0
    int sum=0;
    for (int x =llx; x<=urx; x++)
    {
        for (int y=lly; y<=ury; y++)
        {
            if (!(x>=not_lim.at(0) && x<=not_lim.at(2) && y>=not_lim.at(1) && y<=not_lim.at(3)))
                {sum+=b.at(x*M+y);}
        }
    }
        return sum;
}
bool all_ones(int llx, int lly, int urx, int ury, vector<int> b, int M)
{
    for (int x = llx; x<=urx; x++)
    {
        for (int y = lly; y<=ury; y++)
        {
            if (b.at(x*M+y)==0)
                return false;
        }
    }
    return true;
}

bool L_ones(int llx, int lly, int urx, int ury, vector<int> b, int M, vector<int>& lim, vector<int>& not_lim)
{
    int x=llx;
    int y=lly;
    int xmin, ymin, xmax, ymax;
    if (all_ones(llx,lly,urx,ury, b, M)) // all 0 => no best L possible
        {//cout<<"1"<<endl;
        return false;}
    //find the first 0
    while (b.at(x*M+y)==1 && x<=urx)
    {
        y++;
        if (y>ury)
        {
            x++;
            y=lly;
        }
    }
    if (x>urx) // no 0 on b
        {//cout<<"2"<<endl;
        return false;}
    else if (x==llx && y==lly)//first 0 on (0, 0)
    {
        //first 1 on line llx
        while (b.at(x*M+y)==0 && y<=ury)
        {
            y++;
        }
        if (y==ury+1)
            {//cout<<"3"<<endl;
            return false;}
        int ymax=y;
        //first 0 on column lly
        while (b.at(x*M+lly)==0 && x<=urx)
        {
            x++;
        }
        if (x==urx+1)
            {//cout<<"4"<<endl;
            return false;}
        int xmax=x;
        //vertical ONE rectangle
        while(!all_ones(llx, ymax, urx, ury, b, M) && ymax<ury)
        {
            ymax++;
        }
        if (ymax==ury)
            {//cout<<"5"<<endl;
            return false;}

        //horizontal ONE rectangle
        while(!all_ones(xmax, lly, urx, ymax, b, M) && xmax<urx)
        {
            xmax++;
        }
        if (xmax==urx)
            {//cout<<"6"<<endl;
            return false;}

        lim.push_back(llx); lim.push_back(ymax);
        lim.push_back(llx); lim.push_back(ury);
        lim.push_back(urx); lim.push_back(ury);
        lim.push_back(urx); lim.push_back(lly);
        lim.push_back(xmax+1); lim.push_back(lly);
        lim.push_back(xmax+1); lim.push_back(ymax);
        lim.push_back(llx); lim.push_back(ymax);

        not_lim.push_back(llx); not_lim.push_back(lly);
        not_lim.push_back(xmax-1); not_lim.push_back(ymax-1);
        return true;
    }
    else if (x==llx) //first 0 on (llx, ?)
    {
        int ymin=y-1;//last 1 on line llx
        while (x<=urx && b.at(x*M+ury)==0)
        {
            x++;
        }
        if (x>urx)
            {//cout<<"7"<<endl;
            return false;}
        xmax=x;//first 1 on column ury
        ymax=ury;

        //vertical ONE rectangle
        while (!all_ones(llx, lly, urx, ymin, b, M) && ymin>lly)
        {
            ymin--;
        }
        if (ymin==lly)
            {//cout<<"8"<<endl;
            return false;}

        //horizontal ONE rectangle
        while(!all_ones(xmax, ymin, urx, ymax, b, M) && xmax<urx)
        {
            xmax++;
        }
        if (xmax==urx)
            {//cout<<"9"<<endl;
            return false;}

        lim.push_back(llx); lim.push_back(lly);
        lim.push_back(llx); lim.push_back(ymin);
        lim.push_back(xmax); lim.push_back(ymin);
        lim.push_back(xmax); lim.push_back(ury);
        lim.push_back(urx); lim.push_back(ury);
        lim.push_back(urx); lim.push_back(lly);
        lim.push_back(llx); lim.push_back(lly);

        not_lim.push_back(llx); not_lim.push_back(ymin+1);
        not_lim.push_back(xmax-1); not_lim.push_back(ury);
        return true;
    }
    else if(y==lly) // first 0 on (?, lly)
    {
        xmin=x-1;//last 1 on column lly
        ymin=0;
        while (b.at(urx*M+y)==0 && y<=ury)
        {
            y++;
        }
        if (y>ury)
            {//cout<<"10"<<endl;
            return false;}
        xmax=urx;
        ymax=y;//first 1 on line urx
        //vertical ONE rectangle
        while (!all_ones(llx, ymax, urx, ury, b, M) && ymax<ury)
        {
            ymax++;
        }
        if (ymax==ury)
            {//cout<<"12"<<endl;
            return false;}

        //horizontal ONE rectangle
        while(!all_ones(llx, lly, xmin, ymax, b, M) && xmin>llx)
        {
            xmin--;
        }
        if (xmin==llx)
            {//cout<<"13"<<endl;
            return false;}

        lim.push_back(llx); lim.push_back(lly);
        lim.push_back(llx); lim.push_back(ury);
        lim.push_back(urx); lim.push_back(ury);
        lim.push_back(urx); lim.push_back(ymax);
        lim.push_back(xmin); lim.push_back(ymax);
        lim.push_back(xmin); lim.push_back(lly);
        lim.push_back(llx); lim.push_back(lly);

        not_lim.push_back(xmin+1); not_lim.push_back(lly);
        not_lim.push_back(urx); not_lim.push_back(ymax-1);
        return true;
    }
    else // first 0 on no particular point
    {
        ymin=y-1;//last 1 line
        xmin=x-1;//last 1 on column
        while (!all_ones(llx, lly, urx, ymin, b, M) && ymin>lly)
        {
            ymin--;
        }
        if (ymin==lly)
            {//cout<<"14"<<endl;
            return false;}

        //horizontal ONE rectangle
        while(!all_ones(llx, ymin, xmin, urx, b, M) && xmin>llx)
        {
            xmin--;
        }
        if (xmin==llx)
            {//cout<<"15"<<endl;
            return false;}

        lim.push_back(llx); lim.push_back(lly);
        lim.push_back(llx); lim.push_back(ury);
        lim.push_back(xmin); lim.push_back(ury);
        lim.push_back(xmin); lim.push_back(ymin);
        lim.push_back(urx); lim.push_back(ymin);
        lim.push_back(urx); lim.push_back(lly);
        lim.push_back(llx); lim.push_back(lly);

        not_lim.push_back(xmin+1); not_lim.push_back(ymin+1);
        not_lim.push_back(urx); not_lim.push_back(ury);
        return true;
    }
    lim.clear();
    //cout<<"16"<<endl;
    return false;
}
vector<double> rotate_p(OGRPoint ptTemp, double centerx, double centery, double A)
{
    vector<double> pt;
    double X= ptTemp.getX()-centerx;
    double Y= ptTemp.getY()-centery;
    pt.push_back(centerx + X*cos(A)+Y*sin(A));
    pt.push_back(centery - X*sin(A)+Y*cos(A));
    return pt;
}


int larger_L_included (vector<int> b, int N, int M, vector<int>& lim, int best_area)
{
    int llx =0;
    int lly =0;
    int urx;
    int ury;
    vector<int> lim_temp;
    vector<int> no_lim;
    while  (llx < N && (N-llx)*M>best_area )
    {
        lly=0;
        while (lly<M && (N-llx)*(M-lly)> best_area)
        {
            //cout<<"llx = "<<llx<<" lly = "<< lly <<" value = "<< b.at(llx*M+lly)<<endl;
            if (b.at(llx*M+lly)!=0)
            {
                int a = floor(best_area/M);
                for (urx = llx+a; urx < N; urx++)
                {
                    ury = lly+floor(best_area/(urx-llx+1));
                    //cout<<"llx = "<<llx<<" lly = "<< lly <<" urx = "<< urx <<" ury = "<<ury<<endl;
                    while (ury < M)
                    {
                        //cout<<"urx = "<<urx<<"ury = "<<ury;
                        lim_temp.clear();
                        no_lim.clear();
                        //cout<<"llx = "<<llx<<" lly = "<< lly <<" urx = "<< urx <<" ury = "<<ury<< "out ";
                        bool test=L_ones(llx,lly, urx, ury, b, M, lim_temp, no_lim);
                        if (test)
                        {
                            int atr;
                            //cin >>atr;
                            //cout<<"urx = "<<urx<<"ury = "<<ury;
                            int area_temp=areaL(llx,lly, urx, ury, b, M, no_lim);
                            //cout <<" aire = "<< area_temp<<endl;
                            if (area_temp>best_area)
                            {
                                lim=lim_temp;
                                best_area=area_temp;
                            }
                        }
                        //cout <<endl;
                        ury ++;

                            int atr;
                            //cin >>atr;
                    }
                }
            }
            lly++;
        }
        llx++;
    }
    return best_area;
}

/*
//test area L
#include "catch.h"
TEST_CASE("test areaL ","[areaL]")
{
    vector<int> no_lim;
    no_lim.push_back(0);no_lim.push_back(0);
    no_lim.push_back(1);no_lim.push_back(1);
    vector<int> b;
    b.push_back(0); b.push_back(0); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    int a = areaL(0, 0, 4, 4, b, 5, no_lim);
    REQUIRE(a==21);
    no_lim.clear();
    b.clear();
    no_lim.push_back(0);no_lim.push_back(0);
    no_lim.push_back(1);no_lim.push_back(1);
    b.push_back(0); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    a = areaL(0, 0, 4, 4, b, 5, no_lim);
    REQUIRE(a==21);
    no_lim.clear();
    b.clear();
    no_lim.push_back(3);no_lim.push_back(0);
    no_lim.push_back(9);no_lim.push_back(7);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    a = areaL(0, 0, 9, 9, b, 10, no_lim);
    REQUIRE(a==44);
}
//test L_ones
TEST_CASE("test L_ones ","[L_ones]")
{
    vector<int> lim;
    vector<int> no_lim;
    vector<int> b;
    b.push_back(0); b.push_back(0); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    bool test_L_ones=L_ones(0, 0, 4, 4, b, 5, lim, no_lim);
    REQUIRE(test_L_ones==true);
    REQUIRE(lim.at(0)==0);
    REQUIRE(lim.at(1)==2);
    REQUIRE(lim.at(2)==0);
    REQUIRE(lim.at(3)==4);
    REQUIRE(lim.at(4)==4);
    REQUIRE(lim.at(5)==4);
    REQUIRE(lim.at(6)==4);
    REQUIRE(lim.at(7)==0);
    REQUIRE(lim.at(8)==3);
    REQUIRE(lim.at(9)==0);
    REQUIRE(lim.at(10)==3);
    REQUIRE(lim.at(11)==2);
    REQUIRE(lim.at(12)==0);
    REQUIRE(lim.at(13)==2);
    REQUIRE(no_lim.at(0)==0);
    REQUIRE(no_lim.at(1)==0);
    REQUIRE(no_lim.at(2)==1);
    REQUIRE(no_lim.at(3)==1);
    b.clear();
    lim.clear();
    no_lim.clear();
    b.push_back(1); b.push_back(0); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    test_L_ones=L_ones(0, 0, 4, 4, b, 5, lim, no_lim);
    REQUIRE(test_L_ones==false);
    REQUIRE(lim.size()==0);
    b.clear();
    lim.clear();
    no_lim.clear();
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    test_L_ones=L_ones(0, 0, 4, 4, b, 5, lim, no_lim);
    REQUIRE(test_L_ones==false);
    REQUIRE(lim.size()==0);
    b.clear();
    lim.clear();
    no_lim.clear();
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(0);b.push_back(0);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(0);b.push_back(0);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    test_L_ones=L_ones(0, 0, 4, 4, b, 5, lim, no_lim);
    REQUIRE(test_L_ones==true);
    REQUIRE(lim.at(0)==0);
    REQUIRE(lim.at(1)==0);
    REQUIRE(lim.at(2)==0);
    REQUIRE(lim.at(3)==2);
    REQUIRE(lim.at(4)==2);
    REQUIRE(lim.at(5)==2);
    REQUIRE(lim.at(6)==2);
    REQUIRE(lim.at(7)==4);
    REQUIRE(lim.at(8)==4);
    REQUIRE(lim.at(9)==4);
    REQUIRE(lim.at(10)==4);
    REQUIRE(lim.at(11)==0);
    REQUIRE(lim.at(12)==0);
    REQUIRE(lim.at(13)==0);
    REQUIRE(no_lim.at(0)==0);
    REQUIRE(no_lim.at(1)==3);
    REQUIRE(no_lim.at(2)==1);
    REQUIRE(no_lim.at(3)==4);
    b.clear();
    lim.clear();
    no_lim.clear();
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(0);b.push_back(0);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(0);b.push_back(0);
    test_L_ones=L_ones(0, 0, 4, 4, b, 5, lim, no_lim);
    REQUIRE(test_L_ones==true);
    REQUIRE(lim.at(0)==0);
    REQUIRE(lim.at(1)==0);
    REQUIRE(lim.at(2)==0);
    REQUIRE(lim.at(3)==4);
    REQUIRE(lim.at(4)==2);
    REQUIRE(lim.at(5)==4);
    REQUIRE(lim.at(6)==2);
    REQUIRE(lim.at(7)==2);
    REQUIRE(lim.at(8)==4);
    REQUIRE(lim.at(9)==2);
    REQUIRE(lim.at(10)==4);
    REQUIRE(lim.at(11)==0);
    REQUIRE(lim.at(12)==0);
    REQUIRE(lim.at(13)==0);
    REQUIRE(no_lim.at(0)==3);
    REQUIRE(no_lim.at(1)==3);
    REQUIRE(no_lim.at(2)==4);
    REQUIRE(no_lim.at(3)==4);
    b.clear();
    lim.clear();
    no_lim.clear();
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(0);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(0);b.push_back(1);
    test_L_ones=L_ones(0, 0, 4, 4, b, 5, lim, no_lim);
    REQUIRE(test_L_ones==false);
    REQUIRE(lim.size()==0);
    b.clear();
    lim.clear();
    no_lim.clear();
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(1);b.push_back(1);b.push_back(1);
    test_L_ones=L_ones(0, 0, 4, 4, b, 5, lim, no_lim);
    REQUIRE(test_L_ones==true);
    REQUIRE(lim.at(0)==0);
    REQUIRE(lim.at(1)==0);
    REQUIRE(lim.at(2)==0);
    REQUIRE(lim.at(3)==4);
    REQUIRE(lim.at(4)==4);
    REQUIRE(lim.at(5)==4);
    REQUIRE(lim.at(6)==4);
    REQUIRE(lim.at(7)==2);
    REQUIRE(lim.at(8)==2);
    REQUIRE(lim.at(9)==2);
    REQUIRE(lim.at(10)==2);
    REQUIRE(lim.at(11)==0);
    REQUIRE(lim.at(12)==0);
    REQUIRE(lim.at(13)==0);
    REQUIRE(no_lim.at(0)==3);
    REQUIRE(no_lim.at(1)==0);
    REQUIRE(no_lim.at(2)==4);
    REQUIRE(no_lim.at(3)==1);
    b.clear();
    lim.clear();
    no_lim.clear();
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(0);b.push_back(0);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(0);b.push_back(0);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(0);b.push_back(0);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(0);b.push_back(0);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(0);b.push_back(0);
    test_L_ones=L_ones(0, 0, 4, 4, b, 5, lim, no_lim);
    REQUIRE(test_L_ones==false);
    REQUIRE(lim.size()==0);
}
//test larger_L_included
TEST_CASE("test larger_L_included ","[larger_L_included]")
{
    vector<int> b;
    vector<int> lim;
    int M=5;
    int N=5;
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(0);b.push_back(0);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(0);b.push_back(0);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(0);b.push_back(0);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(0);b.push_back(0);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(0);b.push_back(0);
    int test_larger_L_included = larger_L_included (b, N, M, lim, 0);
    REQUIRE(test_larger_L_included==0);
    REQUIRE(lim.size()==0);
    b.clear();
    lim.clear();
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    test_larger_L_included = larger_L_included (b, N, M, lim, 0);
    REQUIRE(test_larger_L_included==19);
    REQUIRE(lim.at(0)==0);
    REQUIRE(lim.at(1)==0);
    REQUIRE(lim.at(2)==0);
    REQUIRE(lim.at(3)==4);
    REQUIRE(lim.at(4)==4);
    REQUIRE(lim.at(5)==4);
    REQUIRE(lim.at(6)==4);
    REQUIRE(lim.at(7)==3);
    REQUIRE(lim.at(8)==2);
    REQUIRE(lim.at(9)==3);
    REQUIRE(lim.at(10)==2);
    REQUIRE(lim.at(11)==0);
    REQUIRE(lim.at(12)==0);
    REQUIRE(lim.at(13)==0);
    b.clear();
    lim.clear();
    M=10;
    N=10;
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    test_larger_L_included = larger_L_included (b, N, M, lim, 0);
    REQUIRE(test_larger_L_included==44);
    REQUIRE(lim.at(0)==0);
    REQUIRE(lim.at(1)==0);
    REQUIRE(lim.at(2)==0);
    REQUIRE(lim.at(3)==9);
    REQUIRE(lim.at(4)==9);
    REQUIRE(lim.at(5)==9);
    REQUIRE(lim.at(6)==9);
    REQUIRE(lim.at(7)==8);
    REQUIRE(lim.at(8)==2);
    REQUIRE(lim.at(9)==8);
    REQUIRE(lim.at(10)==2);
    REQUIRE(lim.at(11)==0);
    REQUIRE(lim.at(12)==0);
    REQUIRE(lim.at(13)==0);
    b.clear();
    lim.clear();
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(0);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    test_larger_L_included = larger_L_included (b, N, M, lim, 0);
    REQUIRE(test_larger_L_included==36);
    REQUIRE(lim.at(0)==0);
    REQUIRE(lim.at(1)==0);
    REQUIRE(lim.at(2)==0);
    REQUIRE(lim.at(3)==9);
    REQUIRE(lim.at(4)==5);
    REQUIRE(lim.at(5)==9);
    REQUIRE(lim.at(6)==5);
    REQUIRE(lim.at(7)==8);
    REQUIRE(lim.at(8)==2);
    REQUIRE(lim.at(9)==8);
    REQUIRE(lim.at(10)==2);
    REQUIRE(lim.at(11)==0);
    REQUIRE(lim.at(12)==0);
    REQUIRE(lim.at(13)==0);
    b.clear();
    lim.clear();
    N=10;
    M=11;
    b.push_back(1); b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(0);
    b.push_back(0); b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    test_larger_L_included = larger_L_included (b, N, M, lim, 0);
    REQUIRE(test_larger_L_included==35);
    REQUIRE(lim.at(0)==0);
    REQUIRE(lim.at(1)==4);
    REQUIRE(lim.at(2)==0);
    REQUIRE(lim.at(3)==10);
    REQUIRE(lim.at(4)==2);
    REQUIRE(lim.at(5)==10);
    REQUIRE(lim.at(6)==2);
    REQUIRE(lim.at(7)==5);
    REQUIRE(lim.at(8)==9);
    REQUIRE(lim.at(9)==5);
    REQUIRE(lim.at(10)==9);
    REQUIRE(lim.at(11)==4);
    REQUIRE(lim.at(12)==0);
    REQUIRE(lim.at(13)==4);
    b.clear();
    lim.clear();
    N=10;
    M=11;
    b.push_back(0); b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(0);
    b.push_back(0); b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    test_larger_L_included = larger_L_included (b, N, M, lim, 0);
    REQUIRE(test_larger_L_included==35);
    REQUIRE(lim.at(0)==0);
    REQUIRE(lim.at(1)==4);
    REQUIRE(lim.at(2)==0);
    REQUIRE(lim.at(3)==10);
    REQUIRE(lim.at(4)==2);
    REQUIRE(lim.at(5)==10);
    REQUIRE(lim.at(6)==2);
    REQUIRE(lim.at(7)==5);
    REQUIRE(lim.at(8)==9);
    REQUIRE(lim.at(9)==5);
    REQUIRE(lim.at(10)==9);
    REQUIRE(lim.at(11)==4);
    REQUIRE(lim.at(12)==0);
    REQUIRE(lim.at(13)==4);
    b.clear();
    lim.clear();
    N=10;
    M=11;
    b.push_back(1); b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(1); b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);b.push_back(1); b.push_back(1); b.push_back(1);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(0);
    b.push_back(0); b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    b.push_back(0); b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);b.push_back(0); b.push_back(0); b.push_back(0);b.push_back(1);b.push_back(1);
    test_larger_L_included = larger_L_included (b, N, M, lim, 100);
    REQUIRE(test_larger_L_included==100);
    REQUIRE(lim.size()==0);

}
*/

