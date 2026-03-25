#include "mpkg_cpp/utils/transform.hpp"


namespace mpkg {

    Rotation::Rotation(){
        euler << 1, 1, 1;
    }

    std::ostream& operator << (std::ostream& out, const Rotation& obj){
        
        for (auto num : obj.euler.array()){
            out << num << " ";
        }
        out << "\n";

        return out;   
    }

}