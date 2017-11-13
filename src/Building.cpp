#include "Building.h"
#include "Parcel.h"
#include "BuildingModel.h"
#include "Envelop.h"
#include "get_max_rectangle.h"
#include "create_wall.h"
#include <math.h>
#include <vector>
#include "triangles_to_obj.h"
#include "SS.h"

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
    OGRPoint ptTemp1;
    OGRPolygon poPolygon;
    OGRLinearRing poExteriorRing= (OGRLinearRing)env->get_footprint()->get_geom();
    poExteriorRing.OGRLinearRing::closeRings();
    poPolygon.addRing(&poExteriorRing);
    int NumberOfExteriorRingVertices = poExteriorRing.OGRSimpleCurve::getNumPoints();
    double xmin=100000000;
    double xmax=-10000000;
    double ymin=100000000;
    double ymax=-10000000;
    double centerx =0;
    double centery =0;
    vector<double> li_angle;
    li_angle.push_back(0);
    for ( int k = 0; k < NumberOfExteriorRingVertices-1; k++)//NumberOfExteriorRingVertices; k++ )
    {
        poExteriorRing.getPoint(k,&ptTemp);
        if (ptTemp.getX()<xmin)
        {
            xmin=ptTemp.getX();
        }
        if (ptTemp.getX()>xmax)
        {
            xmax=ptTemp.getX();
        }
        if (ptTemp.getY()<ymin)
        {
            ymin=ptTemp.getY();
        }
        if (ptTemp.getY()>ymax)
        {
            ymax=ptTemp.getY();
        }
        //cout<<"("<<ptTemp.getX()<<", "<<ptTemp.getY()<<")"<<endl;
        centerx+=ptTemp.getX();
        centery+=ptTemp.getY();
        poExteriorRing.getPoint(k+1,&ptTemp1);
        double Xb = (ptTemp1.getX()-ptTemp.getX());
        double Yb = (ptTemp1.getY()-ptTemp.getY());
        double angle = angle_calcul(Xb, Yb);
        if (angle >M_PI/2)
        {
            angle-=M_PI/2;
        }
        if (sqrt(Xb*Xb+Yb*Yb)>=4)
        {
            bool test_a=true;
            for (int k =0; k<li_angle.size(); k++)
            {
                //cout<< angle/M_PI*180<<", "<< li_angle.at(k)/M_PI*180<< ", ["<<(li_angle.at(k)-10/180*M_PI)/M_PI*180<<", "<< ((li_angle.at(k))/M_PI*180+10)<<"]"<<endl;
                if (angle/M_PI*180 > ((li_angle.at(k))/M_PI*180-5) && (angle/M_PI*180 < ((li_angle.at(k))/M_PI*180+5)))
                {
                    test_a=false;
                    //cout<<"break"<<endl;
                    break;
                }
            }
            if(test_a==true)
            {
                li_angle.push_back(angle);
                //cout << "Angle = " <<angle/M_PI*180<<endl;
            }
            //int azerty;
            //cin>> azerty;
        }
    }
    //cout<<"nb angle = "<< li_angle.size()<<endl;
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
    if (max(dx, dy)>10*min(dx, dy))
    {gap=min(dx, dy)/10;}
    if (gap<1)
    {gap=1;}
    //cout << "gap = "<< gap<<endl;
    int N=0;
    int M;
    for (double xp=xmin+0.1; xp<=xmax+gap; xp+=gap)
    {
        N++;
        M=0;
        for (double yp=ymin+0.; yp<=ymax+gap; yp+=gap)
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
    for (unsigned int k=0U; k<lim.size(); k+=2)
    {
        coord_rect.push_back( b_coordx.at(lim.at(k)*M+lim.at(k+1)));
        coord_rect.push_back( b_coordy.at(lim.at(k)*M+lim.at(k+1)));
        //cout<<"rect ("<< lim.at(k)<<", "<<lim.at(k+1)<<")"<<endl;
    }
    //cout << best_area <<endl;



    /*L building : ALL PARCEL TYPE */
    lim.clear();
    int best_area1 =larger_L_included (b,N,M,lim,best_area*1.1);
    if (best_area1>best_area*1.1)
    {
        coord_rect.clear();
        for (unsigned int k=0U; k<lim.size(); k+=2)
        {
            coord_rect.push_back( b_coordx.at(lim.at(k)*M+lim.at(k+1)));
            coord_rect.push_back( b_coordy.at(lim.at(k)*M+lim.at(k+1)));
            //cout<<"L ("<< lim.at(k)<<", "<<lim.at(k+1)<<")"<<endl;
        }
        best_area=best_area1;
        //cout<< best_area<<endl;
    }

    for (int k_a = 0; k_a<li_angle.size(); k_a++)
    {
        //with rotation :
        double A = li_angle.at(k_a);
        //cout<<" A = "<< A/M_PI*180<<endl;
        //limit :
        double xminR=10000000000000;
        double xmaxR=-1000000000000;
        double yminR=10000000000000;
        double ymaxR=-1000000000000;
        double Rx, Ry;
        OGRPoint ptTemp;
        for ( int k = 0; k < NumberOfExteriorRingVertices-1; k++)//NumberOfExteriorRingVertices; k++ )
        {
            poExteriorRing.getPoint(k,&ptTemp);
            vector<double>R_pt= rotate_p(ptTemp, centerx, centery, A);
            Rx=R_pt.at(0);
            Ry=R_pt.at(1);
            if (Rx<xminR)
            {
                xminR=Rx;
            }
            if (Rx>xmaxR)
            {
                xmaxR=Rx;
            }
            if (Ry<yminR)
            {
                yminR=Ry;
            }
            if (Ry>ymaxR)
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
        for (double xp=xminR+0.1; xp<=xmaxR+gap; xp+=gap)
        {
            N++;
            M=0;
            for (double yp=yminR+0.1; yp<=ymaxR+gap; yp+=gap)
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
                for (unsigned int k=0U; k<lim.size(); k+=2)
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
            best_area1 =larger_L_included (b,N,M,lim,best_area*1.1);
            if (best_area1>best_area*1.1)
            {
                coord_rect.clear();
                for (unsigned int k=0U; k<lim.size(); k+=2)
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
    for (unsigned int k=0U; k< coord_rect.size(); k+=2)
    {
        pt_temp =OGRPoint(coord_rect.at(k),coord_rect.at(k+1));
        a.addPoint(&pt_temp);
    }
    building_footprint.addRing(&a);
    geom=new OGRPolygon(building_footprint);
    create_wall(&building_footprint, height, li_tri);
    //cout <<"li_tri " <<li_tri.size()<<endl;

    building_models.push_back(BuildingModel(li_tri, parcel));

}

Building::~Building()
{
    //dtor
}

void Building::creat_roof(double roofAngle)
{
    OGRLinearRing* poExteriorRing= geom->getExteriorRing();
    poExteriorRing->OGRLinearRing::closeRings();
    int NumberOfExteriorRingVertices = poExteriorRing->OGRSimpleCurve::getNumPoints();
    if (NumberOfExteriorRingVertices==5)
    {
        //BuildingModel bm= crossed_spine(*this, roofAngle);
        BuildingModel bm= linear_spine(*this, roofAngle);
        building_models.push_back(bm);
    }
}

vector<string> Building::to_obj(OGRPoint* centroid, int& index_offset)
{
    vector<Triangle> li_triangles;
    for (unsigned int i=0U; i<building_models.size(); i++)
    {
        BuildingModel build_mod = building_models.at(i);
        vector<Triangle> building_triangles = build_mod.get_li_triangle();

        li_triangles.insert(li_triangles.end(), building_triangles.begin(), building_triangles.end());
    }
    return triangles_to_obj(li_triangles, index_offset, centroid->getX(), centroid->getY());
}

