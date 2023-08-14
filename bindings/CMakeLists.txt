# Build the internal Python module, named _ktk
set(EXTERNAL_MODULE_NAME ktk)
set(INTERNAL_MODULE_NAME _${EXTERNAL_MODULE_NAME})
pybind11_add_module(${INTERNAL_MODULE_NAME} ktk.cpp)
target_compile_definitions(${INTERNAL_MODULE_NAME} PRIVATE "MODULE_NAME=${INTERNAL_MODULE_NAME}")
target_link_libraries(${INTERNAL_MODULE_NAME} PRIVATE ${LIBRARY_NAME})
set_target_properties(${INTERNAL_MODULE_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${INTERNAL_MODULE_NAME} PROPERTIES INSTALL_RPATH $ORIGIN) # to search for main shared library *.so in same directory as Python module

# Install the Python module under <site-packages> along with the shared library that it needs
# note: scikit-build will move the *.so files to the correct place
message(STATUS "Python Wheels and Dependencies: ${CMAKE_INSTALL_PREFIX}/${EXTERNAL_MODULE_NAME}")
install(
    TARGETS ${INTERNAL_MODULE_NAME}
    LIBRARY DESTINATION ${EXTERNAL_MODULE_NAME}
)
install(
    TARGETS ${LIBRARY_NAME}
    LIBRARY DESTINATION ${EXTERNAL_MODULE_NAME}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Generate and install the Python stubs for type hints
# note: adapted from https://github.com/tttapa/py-build-cmake/blob/main/examples/pybind11-project/cmake/Pybind11Stubgen.cmake]
option(BUILD_STUBS "Build Python Stubs" OFF)
if(BUILD_STUBS)
    find_package(Python3 REQUIRED COMPONENTS Interpreter)
    message(STATUS ${INTERNAL_MODULE_NAME})
    message(STATUS $<TARGET_FILE_BASE_NAME:${INTERNAL_MODULE_NAME}>)
    message(STATUS $<TARGET_FILE_DIR:${INTERNAL_MODULE_NAME}>)
    message(STATUS $<TARGET_FILE_DIR:${INTERNAL_MODULE_NAME})
    add_custom_command(
        TARGET ${INTERNAL_MODULE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo
        "$<TARGET_FILE_BASE_NAME:${INTERNAL_MODULE_NAME}> -o $<TARGET_FILE_DIR:${INTERNAL_MODULE_NAME}>" # --bare-numpy-ndarray --no-setup-py
        "$<TARGET_FILE_DIR:${INTERNAL_MODULE_NAME}>/$<TARGET_FILE_BASE_NAME:${INTERNAL_MODULE_NAME}>-stubs/"
        "${EXTERNAL_MODULE_NAME}/$<TARGET_FILE_BASE_NAME:${INTERNAL_MODULE_NAME}>"
    )

    add_custom_command(
        TARGET ${INTERNAL_MODULE_NAME} POST_BUILD
        COMMAND ${Python3_EXECUTABLE} -m pybind11_stubgen $<TARGET_FILE_BASE_NAME:${INTERNAL_MODULE_NAME}> -o $<TARGET_FILE_DIR:${INTERNAL_MODULE_NAME}> # --bare-numpy-ndarray --no-setup-py
        WORKING_DIRECTORY $<TARGET_FILE_DIR:${INTERNAL_MODULE_NAME}>
        USES_TERMINAL
    )
    install(
        DIRECTORY $<TARGET_FILE_DIR:${INTERNAL_MODULE_NAME}>/$<TARGET_FILE_BASE_NAME:${INTERNAL_MODULE_NAME}>-stubs/
        DESTINATION ${EXTERNAL_MODULE_NAME}
    )
endif()
