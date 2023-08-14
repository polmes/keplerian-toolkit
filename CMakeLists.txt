# CMake requirements
cmake_minimum_required(VERSION 3.20)

# Parse version from pyproject.toml file
file(READ "pyproject.toml" PYPROJECT_TOML)
string(REGEX MATCH "version = \"([0-9]+.[0-9]+.[0-9]+)\"" _ ${PYPROJECT_TOML})
set(PYPROJECT_VERSION ${CMAKE_MATCH_1})

# Define the project
project(KeplerianToolkit VERSION ${PYPROJECT_VERSION} LANGUAGES CXX)

# Use C++ 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# All relevant directories
set(SOURCES_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(TESTING_DIR ${CMAKE_SOURCE_DIR}/tests)
set(BINDING_DIR ${CMAKE_SOURCE_DIR}/bindings)
set(PACKAGE_DIR ${CMAKE_SOURCE_DIR}/ktk)

# List where output shared libraries, public headers, and python wheels will go
message(STATUS "Artifacts will be installed under ${CMAKE_INSTALL_PREFIX}")

# Eigen library dependency
# note: using FetchContent without MakeAvailable to download the necessary headers without adding additional build targets or using submodules
# include(ExternalProject)
# # set(EIGEN_SOURCES_DIR ${CMAKE_BINARY_DIR}/eigen)
# set(EIGEN_NAME eigen)
# ExternalProject_Add(
#     ${EIGEN_NAME}
#     GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
#     GIT_TAG 3.4.0
#     GIT_SHALLOW TRUE
#     CONFIGURE_COMMAND ""
#     BUILD_COMMAND ""
#     INSTALL_COMMAND ""
#     TEST_COMMAND ""
# )
# ExternalProject_Get_Property(${EIGEN_NAME} SOURCE_DIR)
# message(STATUS ${EIGEN_NAME})
# message(STATUS ${SOURCE_DIR})
# include_directories(${DEPENDS_DIR}/eigen)

include(FetchContent)
FetchContent_Declare(
    eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 3.4.0
    GIT_SHALLOW TRUE
)
FetchContent_GetProperties(eigen)
if(NOT eigen_POPULATED)
    message(STATUS "Downloading Eigen dependency")
    FetchContent_Populate(eigen)
endif()
message(STATUS "Found Eigen at ${eigen_SOURCE_DIR}")
include_directories(${eigen_SOURCE_DIR})

# Find all sources and public headers
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${SOURCES_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS ${INCLUDE_DIR}/*.hpp)

# Be pedantic
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Build shared library
set(LIBRARY_NAME ktklib)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(${LIBRARY_NAME} SHARED ${SOURCES})
target_include_directories(${LIBRARY_NAME} PUBLIC ${INCLUDE_DIR}) # allows tests and bindings to inherit public headers
target_include_directories(${LIBRARY_NAME} PRIVATE ${SOURCES_DIR})
set_target_properties(${LIBRARY_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${LIBRARY_NAME} PROPERTIES PUBLIC_HEADER "${HEADERS}")

# Install shared library
include(GNUInstallDirs)
message(STATUS "Shared Libraries: ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
message(STATUS "Public Headers: ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")
install(
    TARGETS ${LIBRARY_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}           # <prefix>/lib     (default is /usr/local/lib)
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} # <prefix>/include (default is /usr/local/include)
)

# Unit tests
option(BUILD_TESTS "Build Unit Tests" ON)
if(BUILD_TESTS)
    message(STATUS "Building Unit Tests")
    # CTest module
    include(CTest)
    enable_testing()
    # add all the test targets
    add_subdirectory(${TESTING_DIR})
endif()

# Python bindings
option(BUILD_BINDINGS "Build Python Bindings" OFF)
if(BUILD_BINDINGS)
    message(STATUS "Building Python Bindings")
    # pybind11 library
    # note: using FetchContent to add dependency without submodules
    FetchContent_Declare(
        pybind11
        GIT_REPOSITORY https://github.com/pybind/pybind11
        GIT_TAG v2.11.1
        GIT_SHALLOW TRUE
    )
    FetchContent_GetProperties(pybind11)
    if(NOT pybind11_POPULATED)
    message(STATUS "Downloading pybind11 dependency")
        FetchContent_Populate(pybind11)
    endif()
    set(PYBIND11_FINDPYTHON ON)
    message(STATUS "Found pybind11 at ${pybind11_SOURCE_DIR}")
    add_subdirectory(${pybind11_SOURCE_DIR} ${pybind11_BINARY_DIR}) # note: adding binary directory here for out-of-tree pip builds
    # add Python module targets
    add_subdirectory(${BINDING_DIR})
endif()
