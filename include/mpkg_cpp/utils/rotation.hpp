#ifndef ROTATION_HPP
#define ROTATION_HPP

#include <iostream>
#include <Eigen/Dense>

namespace mpkg {

    class Rotation{
        private:
            Eigen::Matrix3d rotm;

        public:
            // default
            Rotation();

            // constructor for rotation along X, Y, Z input ( euler notation )
            Rotation(float r_x, float r_y, float r_z, bool degrees);

            Eigen::Matrix3d& matrix();

            // rotation matrix utils
            Eigen::Matrix3d RX(float r_x);
            Eigen::Matrix3d RY(float r_y);
            Eigen::Matrix3d RZ(float r_z);

            // math utils
            float deg2rad(float deg);
            float rad2deg(float deg);

            // cout override function
            friend std::ostream& operator << (std::ostream& out, Rotation& obj);
            friend std::ostream& operator << (std::ostream& out, Eigen::Matrix3d& mat);

    };

}



#endif