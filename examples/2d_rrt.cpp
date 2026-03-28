
/*
    This is an example for performing RRT planning on 2D grid.
*/


#include <cmath>
#include <vector>
#include <climits>
#include <utility>
#include <cstdlib>
#include <iostream>
#include <algorithm>

// global variables
int K = 1000;
float steer_dist = 1.0;
float goal_threshold = 0.5;
bool goalReached = false;

// utils
struct Node
{   
    std::pair<float, float> coord {0, 0};
    Node * parent = nullptr;
    Node(){
        ;
    }
    Node(std::pair<float, float> coord_, Node * parent_ = nullptr){
        coord = coord_;
        parent = parent_;
    }
};

std::ostream& operator << (std::ostream& out, Node& obj){
    out << "Coordinate: " << obj.coord.first << ", " << obj.coord.second << "\n";
    out << "Parent: " << obj.parent << "\n";
    return out;
}

std::ostream& operator << (std::ostream& out, std::pair<float, float> obj){
    out << "Coordinate: " << obj.first << ", " << obj.second << "\n";
    return out;
}

std::ostream& operator << (std::ostream& out, std::vector<std::pair<float, float>> vec){
    for (int i=0; i<vec.size(); i++){
        out << i << " - " << '(' << vec[i].first << ", " << vec[i].second << ")\n";
    }
    out << "Path size: " << vec.size() << '\n';
    return out;
}

std::pair<float, float> get_rand_coord(){
    float r = std::rand() % 10;
    float c = std::rand() % 10;
    return std::pair<float, float>{r, c};
}

float l2_norm(std::pair<float, float> coord1, std::pair<float, float> coord2){
    float n1 = coord2.first - coord1.first;
    float n2 = coord2.second - coord1.second;
    return std::sqrt((n1*n1) + (n2*n2));
}

void clip_coord(std::vector<float>& vec){
    if (vec[0] < 0.0) 
        vec[0] = 0.0;
    if (vec[0] > 9.0)
        vec[0] = 9.0;
    if (vec[1] < 0.0)
        vec[1] = 0.0;
    if (vec[1] > 9.0)
        vec[1] = 9.0;
}

std::vector<float>& operator / (std::vector<float>& vec, float num){
    vec[0] /= num;
    vec[1] /= num;
    return vec;
}

std::vector<float>& operator * (std::vector<float>& vec, float num){
    vec[0] *= num;
    vec[1] *= num;
    return vec;
}

Node * nearest(std::vector<Node *> tree, Node& rand_node){
    float minDist = 1000.0;
    Node * near_node = nullptr;
    float dist;

    for (Node * node : tree){
        // compute euclidian distance
        dist = l2_norm(node->coord, rand_node.coord);
        
        if (dist < minDist){
            minDist = dist;
            near_node = node;
        }
    }

    return near_node;
}

void steer(Node& near_node, Node& rand_node, Node * new_node){
    // base vector or unit vector
    std::vector<float> vec {rand_node.coord.first - near_node.coord.first, rand_node.coord.second - near_node.coord.second};
    float length = l2_norm(near_node.coord, rand_node.coord);
    if (length < 1e-3) length = 1e-3;
    std::vector<float> unitVec { vec / length};

    std::vector<float> scaledVec { unitVec * steer_dist };
    std::vector<float> new_coord { near_node.coord.first + scaledVec[0], near_node.coord.second + scaledVec[1]};

    clip_coord(new_coord);

    new_node->coord = std::pair<float, float>{new_coord[0], new_coord[1]};
}

//

std::vector<Node *> tree;


int main(){
    //
    std::srand(42);
    
    std::pair<float, float> startCoord{0.0, 0.0};
    std::pair<float, float> endCoord{9.0, 9.0};
    Node * startNode = new Node(startCoord, nullptr);
    Node * endNode = new Node(endCoord, nullptr);
    
    tree.push_back(startNode);

    // main loop
    for (int idx=0; idx < K; idx++){

        // generate random node
        Node randNode{get_rand_coord(), nullptr};
        // find nearest node in tree
        Node * nearNode = nearest(tree, randNode);
        
        // steer towards the randomly generated node
        Node * newNode = new Node();
        steer(*nearNode, randNode, newNode);

        newNode->parent = nearNode;
        tree.push_back(newNode);

        float goal_dist = l2_norm(newNode->coord, endNode->coord);
        if (goal_dist <= goal_threshold){
            // endNode->parent = newNode;
            // tree.push_back(endNode);
            break;
        }
    }

    // extract path from tree vector
    std::vector<std::pair<float, float>> path;
    path.push_back(tree.back()->coord);
    Node * temp_parent = tree.back()->parent;

    // extract path from tree
    while (temp_parent){
        path.push_back(temp_parent->coord);
        temp_parent = temp_parent->parent;
    }
    // reverse the path from start - end
    std::reverse(path.begin(), path.end()); 

    // print path
    std::cout << path;    

    return 0;
}