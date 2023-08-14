#include "state/CartesianState.hpp"

CartesianState::CartesianState(const Eigen::Vector3d& pos, const Eigen::Vector3d& vel)
    : pos(pos), vel(vel) {}

Eigen::Vector3d CartesianState::position() {
    return pos;
}

Eigen::Vector3d CartesianState::velocity() {
    return vel;
}
