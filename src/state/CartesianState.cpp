#include "state/CartesianState.hpp"

CartesianState::CartesianState(const Eigen::Vector3d& pos, const Eigen::Vector3d& vel)
    : pos(pos), vel(vel) {}
