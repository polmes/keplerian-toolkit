#include <Eigen/Dense>

class CartesianState {
	public:
		CartesianState(const Eigen::Vector3d& pos, const Eigen::Vector3d& vel);

	private:
		Eigen::Vector3d pos;
		Eigen::Vector3d vel;
};
