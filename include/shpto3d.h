#include <iostream>
using namespace std;


#ifndef SHPTO3D_H
#define SHPTO3D_H


class shpto3d
{
    public:
        shpto3d(std::string fill_path, std::string fill_name);
        virtual ~shpto3d();
    protected:
        std::string name;
        std::string path;
    private:
};

#endif // SHPTO3D_H
