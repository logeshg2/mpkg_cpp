#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <vector>
#include <iostream>
#include <Eigen/Dense>

namespace mpkg {

    class Rotation{
        private:
            Eigen::Matrix3d rotm;
            Eigen::Vector3d euler;
            Eigen::Vector3d rotvec;
            Eigen::Vector4d quat;

        public:
            // default
            Rotation();

        // cout override function
        friend std::ostream& operator << (std::ostream& out, const Rotation& obj);
    
    };

    class SE3{
        private:
            Eigen::Matrix4d mat;

        public:
            // default contructor
            SE3();

            // constructor for only translation
            SE3(const std::vector<double>& trans);

            // constructor for both translation + orientation
            // SE3(const std::vector<double>& trans, const mpkg::Rotation)
    };

}

#endif