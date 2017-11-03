#ifndef BUILDINGMODEL_H
#define BUILDINGMODEL_H

#include "Triangle.h"
#include "Parcel.h"
#include <vector>

class BuildingModel
{
/**
*@class BuildingModel
*Contain the building model.
*/

    public:
        BuildingModel();
        /**
        *@fn BuildingModel::BuildingModel()
        *Constructor
        */

        BuildingModel(std::vector<Triangle> li_T, Parcel* p);
        /**
        *@fn BuildingModel::BuildingModel(std::vector<Triangle> li_T, Parcel* p)
        *Constructor 2.
        *@param[in] li_T std::vector<Triangle> : It's a list of Triangles making up the BuildingModel.
        *@param[in] p Parcel* : It's the parcel associated to the BuildingModel.
        */

        virtual ~BuildingModel();
        /**
        *@fn virtual BuildingModel::~BuildingModel()
        *Destructor.
        */

        void translate(double vec[3], TriangleType name);
        /**
        *@fn void BuildingModel::translate(double vec[3], TriangleType name)
        *This function allows us to translate the selected surfaces of the BuildingModel according to an array.
        *@param[in] vec : It's the array of the translation.
        *@param[in] name : It's the name of the selected surfaces.
        */

        void rotate(double vec[3], double angle, TriangleType name);
        /**
        *@fn void BuildingModel::rotate(double vec[3], double angle, TriangleType name)
        *This function allows us to rotate the selected surfaces of the BuildingModel according to an axis and an angle of rotation (the origin is [0, 0, 0]).
        *@param[in] vec : It's the axis of the rotation.
        *@param[in] angle : It's the angle of rotation.
        *@param[in] name : It's the name of the selected surfaces.
        */

        void size(double vec[3], TriangleType name);
        /**
        *@fn void BuildingModel::size(double vec[3], TriangleType name)
        *This function allows us to resize the selected surfaces of the BuildingModel according to an array.
        *@param[in] vec : It's the array of the resize.
        *@param[in] name : It's the name of the selected surfaces.
        */

        void split(double axis[3], Point origin, TriangleType oldName, TriangleType newName);
        /**
        *@fn void BuildingModel::split(double axis[3], Point origin, TriangleType oldName, TriangleType newName)
        *This function allows us to split the selected surfaces of the BuildingModel according to an axis and a origin point.
        *@param[in] axis : It's the axis of the split.
        *@param[in] origin : It's the origin point of the split (to fix the axis in the 3D dimension).
        *@param[in] oldName : It's the name of the selected surfaces.
        *@param[in] newName : It's the new additional name of the split surfaces.
        */

        //void repeat(TriangleType oldName, TriangleType newName);
        /**
        *@fn void BuildingModel::repeat(TriangleType oldName, TriangleType newName)
        *This function allows us to repeat/copy the selected surfaces of the BuildingModel.
        *@param[in] oldName : It's the name of the selected surfaces.
        *@param[in] newName : It's the new additional name of the repeated surfaces.
        */

        void join(BuildingModel buildingModel);
        /**
        *@fn void BuildingModel::join(BuildingModel buildingModel)
        *This function allows us to join together two BuildingModel.
        *@param[in] buildingModel : It's the building model to join.
        */

        void scope();
        /**
        *@fn void BuildingModel::scope()
        *This function allows us to extract the surfaces touched by occlusion.
        */

        BuildingModel creat_roof(double roofAngle);
        /**
        *@fn BuildingModel BuildingModel::creat_roof(double roofAngle)
        *This function allows us to create a roof for a simple building depending of his roof angle.
        *@param[in] roofAngle : It's the roof angle of the roof.
        */

        void to_obj();
        /**
        *@fn void BuildingModel::to_obj()
        *This function allows us to convert our BuildingModel in .obj.
        */

        // Getters
        std::vector<Triangle> get_li_triangle()const{return li_triangle;};
        /**
        *@fn std::vector<Triangle> BuildingModel::get_li_triangle() const
        *This function allows us to get the list of Triangle of a BuildingModel.
        *@return The list of Triangle of a BuildingModel.
        */

        Parcel* get_parcel()const{return parcel;};
        /**
        *@fn Parcel* BuildingModel::get_parcel() const
        *This function allows us to get the Parcel of a BuildingModel.
        *@return The Parcel of a BuildingModel.
        */

    protected:

    private:
        std::vector<Triangle> li_triangle;
        Parcel* parcel;
};

#endif // BUILDINGMODEL_H
