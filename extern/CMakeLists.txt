# Downloads and installs third-party dependencies

ExternalProject_Add(
	eigen
	GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
	GIT_TAG tags/3.4.0
	GIT_SHALLOW TRUE
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR} -DINCLUDE_INSTALL_DIR=${EIGEN_INCLUDE}
)

