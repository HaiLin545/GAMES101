#include <cmath>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <iostream>

using namespace std;

const float PI = cos(-1.f);

int main() {

    Eigen::Vector3f P(2, 1, 1);
    Eigen::Matrix3f M;

    float a = PI / 4;
    float tx = 1, ty = 2;

    M << cos(a), -sin(a), \
         tx, sin(a), cos(a), \
         ty, 0, 0, 1;

    cout << "P: " << endl;
    cout << P << "\n\n";
    cout << "M : " << endl;
    cout << M << "\n\n";
    cout << "P * M" << endl;
    cout << M * P << endl;

    // Basic Example of cpp
    std::cout << "Example of cpp \n";
    float aa = 1.0, bb = 2.0;
    std::cout << aa << std::endl;
    std::cout << aa / bb << std::endl;
    std::cout << std::sqrt(bb) << std::endl;
    std::cout << std::acos(-1) << std::endl;
    std::cout << std::sin(30.0 / 180.0 * acos(-1)) << std::endl;

    // Example of vector
    std::cout << "Example of vector \n";
    // vector definition
    Eigen::Vector3f v(1.0f, 2.0f, 3.0f);
    Eigen::Vector3f w(1.0f, 0.0f, 0.0f);
    // vector output
    std::cout << "Example of output \n";
    std::cout << v << std::endl;
    // vector add
    std::cout << "Example of add \n";
    std::cout << v + w << std::endl;
    // vector scalar multiply
    std::cout << "Example of scalar multiply \n";
    std::cout << v * 3.0f << std::endl;
    std::cout << 2.0f * v << std::endl;

    // Example of matrix
    std::cout << "Example of matrix \n";
    // matrix definition
    Eigen::Matrix3f i, j;
    i << 1.0, 2.0, 3.0, \
         4.0, 5.0, 6.0, \
         7.0, 8.0, 9.0;
    j << 2.0, 3.0, 1.0, \
         4.0, 6.0, 5.0, \
         9.0, 7.0, 8.0;
    // matrix output
    std::cout << "Example of output \n";
    std::cout << i << std::endl;
    // matrix add i + j
    // matrix scalar multiply i * 2.0
    // matrix multiply i * j
    // matrix multiply vector i * v
    cout << "Scalar multiply: \n";
    cout << i * 2.0 << endl;
    cout << "Multiply matrix: \n";
    cout << i * j << endl;


    return 0;
}