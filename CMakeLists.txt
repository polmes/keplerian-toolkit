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
set(SOURCES_DIR src)
set(INCLUDE_DIR include)
set(DEPENDS_DIR extern)
set(INSTALL_DIR install)
set(LIBRARY_DIR lib)
set(TESTING_DIR tests)
set(BINDING_DIR bindings)
set(PACKAGE_DIR ktk)

# Eigen library dependency
include_directories(${DEPENDS_DIR}/eigen)

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
option(DEVELOPMENT_INSTALL "Install Artifacts Under Project Directory" OFF)
if(DEVELOPMENT_INSTALL)
	set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/${INSTALL_DIR})
endif()
install(
	TARGETS ${LIBRARY_NAME}
	LIBRARY DESTINATION ${LIBRARY_DIR}       # /usr/local/lib
	PUBLIC_HEADER DESTINATION ${INCLUDE_DIR} # /usr/local/include
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
	set(PYBIND11_FINDPYTHON ON)
	add_subdirectory(${DEPENDS_DIR}/pybind11)
	# add Python module targets
	add_subdirectory(${BINDING_DIR})
endif()
