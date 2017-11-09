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
        *Translates the selected surfaces of the BuildingModel according to an array.
        *@param[in] vec: The array of the translation.
        *@param[in] name: The name of the selected surfaces.
        */

        void rotate(double vec[3], double angle, TriangleType name);
        /**
        *@fn void BuildingModel::rotate(double vec[3], double angle, TriangleType name)
        *RotateS the selected surfaces of the BuildingModel according to an axis and an angle of rotation (the origin is [0, 0, 0]).
        *@param[in] vec: The axis of the rotation.
        *@param[in] angle: The angle of rotation.
        *@param[in] name: The name of the selected surfaces.
        */

        void size(double vec[3], TriangleType name);
        /**
        *@fn void BuildingModel::size(double vec[3], TriangleType name)
        *Resizes the selected surfaces of the BuildingModel according to an array.
        *@param[in] vec: Array of the resize.
        *@param[in] name: The name of the selected surfaces.
        */

        void split(double axis[3], Point origin, TriangleType oldName, TriangleType newName);
        /**
        *@fn void BuildingModel::split(double axis[3], Point origin, TriangleType oldName, TriangleType newName)
        *Splits the selected surfaces of the BuildingModel according to an axis and a origin point.
        *@param[in] axis: The axis of the split.
        *@param[in] origin: The origin point of the split (to fix the axis in the 3D dimension).
        *@param[in] oldName: The name of the selected surfaces.
        *@param[in] newName: The new additional name of the split surfaces.
        */

        void repeat(TriangleType oldName, TriangleType newName);
        /**
        *@fn void BuildingModel::repeat(TriangleType oldName, TriangleType newName)
        *Repeat/copies the selected surfaces of the BuildingModel.
        *@param[in] oldName: The name of the selected surfaces.
        *@param[in] newName: The new additional name of the repeated surfaces.
        */

        void join(BuildingModel buildingModel);
        /**
        *@fn void BuildingModel::join(BuildingModel buildingModel)
        *Joins together two BuildingModel.
        *@param[in] buildingModel: The building model to join.
        */

        void scope();
        /**
        *@fn void BuildingModel::scope()
        *Extracts the surfaces touched by occlusion.
        */

        void to_obj();
        /**
        *@fn void BuildingModel::to_obj()
        *Converts the BuildingModel to .obj format.
        */

        // Getters
        std::vector<Triangle> get_li_triangle()const{return li_triangle;};
        /**
        *@fn std::vector<Triangle> BuildingModel::get_li_triangle() const
        *Gets the list of Triangle of a BuildingModel.
        *@return The list of Triangle of a BuildingModel.
        */

        Parcel* get_parcel()const{return parcel;};
        /**
        *@fn Parcel* BuildingModel::get_parcel() const
        *Gets the Parcel of a BuildingModel.
        *@return The Parcel of a BuildingModel.
        */

    protected:

    private:
        std::vector<Triangle> li_triangle;
        Parcel* parcel;
};

#endif // BUILDINGMODEL_H
