cmake_minimum_required (VERSION 3.1.0)
set (EXE_NAME flat_tau3pi)
project (${EXE_NAME} C CXX)
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
add_definitions (-Wfatal-errors)
find_package (Boost COMPONENTS program_options system REQUIRED)
find_package (Threads)
include_directories ( ${Boost_INCLUDE_DIR} rlibs/include gen/include )
add_subdirectory (rlibs)
add_subdirectory (gen)
add_executable (${EXE_NAME} ${EXE_NAME}.cpp)
target_link_libraries( ${EXE_NAME} ${Boost_LIBRARIES} rlibs gen)
