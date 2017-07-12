cmake_minimum_required (VERSION 3.4.0)
project (jni_test)

# use -O3 in CMake.
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

aux_source_directory(. DIR_SRCS)
# add the executable
# add_executable(main ${DIR_SRCS})
add_library( # Specifies the name of the library.
             native-lib
            # Sets the library as a shared library.
             SHARED
            # Provides a relative path to your source file(s).
            ${DIR_SRCS}
    )
