cmake_minimum_required(VERSION 3.23)
project(ND1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/3d787f5a0d58cfc37a0563bb15647a0d8aa2c1bf.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(LargeInt)

#add_executable(ND1 main.cpp)
#
#target_link_libraries(ND1 largeNumbers)
#target_include_directories(ND1 PUBLIC LargeNumber/src)
