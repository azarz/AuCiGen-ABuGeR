#include "Building.h"
#include "Parcel.h"
#include "BuildingModel.h"
#include "Envelop.h"
#include "get_max_rectangle.h"
#include "create_wall.h"
#include <math.h>
#include <vector>

Building::Building(Envelop* env)
{
    //ctor

    //double gap=1; //length between two points
    double step= 20; // angle between two rectangles calculated


    parcel=env->get_parcel();
    height = env->get_height();


    string parcel_type = parcel->get_type()->get_type();
    //cout << parcel_type << endl;
    //lim
    OGRPoint ptTemp;
    OGRPolygon poPolygon;
    OGRLinearRing poExteriorRing= (OGRLinearRing)env->get_footprint()->get_geom();
    poPolygon.addRing(&poExteriorRing);
    int NumberOfExteriorRingVertices = poExteriorRing.OGRSimpleCurve::getNumPoints();
    double xmin=100000000;
    double xmax=-10000000;
    double ymin=100000000;
    double ymax=-10000000;
    double centerx =0;
    double centery =0;
    for ( int k = 0; k < NumberOfExteriorRingVertices; k++)//NumberOfExteriorRingVertices; k++ )
    {
        poExteriorRing.getPoint(k,&ptTemp);
        if (ptTemp.getX()<xmin)
        {
            xmin=ptTemp.getX();
        }
        else if (ptTemp.getX()>xmax)
        {
            xmax=ptTemp.getX();
        }
        if (ptTemp.getY()<ymin)
        {
            ymin=ptTemp.getY();
        }
        else if (ptTemp.getY()>ymax)
        {
            ymax=ptTemp.getY();
        }
        //cout<<"("<<ptTemp.getX()<<", "<<ptTemp.getY()<<")"<<endl;
        centerx+=ptTemp.getX();
        centery+=ptTemp.getY();
    }
    centerx/=NumberOfExteriorRingVertices-1;
    centery/=NumberOfExteriorRingVertices-1;
    vector<int> b;
    vector<double> b_coordx;
    vector<double> b_coordy;
    //cout << "min ("<<xmin <<", "<< ymin<<"); max ("<<xmax<<", "<< ymax <<")"<<endl;
    double dx = xmax-xmin;
    double dy = ymax-ymin;
    //cout << "dx = "<<dx<<"; dy = "<<dy<<endl;
    double gap = max(dx, dy)/50;
    //cout << "gap = "<< gap<<endl;
    int N=0;
    int M;
    for (double xp=xmin; xp<=xmax+gap; xp+=gap)
    {
        N++;
        M=0;
        for (double yp=ymin; yp<=ymax+gap; yp+=gap)
        {
            M++;
            ptTemp = OGRPoint(xp, yp);
            int a=poPolygon.IsPointOnSurface(&ptTemp);
            b.push_back(a);
            b_coordx.push_back(xp);
            b_coordy.push_back(yp);
            //cout<< a<<" ";
        }
        //cout <<endl;
    }
    //cout<< "N ="<< N<<"; M ="<< M <<endl;


    /* for rectangles : ALL PARCEL TYPE */


    vector<int> lim;
    int best_area =larger_rectangle_included (b,N,M,lim,0);
    vector<double> coord_rect;
    for (int k =0; k<lim.size(); k+=2)
    {
        coord_rect.push_back( b_coordx.at(lim.at(k)*M+lim.at(k+1)));
        coord_rect.push_back( b_coordy.at(lim.at(k)*M+lim.at(k+1)));
        //cout<<"rect ("<< lim.at(k)<<", "<<lim.at(k+1)<<")"<<endl;
    }
    //cout << best_area <<endl;



    /*L building : ALL PARCEL TYPE */
    lim.clear();
    int best_area1 =larger_L_included (b,N,M,lim,best_area);
    if (best_area1>best_area)
    {
        coord_rect.clear();
        for (int k =0; k<lim.size(); k+=2)
        {
            coord_rect.push_back( b_coordx.at(lim.at(k)*M+lim.at(k+1)));
            coord_rect.push_back( b_coordy.at(lim.at(k)*M+lim.at(k+1)));
            //cout<<"L ("<< lim.at(k)<<", "<<lim.at(k+1)<<")"<<endl;
        }
        best_area=best_area1;
        //cout<< best_area<<endl;
    }

    for (double A = M_PI/step; A<M_PI/2; A+=(M_PI/step))
    {
        //with rotation :
        //cout<<" A = "<< A/M_PI*180<<endl;
        //limit :
        double xminR=10000000000000;
        double xmaxR=-1000000000000;
        double yminR=10000000000000;
        double ymaxR=-1000000000000;
        double Rx, Ry;
        OGRPoint ptTemp;
        for ( int k = 0; k < NumberOfExteriorRingVertices; k++)//NumberOfExteriorRingVertices; k++ )
        {
            poExteriorRing.getPoint(k,&ptTemp);
            vector<double>R_pt= rotate_p(ptTemp, centerx, centery, A);
            Rx=R_pt.at(0);
            Ry=R_pt.at(1);
            if (Rx<xminR)
            {
                xminR=Rx;
            }
            else if (Rx>xmaxR)
            {
                xmaxR=Rx;
            }
            if (Ry<yminR)
            {
                yminR=Ry;
            }
            else if (Ry>ymaxR)
            {
                ymaxR=Ry;
            }
        }
        //cout << "min ("<<xminR <<", "<< yminR<<"); max ("<<xmaxR<<", "<< ymaxR <<")"<<endl;
        double dxR = xmaxR-xminR;
        double dyR = ymaxR-yminR;
        //cout << "dx = "<<dxR<<"; dy = "<<dyR<<endl;
        //matrix creation :
        N=0;
        b.clear();
        b_coordx.clear();
        b_coordy.clear();
        for (double xp=xminR; xp<=xmaxR+gap; xp+=gap)
        {
            N++;
            M=0;
            for (double yp=yminR; yp<=ymaxR+gap; yp+=gap)
            {
                M++;
                ptTemp = OGRPoint(xp, yp);
                vector<double>R_pt= rotate_p(ptTemp, centerx, centery, -1*A);
                ptTemp = OGRPoint(R_pt.at(0), R_pt.at(1));
                int a=poPolygon.IsPointOnSurface(&ptTemp);
                b.push_back(a);
                b_coordx.push_back(R_pt.at(0));
                b_coordy.push_back(R_pt.at(1));
                //cout<< a<<" ";
            }
            //cout <<endl;
        }
        //cout<< "N ="<< N<<"; M ="<< M <<endl;
        if (N*M>best_area)
        {

            /*for rectangles : ALL PARCEL TYPE;*/

            lim.clear();
            int best_area1 =larger_rectangle_included (b,N,M,lim,best_area);

            if (best_area1>best_area)
            {
                coord_rect.clear();
                for (int k =0; k<lim.size(); k+=2)
                {
                    coord_rect.push_back( b_coordx.at(lim.at(k)*M+lim.at(k+1)));
                    coord_rect.push_back( b_coordy.at(lim.at(k)*M+lim.at(k+1)));
                    //cout<<"rect ("<< lim.at(k)<<", "<<lim.at(k+1)<<")"<<endl;
                }
                best_area=best_area1;
                //cout<<best_area<<endl;
            }

            /*L building : ALL PARCEL TYPE */
            lim.clear();
            best_area1 =larger_L_included (b,N,M,lim,best_area);
            if (best_area1>best_area)
            {
                coord_rect.clear();
                for (int k =0; k<lim.size(); k+=2)
                {
                    coord_rect.push_back( b_coordx.at(lim.at(k)*M+lim.at(k+1)));
                    coord_rect.push_back( b_coordy.at(lim.at(k)*M+lim.at(k+1)));
                    //cout<<"L ("<< lim.at(k)<<", "<<lim.at(k+1)<<")"<<endl;
                }
                best_area=best_area1;
                //cout<<best_area<<endl;
            }
        }



    }
    vector<Triangle> li_tri;
    OGRPolygon building_footprint;
    OGRLinearRing a;
    OGRPoint pt_temp;
    //cout << "coord_rect.size() "<< coord_rect.size()<<endl;
    for (int k=0; k< coord_rect.size(); k+=2)
    {
        pt_temp =OGRPoint(coord_rect.at(k),coord_rect.at(k+1));
        a.addPoint(&pt_temp);
    }
    building_footprint.addRing(&a);
    geom=new OGRPolygon(building_footprint);
    create_wall(&building_footprint, height, li_tri);
    //cout <<"li_tri " <<li_tri.size()<<endl;

    building_model.push_back(BuildingModel(li_tri, parcel));

}

Building::~Building()
{
    //dtor
}

void Building::creat_roof(double roofAngle)
{

}
void Building::to_obj(OGRPoint* centroid)
{
    //
}

