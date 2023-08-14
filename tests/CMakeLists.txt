# Create macro that adds executable, links it, and creates test with provided input arguments
# by convention, test sources are named Test_Something.cpp for the Something test
function(add_executable_test NAME)
    add_executable(${NAME} cpp/${NAME}.cpp)
    target_link_libraries(${NAME} PRIVATE ${LIBRARY_NAME})
    add_test(${NAME} ${NAME} ${ARGN}) # pass in the rest of the input arguments as arguments to the test
endfunction()

# Add all the tests
add_executable_test(Test_CartesianState)
