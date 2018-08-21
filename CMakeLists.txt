cmake_minimum_required(VERSION 3.12)

# Project
project(mock_distribution)

# C++ standards version
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(./vendor/zmq/include/)

# Set output directory
set(out_dir ${CMAKE_CURRENT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${out_dir})

#==========================================================
# Executable: Server
#==========================================================
file(GLOB_RECURSE src_server "./src/modules/server/*.cpp")
add_executable(MockDist-Server ${src_server})

#==========================================================
# Executable: Balancer
#==========================================================
file(GLOB_RECURSE src_balancer "./src/modules/balancer/*.cpp")
add_executable(MockDist-Balancer ${src_balancer})

#==========================================================
# Executable: Worker
#==========================================================
file(GLOB_RECURSE src_worker "./src/modules/worker/*.cpp")
add_executable(MockDist-Worker ${src_worker})

#==========================================================
# Executable: Sink
#==========================================================
file(GLOB_RECURSE src_sink "./src/modules/sink/*.cpp")
add_executable(MockDist-Sink ${src_sink})

#==========================================================
# Linker
#==========================================================
target_link_libraries(MockDist-Server PRIVATE zmq)
target_link_libraries(MockDist-Balancer PRIVATE zmq)
target_link_libraries(MockDist-Worker PRIVATE zmq)
target_link_libraries(MockDist-Sink PRIVATE zmq)
