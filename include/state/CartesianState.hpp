#include <Eigen/Dense>

class CartesianState {
    public:
        CartesianState(const Eigen::Vector3d& pos, const Eigen::Vector3d& vel);
        Eigen::Vector3d position();
        Eigen::Vector3d velocity();

    private:
        Eigen::Vector3d pos;
        Eigen::Vector3d vel;
};
