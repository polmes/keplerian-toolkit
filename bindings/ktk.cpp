#include <pybind11/pybind11.h>

// define the various submodules
void ktk_CartesianState(pybind11::module& m);


// Note: MODULE_NAME is a definition set by CMake
PYBIND11_MODULE(MODULE_NAME, m) {
    m.doc() = "Keplerian Toolkit Python Module";

    // add the variuos binding definitions
    ktk_CartesianState(m);
}
