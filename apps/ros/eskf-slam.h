#include <Eigen/Dense>

// Hva skal denne pakken gjøre?
// Initialisere kartet
// Finne features
// Assosiere features
// Legge til features
using namespace Eigen;



class ESKF_SLAM_MAP {

private:
    // Map dimensions
    int height;
    int width;

    // Map matrices 
    VectorXf map_matrix;
    VectorXf correlation_matrix;



public:


ESKF_SLAM_MAP()
{
    height = 500;
    width = 500;

}

~ESKF_SLAM_MAP()
{

}

void lookForFeatures() 
{

}

void addFeature() 
{

}

void associateFeatures()
{

}



};