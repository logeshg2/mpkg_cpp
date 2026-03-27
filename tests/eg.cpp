#include <iostream>
#include "mpkg_cpp/utils/transform.hpp"

int main(){

    mpkg::Rotation rot_obj(0, 0, 90, true);
    std::cout << rot_obj;

    return 0;
}