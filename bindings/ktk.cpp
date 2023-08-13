#include "state/CartesianState.hpp"

#include <pybind11/pybind11.h>
// #include <pybind11/eigen.h>

#include <iostream>

int my_test_fun(int a) {
    CartesianState sv( Eigen::Vector3d(8000,0,0), Eigen::Vector3d(0,8,0) );
    std::cout << "WOOOW" << std::endl;
    return a * a;
}

// Note: MODULE_NAME is a definition set by CMake
PYBIND11_MODULE(MODULE_NAME, m) {
    m.doc() = "Keplerian Toolkit Python Module";

    m.def("my_test_fun", &my_test_fun, "Test Function");
}
