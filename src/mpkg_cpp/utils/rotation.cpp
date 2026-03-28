#include "mpkg_cpp/utils/rotation.hpp"

namespace mpkg {

    Rotation::Rotation(){
        rotm << Eigen::Matrix3d::Identity(3,3);
    }

    Rotation::Rotation(float r_x, float r_y, float r_z, bool degrees=true){
        if (degrees){
            r_x = Rotation::deg2rad(r_x);
            r_y = Rotation::deg2rad(r_y);
            r_z = Rotation::deg2rad(r_z);
        }
        
        Eigen::Matrix3d rx = Rotation::RX(r_x);
        Eigen::Matrix3d ry = Rotation::RY(r_y);
        Eigen::Matrix3d rz = Rotation::RZ(r_z);
        
        // final rotation matrix
        rotm = (rz * ry) * rx;
    }

    Eigen::Matrix3d& Rotation::matrix(){
        return rotm;
    }

    Eigen::Matrix3d Rotation::RX(float r_x){
        Eigen::Matrix3d rx = Eigen::Matrix3d::Identity(3, 3);
        rx(1, 1) = std::cos(r_x);
        rx(2, 2) = std::cos(r_x);
        rx(1, 2) = -1 * std::sin(r_x);
        rx(2, 1) = std::sin(r_x);
        return rx;
    }

    Eigen::Matrix3d Rotation::RY(float r_y){
        Eigen::Matrix3d ry = Eigen::Matrix3d::Identity(3, 3);
        ry(0, 0) = std::cos(r_y);
        ry(2, 2) = std::cos(r_y);
        ry(2, 0) = -1 * std::sin(r_y);
        ry(0, 2) = std::sin(r_y);
        return ry;
    }

    Eigen::Matrix3d Rotation::RZ(float r_z){
        Eigen::Matrix3d rz = Eigen::Matrix3d::Identity(3, 3);
        rz(0, 0) = std::cos(r_z);
        rz(1, 1) = std::cos(r_z);
        rz(0, 1) = -1 * std::sin(r_z);
        rz(1, 0) = std::sin(r_z);
        return rz;
    }

    std::ostream& operator << (std::ostream& out, Rotation& obj){
        out << obj.matrix();
        out << "\n";

        return out;   
    }

    float Rotation::deg2rad(float deg){
        return (deg * (M_PI / 180.0));
    }

    float Rotation::rad2deg(float deg){
        return (deg * (M_PI / 180.0));
    }

}