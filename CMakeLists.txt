cmake_minimum_required(VERSION 3.23)
project(ND1)

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/3d787f5a0d58cfc37a0563bb15647a0d8aa2c1bf.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(demo demo.cpp)
target_link_libraries(demo large_float)
target_include_directories(demo PUBLIC "./LargeFloat/src")

add_executable(test_exe test.cpp)
target_link_libraries(test_exe large_float)
target_include_directories(test_exe PUBLIC "./LargeFloat/src")

enable_testing()

add_subdirectory(LargeInt)
add_subdirectory(LargeFloat)

add_subdirectory(submissions)

add_executable(ND1 main.cpp)
target_link_libraries(ND1 large_int)
target_include_directories(ND1 PUBLIC LargeInt/src)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif ()
