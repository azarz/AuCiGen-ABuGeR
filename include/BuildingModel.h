#ifndef BUILDINGMODEL_H
#define BUILDINGMODEL_H

#include "Triangle.h"
#include "Parcel.h"
#include <vector>

class BuildingModel
{
    public:
        /**
        * Constructor
        */
        BuildingModel();

        /**
        * Destructor
        */
        virtual ~BuildingModel();

        /**
        * This function allows us to translate the selected surfaces of the BuildingModel according to an array.
        * @param[in] vec It's the array of the translation.
        * @param[in] name It's the name of the selected surfaces.
        */
        void translate(double vec[3], TriangleType name);

        /**
        * This function allows us to rotate the selected surfaces of the BuildingModel according to an axis and an angle of rotation (the origin is [0, 0, 0]).
        * @param[in] vec It's the axis of the rotation.
        * @param[in] angle It's the angle of rotation.
        * @param[in] name It's the name of the selected surfaces.
        */
        void rotate(double vec[3], double angle, TriangleType name);

        /**
        * This function allows us to resize the selected surfaces of the BuildingModel according to an array.
        * @param[in] vec It's the array of the resize.
        * @param[in] name It's the name of the selected surfaces.
        */
        void size(double vec[3], TriangleType name);

        /**
        * This function allows us to split the selected surfaces of the BuildingModel according to an axis and a origin point.
        * @param[in] axis It's the axis of the split.
        * @param[in] origin It's the origin point of the split (to fix the axis in the 3D dimension).
        * @param[in] oldName It's the name of the selected surfaces.
        * @param[in] newName It's the new additional name of the split surfaces.
        */
        void split(double axis[3], Point origin, TriangleType oldName, TriangleType newName);

        /**
        * This function allows us to repeat/copy the selected surfaces of the BuildingModel.
        * @param[in] oldName It's the name of the selected surfaces.
        * @param[in] newName It's the new additional name of the repeated surfaces.
        */
        void repeat(TriangleType oldName, TriangleType newName);

        /**
        * This function allows us to join together two BuildingModel.
        * @param[in]
        */
        BuildingModel join();

        /**
        * This function allows us to extract the surfaces touched by occlusion.
        * @param[in]
        */
        void scope();

        /**
        * This function allows us to create a roof for a simple building depending of his roof angle.
        * @param[in] roofAngle It's the roof angle of the roof.
        */
        BuildingModel creat_roof(double roofAngle);

        /**
        * This function allows us to convert our BuildingModel in .obj.
        */
        void to_obj();

        // Getters
        /**
        * This function allows us to get the list of Triangle of a BuildingModel.
        * @return The list of Triangle of a BuildingModel.
        */
        std::vector<Triangle> get_li_triangle()const{return li_triangle;};

        /**
        * This function allows us to get the Parcel of a BuildingModel.
        * @return The Parcel of a BuildingModel.
        */
        Parcel* get_parcel()const{return parcel;};

    protected:

    private:
        std::vector<Triangle> li_triangle;
        Parcel* parcel;
};

#endif // BUILDINGMODEL_H
