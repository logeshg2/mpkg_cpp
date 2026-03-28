#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <cmath>
#include <cassert>
#include <vector>
#include <iostream>
#include <Eigen/Dense>

#include "mpkg_cpp/utils/rotation.hpp"

namespace mpkg {

    class SE3{
        private:
            Eigen::Matrix4d mat;
            std::vector<double> trans{0, 0, 0};
            Eigen::Matrix3d rotm;

        public:
            // default contructor
            SE3();

            // constructor for only translation
            SE3(const std::vector<double>& translaion);

            // constructor for both translation and rotation (euler notation)
            SE3(const std::vector<double>& translation, const std::vector<double>& rotation);

            // other utils
            Eigen::Matrix4d transform();
            std::vector<double> translation();
            Eigen::Matrix3d rotation();

            // utils
            void updateRotation(Eigen::Matrix3d& rot);

            friend std::ostream& operator << (std::ostream& out, SE3& obj);
            friend std::ostream& operator << (std::ostream& out, std::vector<double>& tvec);

    };

}

#endif