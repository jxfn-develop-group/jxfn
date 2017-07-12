cmake_minimum_required (VERSION 2.6)
project (jni_test)

# use -O3 in CMake.
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

aux_source_directory(. DIR_SRCS)
# add the executable
add_executable(main ${DIR_SRCS})
