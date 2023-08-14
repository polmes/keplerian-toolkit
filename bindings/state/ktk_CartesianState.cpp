#include "state/CartesianState.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

#include <iostream>

int my_test_fun(int a) {
    CartesianState sv( Eigen::Vector3d(8000,0,0), Eigen::Vector3d(0,8,0) );
    std::cout << "WOOOW" << std::endl;
    return a * a;
}

Eigen::Vector3d my_eigen_fun(const double& a, const double& b) {
    CartesianState sv( Eigen::Vector3d(a,0,0), Eigen::Vector3d(0,b,0) );
    return sv.position();
}


void ktk_CartesianState(pybind11::module& m) {
    m.def("my_test_fun", &my_test_fun, "Test Function");
    m.def("my_eigen_fun", &my_eigen_fun, "Eigen Function");
}
