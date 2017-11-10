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
                    if(sum(llx, ury, urx, ury, b, M)==0)
                    {
                        ury++;
                        continue;
                    }
                    while (ury < M && all_ones(llx, lly, urx, ury, b, M))//sum(llx, ury, urx, ury, b, M)==urx-llx+1)
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
int sum(int llx, int lly, int urx, int ury, vector<int> b, int M)
{
    if (llx>urx || lly>ury) // If ur is left of or
        return 0;               // below 11: return 0
    int sum=0;
    for (int x =llx; x<=urx; x++)
    {
        for (int y=lly; y<=ury; y++)
        {
            sum+=b.at(x*M+y);
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
    int test_x, test_y;
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
        while (b.at(x*M+y)==0 && y<ury)
        {
            y++;
        }
        if (y>=ury)
            {//cout<<"3"<<endl;
            return false;}
        int ymax=y;
        //first 0 on column lly
        while (b.at(x*M+lly)==0 && x<urx)
        {
            x++;
        }
        if (x>=urx)
            {//cout<<"4"<<endl;
            return false;}
        int xmax=x;
        //vertical ONE rectangle
        test_x=llx;
        while (test_x<=urx)
        {
            test_y=ymax;
            while (test_y<=ury)
            {
                if (b.at(test_x*M+test_y)==0)
                {
                    ymax=test_y+1;
                    if (ymax>=ury)
                        { //cout<<"5.a"<<endl;
                        return false;}
                }
                test_y++;
            }
            test_x++;
        }
        if (ymax>=ury)
            {//cout<<"5.b"<<endl;
            return false;}

        //horizontal ONE rectangle
        test_y=0;
        while (test_y<ymax)
        {
            test_x=xmax;
            while (test_x<urx)
            {
                if (b.at(test_x*M+test_y)==0)
                {
                    xmax=test_x+1;
                    if (xmax>=urx)
                        {//cout<<"6.a"<<endl;
                        return false;}
                }
                test_x++;
            }
            test_y++;
        }
        if (xmax>=urx)
            {//cout<<"6.b"<<endl;
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
        if (ymin==lly)
            {return false;}
        while (x<urx && b.at(x*M+ury)==0)
        {
            x++;
        }
        if (x>=urx)
            {//cout<<"7"<<endl;
            return false;}
        xmax=x;//first 1 on column ury

        //vertical ONE rectangle
        test_x=llx;
        while (test_x<=urx)
        {
            test_y=lly;
            while (test_y<=ymin)
            {
                if (b.at(test_x*M+test_y)==0)
                {
                    ymin=test_y-1;
                    if (ymin<=lly)
                        {//cout<<"8.b"<<endl;
                        return false;}
                }
                test_y++;
            }
            test_x++;
        }
        if (ymin<=lly)
            {//out<<"8.a"<<endl;
            return false;}

        //horizontal ONE rectangle
        test_y=ymin;
        while (test_y<ury)
        {
            test_x=xmax;
            while (test_x<urx)
            {
                if (b.at(test_x*M+test_y)==0)
                {
                    xmax=test_x+1;
                    if (xmax>=urx)
                        { //cout<<"9.a"<<endl;
                        return false;}
                }
                test_x++;
            }
            test_y++;
        }
        if (xmax>=urx)
            {//cout<<"9.b"<<endl;
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

        test_x=llx;
        while (test_x<=urx)
        {
            test_y=ymax;
            while (test_y<=ury)
            {
                if (b.at(test_x*M+test_y)==0)
                {
                    ymax=test_y+1;
                    if (ymax>=ury)
                        {//cout<<"12.a"<<endl;
                        return false;}
                }
                test_y++;
            }
            test_x++;
        }
        if (ymax>=ury)
            {//cout<<"12.b"<<endl;
            return false;}

        //horizontal ONE rectangle
        test_y=lly;
        while(test_y<ymax)
        {
            test_x=llx;
            while (test_x<=xmin)
            {
                if (b.at(test_x*M+test_y)==0)
                {
                    xmin=test_x-1;
                    if (xmin<=llx)
                        {//cout<<"13.a"<<endl;
                        return false;}
                }
                test_x++;
            }
            test_y++;
        }
        if (xmin<=llx)
            {//cout<<"13.b"<<endl;
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

        test_x=llx;
        while (test_x<=urx)
        {
            test_y=lly;
            while (test_y<=ymin)
            {
                if (b.at(test_x*M+test_y)==0)
                {
                    ymin=test_y-1;
                    if (ymin<=lly)
                        {//cout<<"14.a"<<endl;
                        return false;}
                }
                test_y++;
            }
            test_x++;
        }
        if (ymin<=lly)
            {//cout<<"14.b"<<endl;
            return false;}

        //horizontal ONE rectangle

        test_y=ymin;
        while(test_y<ury)
        {
            test_x=llx;
            while (test_x<=xmin)
            {
                if (b.at(test_x*M+test_y)==0)
                {
                    xmin=test_x-1;
                    if (xmin<=llx)
                        {//cout<<"15.a"<<endl;
                        return false;}
                }
                test_x++;
            }
            test_y++;
        }
        if (xmin<=llx)
            {//cout<<"15.b"<<endl;
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
                        if(sum(llx, ury, urx, ury, b, M)==0)
                        {
                            ury++;
                            continue;
                        }
                        //cout<<"urx = "<<urx<<"ury = "<<ury;
                        lim_temp.clear();
                        no_lim.clear();
                        //cout<<"llx = "<<llx<<" lly = "<< lly <<" urx = "<< urx <<" ury = "<<ury<< "out ";
                        if (sum(llx,lly, urx, ury, b, M)>best_area && L_ones(llx,lly, urx, ury, b, M, lim_temp, no_lim))
                        {
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
                    }
                }
            }
            lly++;
        }
        llx++;
    }
    return best_area;
}

