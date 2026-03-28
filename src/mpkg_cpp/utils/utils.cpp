#include "mpkg_cpp/utils/utils.hpp"


std::ostream& operator << (std::ostream& out, std::vector<double> vec){
    for (auto val : vec){
        out << val << " ";
    }
    out << "\n";
    
    return out;
}