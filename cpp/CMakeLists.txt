cmake_minimum_required (VERSION 3.4.0)
project (jni_test)

# use -O3 in CMake.
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

aux_source_directory(. DIR_SRCS)
# add the shared library.
add_library( # Specifies the name of the library.
            pre-process
            # Sets the library as a shared library.
            SHARED
            # Provides a relative path to your source file(s).
            ${DIR_SRCS}
    )
# add_executable(a.out ${DIR_SRCS})
