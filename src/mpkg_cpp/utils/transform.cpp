#include "mpkg_cpp/utils/transform.hpp"


namespace mpkg {

    SE3::SE3(){
        mat = Eigen::Matrix4d::Identity();
    }

    SE3::SE3(const std::vector<double>& translation){
        
        assert(translation.size() == 3 && "Translation vector should of size 3");
        
        mat = Eigen::Matrix4d::Identity();

        // update translation
        mat(0, 3) = translation[0];
        mat(1, 3) = translation[1];
        mat(2, 3) = translation[2];

        // update trans
        trans[0] = translation[0];
        trans[1] = translation[1];
        trans[2] = translation[2];
        // uprate rotm
        rotm = Eigen::Matrix3d::Identity();
    }

    SE3::SE3(const std::vector<double>& translation, const std::vector<double>& rotation){
        
        assert(translation.size() == 3 && "Translation vector should of size 3");
        assert(rotation.size() == 3 && "Rotation vector should of size 3");

        mat = Eigen::Matrix4d::Identity();

        // update translation
        mat(0, 3) = translation[0];
        mat(1, 3) = translation[1];
        mat(2, 3) = translation[2];

        // update rotation
        // first create rotation matrix from euler notation
        Rotation rotObj(rotation[0], rotation[1], rotation[2], true);
        updateRotation(rotObj.matrix());
    
        // update trans
        trans[0] = translation[0];
        trans[1] = translation[1];
        trans[2] = translation[2];
    }

    void SE3::updateRotation(Eigen::Matrix3d& rot){
        // this is brute for update
        for (int ri=0;ri<3;ri++){
            for (int ci=0;ci<3;ci++){
                mat(ri, ci) = rot(ri, ci);

                // uprate rotm
                rotm(ri, ci) = rot(ri, ci);
            }
        }
    }

    Eigen::Matrix4d SE3::transform(){
        return mat;
    }

    std::vector<double> SE3::translation(){
        return trans;
    }

    Eigen::Matrix3d SE3::rotation(){
        return rotm;
    }

    std::ostream& operator << (std::ostream& out, SE3& obj){
        out << obj.transform();
        out << "\n";
        
        return out;
    }

    std::ostream& operator << (std::ostream& out, std::vector<double> tvec){
        for (auto val : tvec){
            out << val << " ";
        }
        out << "\n";
        
        return out;
    }

}