FILE(GLOB SRC_FILES *.cpp)

add_library(large_int STATIC ${SRC_FILES})
target_include_directories(large_int PUBLIC "${CMAKE_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}/LargeFloat/src")

set_target_properties(large_int PROPERTIES LINKER_LANGUAGE CXX)
