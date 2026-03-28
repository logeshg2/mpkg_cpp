#include <iostream>
#include "mpkg_cpp/utils/utils.hpp"
#include "mpkg_cpp/utils/rotation.hpp"
#include "mpkg_cpp/utils/transform.hpp"


int main(){

    // rotation eg
    // mpkg::Rotation rot_obj(0, 0, 90, true);
    // std::cout << rot_obj;

    // transform eg
    std::vector<double> trans{0.1, 0.2, 0.3};
    std::vector<double> rotv{0.0, 0.0, 90.0};
    mpkg::SE3 T(trans, rotv);
    std::cout << "Translation:\n" << T.translation() <<"\n";
    std::cout << "Rotation:\n" << T.rotation() << "\n";
    std::cout << "Transform:\n" << T << "\n";

    return 0;
}