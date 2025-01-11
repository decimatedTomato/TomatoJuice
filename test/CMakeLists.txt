cmake_minimum_required(VERSION 3.22)

project(inverse_kinematics_cyclic_coordinate_descent)

add_executable(${PROJECT_NAME}
    src/main.c
)
target_include_directories(${PROJECT_NAME} PRIVATE "include")
target_link_directories(${PROJECT_NAME} PRIVATE "lib")
target_link_libraries(${PROJECT_NAME} libraylib.a m)